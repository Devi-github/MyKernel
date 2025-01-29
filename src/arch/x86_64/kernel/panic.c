#include "panic.h"
#include "kernel.h"

#include <string.h>

void kpanic(struct KernelPanicInfo *panicInfo) {
    char buffer[1024];
    
    uint64 args[] = {
        panicInfo->message
    };
    vformat(buffer, sizeof(buffer),
        "\n-----------------------------\n"
        "KERNEL PANIC: %s\n", args
        );
    kprint(buffer);

    // TODO: proper sleep-reboot procedure
    asm volatile("cli; hlt");

    for(;;); // removes noreturn warning
}
