#!/bin/bash

#
# This script is used to create a disk image with a minimal Alpine Linux
# based on the kernel you pass as argument
#
# Usage: ./build_img.sh <kernel_version>
#
# Note: You need to build your kernel before running this script
#
# Requirements:
# - Docker
# - Parted
# - mkfs.ext4

set -e

if [ -z "$1" ]; then
    echo "Usage: $0 <kernel_version>"
    exit 1
fi

KERNEL_VERSION=$1
KERNEL_PATH="linux-${KERNEL_VERSION}"

# Check if the kernel source exists and if it is built
if [ ! -d $KERNEL_PATH ]; then
    echo "[-] Kernel source not found"
    exit 1
fi

if [ ! -f $KERNEL_PATH/arch/x86/boot/bzImage ]; then
    echo "[-] Kernel not built"
    exit 1
fi

DISK_IMG="disk.img"
DISK_SIZE="450M"
ROOTFS_DIR="/tmp/custom-rootfs"
LOOP_DEVICE=""

# Delete previous disk image if exists
if [ -f $DISK_IMG ]; then
    echo "[+] Deleting previous disk image..."
    rm $DISK_IMG
fi

echo "[+] Creating disk image..."
truncate -s $DISK_SIZE $DISK_IMG

echo "[+] Creating partition table..."
/sbin/parted -s $DISK_IMG mktable msdos
/sbin/parted -s $DISK_IMG mkpart primary ext4 1 "100%"
/sbin/parted -s $DISK_IMG set 1 boot on

echo "[+] Setting up loop device..."
sudo losetup -Pf $DISK_IMG
LOOP_DEVICE=$(losetup -l | grep $DISK_IMG | awk '{print $1}')

echo "[+] Formatting partition as ext4..."
sudo mkfs.ext4 ${LOOP_DEVICE}p1

echo "[+] Mounting partition..."
mkdir -p $ROOTFS_DIR
sudo mount ${LOOP_DEVICE}p1 $ROOTFS_DIR

echo "[+] Installing minimal Alpine Linux..."
docker run -it --rm -v $ROOTFS_DIR:/custom-rootfs alpine sh -c '
  apk add openrc util-linux build-base;
  ln -s agetty /etc/init.d/agetty.ttyS0;
  echo ttyS0 > /etc/securetty;
  rc-update add agetty.ttyS0 default;
  rc-update add root default;
  echo "root:root" | chpasswd;
  rc-update add devfs boot;
  rc-update add procfs boot;
  rc-update add sysfs boot;
  for d in bin etc lib root sbin usr; do tar c "/$d" | tar x -C /custom-rootfs; done;
  for dir in dev proc run sys var; do mkdir -p /custom-rootfs/${dir}; done;
'

echo "[+] Copying Kernel source to rootfs..."
sudo mkdir $ROOTFS_DIR/boot
sudo cp $KERNEL_PATH/arch/x86/boot/bzImage $ROOTFS_DIR/boot/vmlinuz

echo "[+] Configuring GRUB..."
sudo mkdir -p $ROOTFS_DIR/boot/grub

cat <<EOF | sudo tee $ROOTFS_DIR/boot/grub/grub.cfg 
serial
terminal_input serial
terminal_output serial
set root=(hd0,1)
menuentry "Linux2600" {
    linux /boot/vmlinuz root=/dev/sda1 console=ttyS0 noapic
}
EOF

echo "[+] Installing GRUB..."
sudo grub-install --directory=/usr/lib/grub/i386-pc --boot-directory=$ROOTFS_DIR/boot $LOOP_DEVICE

echo "[+] Cleaning up..."
sudo umount $ROOTFS_DIR
sudo losetup -d $LOOP_DEVICE

echo "[*] Disk image created successfully at $DISK_IMG"
