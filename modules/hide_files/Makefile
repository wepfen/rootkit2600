# Kernel
KERNEL ?= 6.11

# Building the rootkit
MOD := hide_files
BASE_DIR := ../..
MODS_DIR := $(BASE_DIR)/linux-${KERNEL}
BUILD_DIR := $(MODS_DIR)
KERN_DIR := $(MODS_DIR)
SHARED_FOLDER := /tmp/qemu-share
ROOTKIT_DIR := $(BASE_DIR)/src/rootkit
DIST := $(BASE_DIR)/dist
CC := clang

# Module	
obj-m += $(MOD).o

# Core
$(mod)-y += $(ROOTKIT_DIR)/core.o $(ROOTKIT_DIR)/init.o $(ROOTKIT_DIR)/hide.o

# Flags
ccflags-y += -I$(PWD)/include
ccflags-y += -O0 -Wno-declaration-after-statement -Wno-ignored-qualifiers 

PWD := $(CURDIR)

build:
	make -C ${BUILD_DIR} M=$(PWD) modules CC=$(CC) 
	@cp $(MOD).ko $(DIST)

clean:
	make -C ${BUILD_DIR} M=$(PWD) clean CC=$(CC) 

.PHONY: build
