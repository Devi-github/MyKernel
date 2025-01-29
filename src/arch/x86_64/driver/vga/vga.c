#include "vga.h"
#include <string.h>

#define VGA_ADDRESS (void*)0xB8000
#define BUFSIZE 2200
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

// Clears VGA buffer
void vga_clear_buffer(uint8, uint8);

// VGA interface information structure
struct VGAInfo {
    // Index VGA cursor is currently at
    uint32 vga_index;
    // Next line index
    uint32 next_line_index;
    // Foreground color
    uint8 g_fore_color;
    // Background color
    uint8 g_back_color;
    // Buffer pointer
    uint16* vga_buffer;
} info;

void vga_init(uint8 fore_color, uint8 back_color) {
    info.vga_buffer = (uint16*)VGA_ADDRESS;
    vga_clear_buffer(fore_color, back_color);
    info.g_fore_color = fore_color;
    info.g_back_color = back_color;
}

void vga_set_cursor(uint32 index)
{
    info.vga_index = index;
    info.next_line_index = info.vga_index / 80 + 1;
}

void vga_set_cursor_coord(uint32 x, uint32 y) {
    info.vga_index = x + y * 80;
    info.next_line_index = y + 1;
}

void vga_clear_buffer(uint8 fore_color, uint8 back_color) {
    for(uint32 i = 0; i < BUFSIZE; i++) {
        info.vga_buffer[i] = vga_entry(0, fore_color, back_color);
    }
    info.next_line_index = 1;
    info.vga_index = 0;
}

void vga_set_color(uint8 fr, uint8 bg) {
    info.g_fore_color = fr;
    info.g_back_color = bg;
}

uint16 vga_entry(uint8 ch, uint8 fore_color, uint8 back_color) {
    uint16 ax = 0;
    uint8 ah = 0, al = 0;

    ah = back_color;
    ah <<= 4;
    ah |= fore_color;
    ax = ah;
    ax <<= 8;
    al = ch;
    ax |= al;

    return ax;
}

void newline() {
    if(info.next_line_index >= 55) {
        info.next_line_index = 0;
        vga_clear_buffer(info.g_fore_color, info.g_back_color);
    }
    info.vga_index = 80 * info.next_line_index;
    info.next_line_index++;
}

void vga_puts(const char *str, size_t length) {
    for(size_t i = 0; i < length; i++) {
        vga_putc(str[i]);
    }
}

void vga_putc(char c) {
    if(c == '\n') {
        newline();
        return;
    }

    info.vga_buffer[info.vga_index] = vga_entry(c, info.g_fore_color, info.g_back_color);
    info.vga_index++;
}

void vga_putcs(const char *str) {
    size_t length = strlen(str);
    vga_puts(str, length);
}
