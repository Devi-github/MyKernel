#include "kernel.h"
#include "keyboard.h"
#include "math.h"
#include "stdio_myos.h"

uint8 digit_ascii_code[] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};
struct VGAInfo info;

void __stack_chk_fail(void) {
    print_string(&info, "ERROR: STACK_CHK_FAIL");
}

void _cmain() {
    info.next_line_index = 1;
    info.g_back_color = BLACK;
    info.g_fore_color = WHITE;

    uint32 seed = __gcca();

    init_vga(&info, WHITE, BLACK);
    print_string(&info, "Hello, world: ");
    print_int(&info, __random32(&seed) % 10);
    print_new_line(&info);
}