/*
    VGA text mode driver.
*/

#ifndef _VGA_DRIVER_H
#define _VGA_DRIVER_H

#include <types.h>

/// @brief Computes an entry into a VGA buffer
/// @param character Character to input
/// @param foreground Foreground color
/// @param background Background color
/// @return Returns a low-level entry into vga
uint16 vga_entry(uint8 character, uint8 foreground, uint8 background);

// Sets cursor at specific index
void vga_set_cursor_index(uint32);

// Sets cursor at specific coordinates
void vga_set_cursor_coord(uint32, uint32);

/*
* Initialize VGA Text mode for screen, clears VGA buffer and sets foreground and background colors
*/
void vga_init(uint8 bg, uint8 fg);

/// Sets foreground and background colors for next entries
void vga_set_color(uint8 foreground, uint8 background);

void vga_puts(const char *, size_t);
void vga_putc(char);
void vga_putcs(const char *);

#endif
