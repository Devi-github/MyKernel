#include "errors.h"

void __stack_chk_fail(void) {
    asm volatile ("jmp 0x0"); // jump to protected 0x0 meaning an error
}
void __div_by_zero(void) {
    asm volatile ("jmp 0x0");
}