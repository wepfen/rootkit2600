#!/bin/sh

# This script  compiles the kernel source code

KERNEL_VERSION=$1

if [ -z "$KERNEL_VERSION" ]; then
    echo "Usage: $0 <kernel_version>"
    exit 1
fi

# Compile the kernel
cd linux-${KERNEL_VERSION}

# Ask the user if they want to configure the kernel by running make defconfig
read -p "[*] Do you want to configure the kernel? [y/N]: " choice
case $choice in
    [Yy]* ) make defconfig;;
    [Nn]* ) echo "[*] Skipping kernel configuration.";;
    * ) echo "Invalid choice"; exit 1;;
esac

echo "[+] Compiling the kernel..."

# Compile the kernel
make -j$(nproc)

if [ $? -ne 0 ]; then
    echo "[-] Failed to compile the kernel."
    exit 1
fi

echo "[*] Kernel compiled successfully."

cd ..

echo "[*] Done."