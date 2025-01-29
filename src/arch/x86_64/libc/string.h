#ifndef _STRING_H
#define _STRING_H

#include "types.h"

// Gets c-type string length
size_t strlen(const char*);

// Converts unsigned 32 bit integer into string and puts it into buffer
// Returns number of bytes written
size_t itoa(int, char*);

// Converts unsigned 64 bit integer into string and puts it into buffer
size_t itoa64(uint64, char*);

void memcpy(void *dst, const void *src, size_t len);

size_t vformat(char *buffer, size_t buffer_size, const char *fmt, void *args);

#endif
