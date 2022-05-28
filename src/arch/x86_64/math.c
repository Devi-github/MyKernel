#include "math.h"

// Gives random 32 bit string of binary
uint32 __random32(uint32* seed)
{
    *seed = (((*seed) * 437823875u) + 0xf87c6f30);
    return *seed;
}
uint16 __random16(uint32* seed) {
    __random32(seed);
    return (uint16)seed;
}
uint8 __random8(uint32* seed) {
    __random32(seed);
    return (uint8)seed;
}
// Gets current clock cycles as a 64 bit number
uint64 __gcca() {
    uint32 lo, hi;
    asm volatile ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64)hi << 32) | (uint64)lo;
}