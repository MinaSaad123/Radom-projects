# Simple Linux Distribution for ARM Versatile Board

## Project Overview
This project aims to create a simple custom Linux distribution from scratch for the ARM Versatile board and run it on QEMU. You will cross-compile your shell (and other utilities you created) and run them inside this new Linux distribution. By the end, you'll understand the essential steps involved in creating a Linux system and running it in an ARM environment.

## Prerequisites
Before you begin, ensure you have the following installed on your development machine:
- QEMU
- Cross-compiler for ARM (`gcc-arm-linux-gnueabi` or similar)
- BusyBox
- Buildroot (optional)
- GNU Make
- Linux kernel source code
- Any shell or utilities you've created

## Steps to Create the Linux Distribution

### 1. Set Up Cross-Compiler
Install the ARM cross-compiler toolchain:

```bash
sudo apt-get install gcc-arm-linux-gnueabi
```
### 2. Download and Compile the Linux Kernel
Download the Linux kernel source for ARM and compile it using the cross-compiler:

```bash
git clone https://github.com/torvalds/linux.git
cd linux
make ARCH=arm versatile_defconfig
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- -j4
```
This will create a kernel image called zImage.

### 3. Create a Root Filesystem
Use BusyBox to create a minimal root filesystem:

```bash
git clone https://git.busybox.net/busybox
cd busybox
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- defconfig
make ARCH=arm CROSS_COMPILE=arm-linux-gnueabi- install
```
This will create a directory with the essential binaries and configuration files for the root filesystem.

### 4. Configure the Root Filesystem
In the root filesystem, create necessary directories and configuration files:

```bash
mkdir -p rootfs/{bin,sbin,etc,proc,sys,usr/{bin,sbin}}
cp -a busybox/_install/* rootfs/
```

Create a basic init file in the root filesystem’s etc directory:
```bash
#!/bin/sh

mount -t proc none /proc
mount -t sysfs none /sys
mknod -m 660 /dev/mem c 1 1
echo -e "\nHello!\n"
exec /bin/sh
```

### 5. Cross-Compile Your Shell and Utilities
If you have your own shell like me or other utilities, cross-compile them for ARM:

```bash
arm-linux-gnueabi-gcc -o my_shell my_shell.c
cp my_shell rootfs/bin/
```

### 6. Run Linux on QEMU
Now run your custom Linux distribution using QEMU:

```bash
qemu-system-arm -M versatilepb -kernel zImage -hda rootfs.img -append "root=/dev/sda console=ttyAMA0" -serial stdio
```
This command boots the ARM Versatile board with your Linux kernel and root filesystem in QEMU.

### 7. Test Your Shell
Once the system is running, you should see the prompt for your custom shell. Run your shell or other utilities inside the QEMU environment.

[Screencast from 02 أكت, 2024 EEST 05:26:36 ص.webm](https://github.com/user-attachments/assets/3d757797-4014-4ee2-bffd-1030ec2ab186)
