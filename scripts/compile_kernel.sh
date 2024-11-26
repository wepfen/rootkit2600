#!/bin/sh

# This script  compiles the kernel source code

KERNEL_VERSION=$1

if [ -z "$KERNEL_VERSION" ]; then
    echo "Usage: $0 <kernel_version>"
    exit 1
fi

# Check if the kernel version exists
if [ ! -d "linux-${KERNEL_VERSION}" ]; then
	echo "[-] linux-${KERNEL_VERSION} not found"
	echo "[-] You may download it first : make get_kernel KERNEL=${KERNEL_VERSION}"
	exit 1
fi


# Compile the kernel
cd linux-${KERNEL_VERSION}

# Check if the kernel is already compiled
if [ -f "arch/x86/boot/bzImage" ]; then
	read -p "[*] Kernel already compiled, compile anyway ? [y/N]" choice
	case $choice in
		[Yy]* ) echo "[+] Compiling the kernel...";;
		[Nn]* ) exit 0;;
		* ) echo "Invalid choice"; exit 1;;
	esac
fi

# Configure the kernel .config is not found (default config is used)
if [ ! -f ".config" ]; then
    echo "[+] Configuring the kernel";
    make defconfig;
fi

# Compile the kernel
make -j$(nproc)

if [ $? -ne 0 ]; then
    echo "[-] Failed to compile the kernel."
    exit 1
fi

echo "[*] Kernel compiled successfully."

cd ..

echo "[*] Done."
