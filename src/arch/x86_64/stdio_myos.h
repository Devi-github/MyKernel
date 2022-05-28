#ifndef STDIO_H
#define STDIO_H
#include "kernel.h"
#include "keyboard.h"

// VGA interface information structure
struct VGAInfo {
    uint32 vga_index;
    uint32 next_line_index;
    uint8 g_fore_color;
    uint8 g_back_color;
};

// ##############################################
// STDOUT SECTION
// ##############################################
uint16 vga_entry(uint8, uint8, uint8);
void set_cursor(struct VGAInfo*, uint32);
void clear_vga_buffer(struct VGAInfo*, uint16**, uint8, uint8);
void init_vga(struct VGAInfo*, uint8, uint8);
void print_new_line(struct VGAInfo*);
void print_char(struct VGAInfo*, char);
uint32 strlen(const char*);
uint32 digit_count(int);
void itoa(int, char*);
void print_int(struct VGAInfo*, uint32);
void print_string(struct VGAInfo*, char*);

// ##############################################
// STDIN SECTION
// ##############################################

uint8 inb(uint16);
void outb(uint16, uint8);
char get_input_keycode();
void wait_for_io(uint32);
void sleep(uint32);
void test_input();

#endif