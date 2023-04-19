#ifndef STDIO_H
#define STDIO_H
#include "kernel.h"
#include "keyboard.h"
#include "char.h"
#include "math.h"

// ##############################################
// STDOUT SECTION
// ##############################################

// VGA Entry
uint16 vga_entry(uint8, uint8, uint8);
// Sets cursor at specific index
void set_cursor(uint32);
// Sets cursor at specific coordinates
void set_cursor_coord(uint32, uint32);
// Clears VGA buffer
void clear_vga_buffer(uint16**, uint8, uint8);
/*
* Initialize VGA Text mode for screen, clears VGA buffer and sets foreground and background colors
*/
void init_vga(uint8, uint8);
// Prints new line
void print_new_line();
// Prints character on the screen
void print_char(char);
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
void print_int(uint32);
// Prints unsigned 64 bit number
void print_long(uint64);
// Prints c-type string
void print_string(char*);

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