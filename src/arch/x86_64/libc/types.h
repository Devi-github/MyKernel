#ifndef TYPES_H_
#define TYPES_H_

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;
typedef unsigned long long size_t;

#define UINT64_MAX 0xFFFFFFFFFFFFFFFF
#define UINT32_MAX 0xFFFFFFFF
#define UINT16_MAX 0xFFFF
#define UINT8_MAX 0xFF

#define WORD_SIZE 4

#define NULL (void*)0

typedef unsigned char bool;

#define true (bool)1
#define false (bool)0

enum vga_color {
    C_BLACK,
    C_BLUE,
    C_GREEN,
    C_CYAN,
    C_RED,
    C_MAGENTA,
    C_BROWN,
    C_GREY,
    C_DARK_GREY,
    C_BRIGHT_BLUE,
    C_BRIGHT_GREEN,
    C_BRIGHT_CYAN,
    C_BRIGHT_RED,
    C_BRIGHT_MAGENTA,
    C_YELLOW,
    C_WHITE,
};

#endif