#ifndef _STRING_H
#define _STRING_H

#include "types.h"

// Gets c-type string length
size_t strlen(const char*);

// Converts unsigned 32 bit integer into string and puts it into buffer
void itoa(int, char*);

// Converts unsigned 64 bit integer into string and puts it into buffer
void itoa64(uint64, char*);


#endif
