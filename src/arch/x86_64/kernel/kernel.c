#include "keyboard.h"
#include "random.h"
#include "kernel.h"
#include "panic.h"
#include "idt.h"

#include <string.h>

#include "../driver/vga/vga.h"

uint64 __gcca() {
    uint32 lo, hi;
    asm volatile ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64)hi << 32) | (uint64)lo;
}

__attribute__((noreturn))
void _cmain() {
    vga_init(C_WHITE, C_BLACK);

    vga_putcs("Welcome to MyKernel!\n");

    load_idt();

    vga_putcs("Interrupts enabled.\n");

    char numtest_buffer[64];
    uint64 args[] = {
        12345678
    };

    vformat(numtest_buffer, sizeof(numtest_buffer), "Number test: %d", (void*)args);

    kprint(numtest_buffer);

    for(;;) {}
}

void kprint(const char *message) {
    vga_putcs(message);
    vga_putc('\n');
}
