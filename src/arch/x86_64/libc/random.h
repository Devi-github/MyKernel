#ifndef RANDOM_H_
#define RANDOM_H_

#include "types.h"

void srand(uint64 seed);

// Gives random 64 bit string of binary, seed autocorrected
uint64 __random64();
// Gives random 32 bit string of binary, seed autocorrected
uint32 __random32();
// Gives random 16 bit string of binary, seed autocorrected
uint16 __random16();
// Gives random 8 bit string of binary, seed autocorrected
uint8 __random8();

#endif