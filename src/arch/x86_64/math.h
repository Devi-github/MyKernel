#ifndef MATH_H
#define MATH_H
#include "kernel.h"

// Gives random 64 bit string of binary, seed autocorrected
uint64 __random64(uint64*);
// Gives random 32 bit string of binary, seed autocorrected
uint32 __random32(uint32*);
// Gives random 16 bit string of binary, seed autocorrected
uint16 __random16(uint32*);
// Gives random 8 bit string of binary, seed autocorrected
uint8 __random8(uint32*);
// Gets current clock cycles as a 64 bit number
uint64 __gcca();

#endif