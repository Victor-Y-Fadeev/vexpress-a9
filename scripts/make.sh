#!/bin/bash

XVISOR=modules/xvisor
PATCH=modules/patches
FREERTOS=modules/FreeRTOS
PORT=modules/port
CONFIG=modules/FreeRTOSConfig.h
SRC=src

DIRECTORY=$(cd `dirname $0` && pwd)

# Copy FreeRTOS source
cd $DIRECTORY/..
cp -rf $FREERTOS $XVISOR/tests/arm32/vexpress-a9/freertos
cp -rf $PORT $XVISOR/tests/arm32/vexpress-a9/freertos
cp -f $CONFIG $XVISOR/tests/arm32/vexpress-a9/freertos

# Patch vexpress-a9 source
patch -f $XVISOR/tests/arm32/vexpress-a9/freertos/glue.c < $PATCH/glue.patch
patch -f $XVISOR/tests/arm32/vexpress-a9/freertos/Makefile < $PATCH/makefile.patch
patch -f $XVISOR/tests/arm32/vexpress-a9/xscript/one_guest_vexpress-a9.xscript < $PATCH/one_guest_vexpress-a9.patch

# Copy application source
cp -rf $SRC $XVISOR/tests/arm32/vexpress-a9/freertos

# Build FreeRTOS
export CROSS_COMPILE=arm-none-eabi-
cd $XVISOR/tests/arm32/vexpress-a9/freertos
if ! make ; then
	exit 1
fi

# Create the disk image for Xvisor
cd ../../../..

dtc=./build/tools/dtc/bin/dtc
bindir=./build/disk/images/arm32/vexpress-a9
system_dir=./build/disk/system
img_dir=./build/disk/images/arm32
srcdir=./tests/arm32/vexpress-a9

mkdir -p $system_dir
mkdir -p $bindir

cp -f ../banner/roman.txt $system_dir/banner.txt
$dtc -I dts -O dtb -o $img_dir/vexpress-a9x2.dtb $srcdir/vexpress-a9x2.dts
cp -f ./build/$srcdir/freertos/freertos.patched.bin $bindir/freertos.bin
cp -f $srcdir/freertos/nor_flash.list $bindir/nor_flash.list
cp -f $srcdir/xscript/one_guest_vexpress-a9.xscript ./build/disk/boot.xscript
genext2fs -B 1024 -b 32768 -d ./build/disk ./build/disk.img
