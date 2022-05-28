#include "math.h"
#include "errors.h"

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
uint64 __gcca() {
    uint32 lo, hi;
    asm volatile ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64)hi << 32) | (uint64)lo;
}