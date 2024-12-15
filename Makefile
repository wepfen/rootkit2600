PWD := $(CURDIR)

CC := clang

# Kernel & image
KERNEL ?= 6.11
DISK ?= disk.img

DISK_QCOW2 := $(basename $(DISK)).qcow2

CLIENT := ientcli
ROOTKIT := rootkit

SHARED_FOLDER := /tmp/qemu-share

SRC_DIR := src
RELEASE_DIR := dist/
KERN_DIR := linux-${KERNEL}
CLIENT_DIR := $(SRC_DIR)/client
ROOTKIT_DIR := $(SRC_DIR)/rootkit

# Rootkit
obj-m += $(ROOTKIT).o

$(ROOTKIT)-y += $(ROOTKIT_DIR)/init.o
$(ROOTKIT)-y += $(ROOTKIT_DIR)/hide.o
# $(ROOTKIT)-y += $(ROOTKIT_DIR)/phide.o
$(ROOTKIT)-y += $(ROOTKIT_DIR)/privesc.o
$(ROOTKIT)-y += $(ROOTKIT_DIR)/kprobe.o
$(ROOTKIT)-y += $(ROOTKIT_DIR)/driver.o

# Client
CLIENT_SRC := $(CLIENT_DIR)/main.c
CLIENT_SRC += $(CLIENT_DIR)/commands.c

# Flags
ccflags-y += -I $(SRC_DIR)/include
ccflags-y += -I $(ROOTKIT_DIR)/include
ccflags-y += -O0 -Wno-declaration-after-statement -Wno-ignored-qualifiers 

CLIENT_FLAGS := -I $(SRC_DIR)/include -I $(CLIENT_DIR)/include

help:
	@echo "Usage: make <target>"
	@echo ""
	@echo "Targets:"
	@echo "  help         			Display this help message"
	@echo "  lfs         			Build the lfs : compile the kernel, build VM img and run it"
	@echo "  build      			Compile and copy rootkit and client"
	@echo "  rootkit			Compile rootkit"
	@echo "  client			Compile client"
	@echo "  copy				Copy rootkit and client to shared folder"
	@echo "  kernel			Download and compile kernel"
	@echo "  get_kernel 			Download kernel"
	@echo "  compile_kernel 		Compile kernel"
	@echo "  disk        			Make VM disk image"
	@echo "  deploy        		Run VM (build it if necessary)"
	@echo "  run				Run VM only"
	@echo "  convert 			Convert img disk to compressed qcow2"
	@echo "  clean        			Clean modules"
	@echo "  clean_disk    		Clean up VM images"
	@echo ""
	@echo "Optionnal params:"
	@echo "  KERNEL=<version>		Define the kernel version to be compiled (default: ${KERNEL})"
	@echo "  DISK=<disk path>		Specifies the disk path to be ran (default : ${DISK})"

build: rootkit client copy

rootkit:
	make -C ${KERN_DIR} M=$(PWD) modules CC=$(CC) 
	@mkdir -p $(RELEASE_DIR)
	@mv $(ROOTKIT).ko $(RELEASE_DIR)

client:
	gcc -Wall -Werror -static -o $(CLIENT) $(CLIENT_SRC) $(CLIENT_FLAGS) || { echo "Failed to compile client."; exit 1; }
	@mkdir -p $(RELEASE_DIR)
	@mv $(CLIENT) $(RELEASE_DIR)

copy:
	@mkdir -p $(SHARED_FOLDER)
	@cp $(RELEASE_DIR)/* $(SHARED_FOLDER) || { echo "Failed to copy files."; exit 1; }

clean:
	make -C ${KERN_DIR} M=$(PWD) clean
	@rm -f dist/*

compile_kernel:
	./scripts/compile_kernel.sh $(KERNEL) $(CC)

get_kernel:
	./scripts/get_kernel.sh $(KERNEL) 

kernel: get_kernel compile_kernel

disk:
	./scripts/build_img.sh $(KERNEL) $(DISK)

run:
	./scripts/run_vm.sh $(DISK)

convert:
	@qemu-img convert -cp -f raw -O qcow2 $(DISK) $(DISK_QCOW2) || { echo "Failed to convert image."; exit 1; }
	@echo "output : $(DISK_QCOW2)"

deploy: disk run

lfs: kernel deploy

clean_disk:
	@rm -f *.img *.qcow2

.PHONY: help kernel compile_kernel clean get_kernel disk run deploy all clean_disk copy client build convert lfs
