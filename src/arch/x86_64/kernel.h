#ifndef TYPES
#define TYPES

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long uint64;
typedef unsigned long long uint128;
typedef unsigned long long size_t;

#define UINT64_MAX 0xFFFFFFFFFFFFFFFF
#define UINT32_MAX 0xFFFFFFFF
#define UINT16_MAX 0xFFFF
#define UINT8_MAX 0xFF

typedef uint8 bool;

#define true (bool)1
#define false (bool)0
#endif

#ifndef KERNEL_H
#define KERNEL_H

#define VGA_ADDRESS (void*)0xB8000
#define BUFSIZE 2200
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define NULL (void*)0

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
