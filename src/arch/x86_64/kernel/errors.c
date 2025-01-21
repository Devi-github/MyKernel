#include "errors.h"
#include "../driver/vga/vga.h"

void __stack_chk_fail(void) {
    char errors_string[] = "Stack overflow!";
    vga_puts(errors_string, sizeof(errors_string));
    asm volatile (
        "cli\n"
        "hlt"
    );
}

void __div_by_zero(void) {
    char errors_string[] = "Stack overflow!";
    vga_puts(errors_string, sizeof(errors_string));
    asm volatile (
        "cli\n"
        "hlt"
    );
}
