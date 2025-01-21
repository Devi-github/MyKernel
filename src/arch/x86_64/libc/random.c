#include "random.h"

static uint64 seed = 0;

void srand(uint64 sd)
{
    seed = sd;
}

uint64 __random64()
{
    seed = ((seed ^ (UINT64_MAX / 73) + 5)+ 0xf87c6f30dde4599aul);
    return seed;
}
uint32 __random32()
{
    return (uint32)__random64();
}
uint16 __random16() {
    return (uint16)__random64();
}
uint8 __random8() {
    return (uint8)__random64();
}