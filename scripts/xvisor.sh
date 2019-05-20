#!/bin/bash

XVISOR=modules/xvisor
PATCH=modules/patches

DIRECTORY=$(cd `dirname $0` && pwd)

# Load Xvisor module
git submodule init
git submodule update

# Patch vexpress-v2p-ca9.dts
cd $DIRECTORY/..
patch -f $XVISOR/arch/arm/board/generic/dts/arm/vexpress-v2p-ca9.dts < $PATCH/vexpress-v2p-ca9.patch

# Build Xvisor
export CROSS_COMPILE=arm-none-eabi-
export xvisor_src=$XVISOR
cd $xvisor_src

git submodule init
git submodule update

make ARCH=arm generic-v7-defconfig
make
