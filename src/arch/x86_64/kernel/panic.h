/*
    panic.h

    Defines kernel panic routines
*/

#ifndef _PANIC_H
#define _PANIC_H

#include <types.h>

struct KernelPanicInfo {
    const char *message;
};

void kpanic(struct KernelPanicInfo *panicInfo) __attribute__((noreturn));

#endif
