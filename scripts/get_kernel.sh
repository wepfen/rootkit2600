#!/bin/sh

# This script downloads the kernel source code from kernel.org

KERNEL_VERSION=$1

if [ -z "$KERNEL_VERSION" ]; then
    echo "Usage: $0 <kernel_version>"
    exit 1
fi

KERNEL_MAJOR_VERSION=$(echo $KERNEL_VERSION | cut -d. -f1)

echo "[*] Kernel version: $KERNEL_VERSION"
echo "[*] Kernel major version: $KERNEL_MAJOR_VERSION"

# Check if the kernel source code is already downloaded if so, ask the user if they want to download it again
if [ -d linux-${KERNEL_VERSION} ]; then
    read -p "[*] The kernel source code is already downloaded. Do you want to download it again? [y/N]: " choice
    case $choice in
        [Yy]* ) rm -rf linux-${KERNEL_VERSION};;
        [Nn]* ) exit 0;;
        * ) echo "Invalid choice"; exit 1;;
    esac
fi

# Craft the URL to download the kernel source code
KERNEL_SOURCE_URL="https://cdn.kernel.org/pub/linux/kernel/v${KERNEL_MAJOR_VERSION}.x/linux-${KERNEL_VERSION}.tar.xz"

echo "[+] Downloading the kernel source code..."

# Download the kernel source code
wget $KERNEL_SOURCE_URL -O linux-${KERNEL_VERSION}.tar.xz

if [ $? -ne 0 ]; then
    echo "[-] Failed to download the kernel source code."
	rm linux-${KERNEL_VERSION}.tar.xz
    exit 1
fi

echo "[*] Kernel source code downloaded successfully."
echo "[+] Extracting the kernel source code..."

# Extract the kernel source code
tar -xf linux-${KERNEL_VERSION}.tar.xz

if [ $? -ne 0 ]; then
    echo "[-] Failed to extract the kernel source code."
    exit 1
fi

echo "[*] Kernel source code extracted successfully."

echo "[+] Cleaning up..."

# Remove the downloaded tarball
rm linux-${KERNEL_VERSION}.tar.xz

echo "[*] Done."
