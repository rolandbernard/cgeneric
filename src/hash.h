#ifndef _HASH_H_
#define _HASH_H_

// This defines some simple hash functions

#include <stddef.h>

size_t hashBytes(const void* mem, size_t size);

size_t hashInt(size_t value);

size_t hashString(const char* s);

size_t hashCombine(size_t first, size_t second);

#endif
