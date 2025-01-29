#include "panic.h"

#include "../driver/vga/vga.h"

void kpanic(struct KernelPanicInfo *panicInfo) {
    vga_putcs("KERNEL PANIC: ");
    vga_putcs(panicInfo->message);

    // TODO: proper sleep-reboot procedure
    asm volatile("cli; hlt");
}
