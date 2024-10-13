ROOTKIT := rootkit

# Directories
MODS_DIR := /lib/modules/$(shell uname -r)
BUILD_DIR := $(MODS_DIR)/build
KERN_DIR := $(MODS_DIR)/kernel

# Module
obj-m := $(ROOTKIT).o

# Core
$(ROOTKIT)-y += core.o init.o

# Fonctionnalities
#$(ROOTKIT)-y 		+= module.o

# Flags
ccflags-y += -I$(PWD)/include
ccflags-y += -O0 -Wno-declaration-after-statement -Wno-discarded-qualifiers

all:
	make -C $(BUILD_DIR) M=$(PWD) modules

clean:
	make -C $(BUILD_DIR) M=$(PWD) clean

install:
	sudo insmod $(ROOTKIT).ko

remove:
	sudo rmmod $(ROOTKIT).ko