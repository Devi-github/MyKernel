#include "keyboard.h"
#include "random.h"
#include "kernel.h"
#include "../driver/vga/vga.h"

uint64 __gcca() {
    uint32 lo, hi;
    asm volatile ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64)hi << 32) | (uint64)lo;
}

void _cmain() {
    vga_init(C_WHITE, C_BLACK);

    vga_putcs("Welcome to MyKernel!\n");
}
