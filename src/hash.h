#ifndef _HASH_H_
#define _HASH_H_

// This defines some simple hash functions

#include <stddef.h>
#include <stdint.h>

uint64_t hashBytes(const void* mem, size_t size);

uint64_t hashInt(uint64_t value);

uint64_t hashString(const char* s);

uint64_t hashCombine(uint64_t first, uint64_t second);

#endif
