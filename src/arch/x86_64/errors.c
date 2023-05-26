#include "errors.h"
#include "stdio_myos.h"

void __stack_chk_fail(void) {
    print_string("Stack overflow!");
    asm volatile ("hlt");
    //asm volatile ("jmp 0x0"); // jump to protected 0x0 meaning an error
}
void __div_by_zero(void) {
    print_string("Division by zero!");
    asm volatile ("hlt");
}