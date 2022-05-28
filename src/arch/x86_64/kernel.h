#ifndef TYPES
#define TYPES

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long uint64;
typedef unsigned long long uint128;
typedef unsigned long long size_t;

#define nullptr (void*)0x0
#define UINT64_MAX 0xFFFFFFFFFFFFFFFF

typedef uint8 bool;

#define true 1
#define false 0
#endif

#ifndef KERNEL_H
#define KERNEL_H

#define VGA_ADDRESS 0xB8000
#define BUFSIZE 2200

uint16* vga_buffer;

#define NULL 0

enum vga_color {
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    GREY,
    DARK_GREY,
    BRIGHT_BLUE,
    BRIGHT_GREEN,
    BRIGHT_CYAN,
    BRIGHT_RED,
    BRIGHT_MAGENTA,
    YELLOW,
    WHITE,
};
#endif
