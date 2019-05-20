#!/bin/bash

XVISOR=modules/xvisor

DIRECTORY=$(cd `dirname $0` && pwd)

# Copy FreeRTOS source
cd $DIRECTORY/../$XVISOR
qemu-system-arm -M vexpress-a9 -m 512M -nographic \
	-kernel build/vmm.bin \
	-dtb    build/arch/arm/board/generic/dts/arm/vexpress-v2p-ca9.dtb \
	-initrd build/disk.img
