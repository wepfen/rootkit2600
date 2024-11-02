.DEFAULT_GOAL := help
KERNEL ?= 6.11
DISK ?= disk.img
DISK_QCOW2 = disk.qcow2

help:
	@echo "Usage: make <target>"
	@echo "Targets:"
	@echo "  help         			Display this help message"
	@echo "  lfs         			Build the lfs : compile the kernel, build VM img and run it"
	@echo "  build      			Deploy VM and build kernel with defconfig"
	@echo "  kernel			Download and compile kernel"  
	@echo "  get_kernel 			Download kernel" 
	@echo "  compile_kernel 		Compile kernel" 
	@echo "  disk        			Make VM disk image" 
	@echo "  deploy        		Run VM (build it if necessary)"
	@echo "  run				Run VM only" 
	@echo "  convert 			Convert img disk to compressed qcow2" 
	@echo "  clean        			Clean up VM images"
	@echo ""
	@echo "Optionnal params:"
	@echo "  KERNEL=<version>		Define the kernel version to be compiled (default: ${KERNEL})"
	@echo "  DISK=<disk path>		Specifies the disk path to be ran (default : ${DISK})"
	
clean:
	rm -rf $(DISK) $(DISK_QCOW2)

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

.PHONY: help kernel compile_kernel clean get_kernel disk run deploy all
