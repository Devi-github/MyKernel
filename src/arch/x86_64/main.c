#include "kernel.h"
#include "keyboard.h"
#include "math.h"
#include "stdio_myos.h"
#include "errors.h"
#include "char.h"

void _cmain() {
    uint64 seed = __gcca();

    init_vga(WHITE, BLACK);

    float a = 3.14159;

    set_cursor(0);
    uint16 shrt = __random16(&seed);
    print_int(shrt);
    print_new_line();
    char str[20];
    itoa64(8844564569835, str);
    print_string(str);
    return;
}