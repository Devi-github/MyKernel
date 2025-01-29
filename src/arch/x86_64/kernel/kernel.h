#ifndef KERNEL_H
#define KERNEL_H

#include "types.h"

// Gets current clock cycles as a 64 bit number
uint64 __gcca();

void kprint(const char *);

#endif
