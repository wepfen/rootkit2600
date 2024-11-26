#!/bin/bash

DISK_IMG=$1

if [ ! -f "$DISK_IMG" ]; then
	echo "[-] $DISK_IMG not found"
	exit 1
fi

shared_folder="/tmp/qemu-share"
if [ -f ${shared_folder} ]; then
	read -p "[*] ${shared_folder} is currently a file and a folder do you want to delete it ? [y/N]" choice
    case $choice in
        [Yy]* ) rm -rf ${shared_folder};;
        [Nn]* ) echo "make sure /tmp/qemu-share is a folder or make it available"; exit 0;;
        * ) echo "Invalid choice"; exit 1;;
    esac
fi


if [ ! -d ${shared_folder} ]; then
	echo "[*] Creating a shared folder on host at ${shared_folder}"
	mkdir -p $shared_folder
fi

echo "[*] Running QEMU..."
qemu-system-x86_64 -hda $DISK_IMG \
	-nographic \
	-virtfs local,path=$shared_folder,mount_tag=host0,security_model=passthrough,id=host0
