#include "kernel.h"
#include "keyboard.h"
#include "math.h"
#include "stdio_myos.h"
#include "errors.h"
#include "char.h"

void _cmain() {
    uint64 seed = __gcca();

    init_vga(WHITE, BLACK);

    print_string("Hello                          \n");
    set_color(16, 15);
    print_string("World                          \n");
}