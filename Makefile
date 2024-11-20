# Kernel & image
KERNEL ?= 6.11
DISK ?= disk.img
DISK_QCOW2 = disk.qcow2

# Building the rootkit
ROOTKIT := rootkit
ROOTKIT_DIR := src/rootkit
MODS_DIR := linux-${KERNEL}
BUILD_DIR := $(MODS_DIR)
KERN_DIR := $(MODS_DIR)
SHARED_FOLDER := /tmp/qemu-share

# Module	
obj-m += $(ROOTKIT_DIR)/$(ROOTKIT).o

# Core
$(ROOTKIT)-y += $(ROOTKIT_DIR)/core.o $(ROOTKIT_DIR)/init.o

# Flags
ccflags-y += -I$(PWD)/include
ccflags-y += -O0 -Wno-declaration-after-statement -Wno-discarded-qualifiers

PWD := $(CURDIR)

build:
	make -C ${BUILD_DIR} M=$(PWD) modules
	@mkdir -p /tmp/qemu-share
	@cp ${ROOTKIT_DIR}/rootkit.ko $(SHARED_FOLDER) 

clean:
	make -C ${BUILD_DIR} M=$(PWD) clean
	@rm ${ROOTKIT_DIR}/client

help:
	@echo "Usage: make <target>"
	@echo "Targets:"
	@echo "  help         			Display this help message"
	@echo "  lfs         			Build the lfs : compile the kernel, build VM img and run it"
	@echo "  build      			Compile rootkit"
	@echo "  kernel			Download and compile kernel"  
	@echo "  get_kernel 			Download kernel" 
	@echo "  compile_kernel 		Compile kernel" 
	@echo "  disk        			Make VM disk image" 
	@echo "  deploy        		Run VM (build it if necessary)"
	@echo "  run				Run VM only" 
	@echo "  convert 			Convert img disk to compressed qcow2" 
	@echo "  clean        			Clean modules"
	@echo "  clean_disk    			Clean up VM images"
	@echo ""
	@echo "Optionnal params:"
	@echo "  KERNEL=<version>		Define the kernel version to be compiled (default: ${KERNEL})"
	@echo "  DISK=<disk path>		Specifies the disk path to be ran (default : ${DISK})"
	
kernel:
	./scripts/get_kernel.sh $(KERNEL) 
	./scripts/compile_kernel.sh $(KERNEL)

compile_kernel:
	./scripts/compile_kernel.sh $(KERNEL)

get_kernel:
	./scripts/get_kernel.sh $(KERNEL) 

disk:
	./scripts/build_img.sh $(KERNEL)

run:
	./scripts/run_vm.sh $(DISK)

convert:
	@qemu-img convert -cp -f raw -O qcow2 $(DISK) $(DISK_QCOW2) || { echo "Failed to convert image."; exit 1; }
	@echo "output : $(DISK_QCOW2)"

deploy : disk run

lfs: kernel deploy

clean_disk:
	rm -rf $(DISK) $(DISK_QCOW2)

.PHONY: help kernel compile_kernel clean get_kernel disk run deploy all clean_disk
