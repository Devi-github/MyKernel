#ifndef KERNEL_H
#define KERNEL_H

#include "types.h"

#define VGA_ADDRESS (void*)0xB8000
#define BUFSIZE 2200
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

// Gets current clock cycles as a 64 bit number
uint64 __gcca();

#endif
