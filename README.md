# My simple 64 bit kernel

## Overview

This is a kernel or OS that is written in **ASM** and **C**. It's pretty simple and straightforward, though not very functional sometimes.

This serves as an educative demo of a kernel with simple commands and without multitasking or any kind of *good* IO interface. Don't take it seriously

## Prerequisites

To install all prerequisites use these commands: 

```bash
sudo apt update
sudo apt install qemu -y
sudo apt install qemu-system-x86 -y
sudo apt install xorriso -y
sudo apt install mtools -y
```

## Installation

### Linux Debian or Ubuntu

Just copy the repository in your directory using 

```bash
git clone https://github.com/IgruantyPlay/MyKernel.git
```

And that is all! You are ready for the next step.

## Build and run

### Linux Debian or Ubuntu

To build our little OS run:

```bash
make all # or just 'make', no difference
```

Than to run it just use `make run` or `qemu-systems-x86_64 -cdrom build/os-x86_64.iso`

## And that is it!

You are ready to use it! Though, the only use now is education I suppose

## Contributions

I will be glad if anyone points out any mistakes and corrects it to finally support floats. I am a beginner programmer especially in this topic. Because of that I want to learn more. Thank you!
