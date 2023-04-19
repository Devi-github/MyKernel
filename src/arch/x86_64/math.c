#include "math.h"
#include "errors.h"

uint64 __random64(uint64* seed) {
    *seed = ((*seed ^ (UINT64_MAX / 73) + 5)+ 0xf87c6f30dde4599aul);
    return *seed;
}
uint32 __random32(uint32* seed)
{
    *seed = (((*seed) * 437823875u) + 0xf87c6f30);
    return *seed;
}
uint16 __random16(uint32* seed) {
    __random32(seed);
    return (uint16)*seed;
}
uint8 __random8(uint32* seed) {
    __random32(seed);
    return (uint8)*seed;
}
uint64 __gcca() {
    uint32 lo, hi;
    asm volatile ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((uint64)hi << 32) | (uint64)lo;
}