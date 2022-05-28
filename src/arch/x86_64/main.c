#include "kernel.h"
#include "keyboard.h"
#include "math.h"
#include "stdio_myos.h"
#include "errors.h"

uint8 digit_ascii_code[] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};
struct VGAInfo info;

void _cmain() {
    uint32 seed = __gcca();

    info.next_line_index = 1;
    info.g_back_color = BLACK;
    info.g_fore_color = WHITE;

    init_vga(&info, WHITE, BLACK);
    print_int(&info, seed);
}