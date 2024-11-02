#!/bin/bash

DISK_IMG=$1

if [ ! -f "disk.img" ]; then
	echo "[-] disk.img not found"
	exit 1
fi

shared_folder="/tmp/qemu-share"
if [ ! -d ${shared_folder} ]; then
	echo "[*] Creating a shared folder on host at ${shared_folder}"
	mkdir -p $shared_folder
fi

echo "[*] Running QEMU..."
qemu-system-x86_64 -hda $DISK_IMG \
	-nographic \
	-virtfs local,path=$shared_folder,mount_tag=host0,security_model=passthrough,id=host0
