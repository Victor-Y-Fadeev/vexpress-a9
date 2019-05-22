FreeRTOS [![Build Status](https://travis-ci.org/Victor-Y-Fadeev/vexpress-a9.svg?branch=master)](https://travis-ci.org/Victor-Y-Fadeev/vexpress-a9)
========
This port runs FreeRTOS v10.2.0 on the Versatile Express with the the ARM Cortex-A9 MPCore.
It's use [Xvisor](https://github.com/xvisor/xvisor) hypervisor for running FreeRTOS as a guest OS.
And it's based on the available Cortex A9 Zynq ZC702 port.
For testing you could run it at the [QEMU](https://www.qemu.org/) virtual machine.

### Build Instructions
The next scripts automatically install and build Xvisor environment:
```
$ ./scripts/install.sh
$ ./scripts/xvisor.sh
```

To make your project use:
```
$ ./scripts/make.sh
```

And this for running it at the QEMU:
```
$ ./scripts/qemu.sh
```
