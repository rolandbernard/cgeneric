
#include <stdint.h>

#include "hash.h"

uint64_t hashBytes(const void* mem, size_t size) {
    uint64_t hash = 7919;
    while (size > 0) {
        hash *= 293;
        hash += *(const char*)mem;
        mem++;
        size--;
    }
    return hashInt(hash);
}

uint64_t hashInt(uint64_t x) {
    x = (x ^ (x >> 30)) * UINT64_C(0xbf58476d1ce4e5b9);
    x = (x ^ (x >> 27)) * UINT64_C(0x94d049bb133111eb);
    x = x ^ (x >> 31);
    return x;
}

uint64_t hashString(const char* s) {
    uint64_t hash = 7919;
    while (*s != 0) {
        hash *= 293;
        hash += *s;
        s++;
    }
    return hashInt(hash);
}

uint64_t hashCombine(uint64_t first, uint64_t second) {
    return first ^ (second + 0x9e3779b9 + (first << 6) + (first >> 2));
}

