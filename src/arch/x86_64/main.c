#include "stdio_myos.h"
#include "random.h"
#include "kernel.h"

void get_chars() {
    bool first = true;
    while(1) {
        putc(stdout, getc(stdin));
        if(first) {
            sleep(100000000);
            first = false;
        } else {
            sleep(10000000);
        }
    }
}

void _cmain() {
    init_vga(C_WHITE, C_BLACK);

    puts(stdout, "Hello, world!\n");

    get_chars();

    return;
}