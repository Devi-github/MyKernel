#ifndef STDIO_H
#define STDIO_H
#include "kernel.h"
#include "keyboard.h"

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
};

// ##############################################
// STDOUT SECTION
// ##############################################

// VGA Entry
uint16 vga_entry(uint8, uint8, uint8);
// Sets cursor at specific index
void set_cursor(struct VGAInfo*, uint32);
// Sets cursor at specific coordinates
void set_cursor_coord(struct VGAInfo*, uint32, uint32);
// Clears VGA buffer
void clear_vga_buffer(struct VGAInfo*, uint16**, uint8, uint8);
/*
* Initialize VGA Text mode for screen, clears VGA buffer and sets foreground and background colors
*/
void init_vga(struct VGAInfo*, uint8, uint8);
// Prints new line
void print_new_line(struct VGAInfo*);
// Prints character on the screen
void print_char(struct VGAInfo*, char);
// Gets c-type string length
uint32 strlen(const char*);
// Gets length of a number
uint32 digit_count(int);
// Gets length of a 64 bit number
uint32 digit_count64(uint64);
// Gets string from number
void itoa(int, char*);
// Gets string from a 64 bit number
void itoa64(uint64, char*);
// Prints unsigned 32 bit number
void print_int(struct VGAInfo*, uint32);
// Prints unsigned 64 bit number
void print_long(struct VGAInfo*, uint64);
// Prints c-type string
void print_string(struct VGAInfo*, char*);

// ##############################################
// STDIN SECTION
// ##############################################

uint8 inb(uint16);
void outb(uint16, uint8);
// Gets input keycode from keyboard key pressed
char get_input_keycode();
/*
keep the cpu busy for doing nothing(nop)
so that io port will not be processed by cpu
here timer can also be used, but lets do this in looping counter
*/
void wait_for_io(uint32);
// Sleeps for amount of ticks
void sleep(uint32);
void test_input();

#endif