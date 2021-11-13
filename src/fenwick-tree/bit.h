
#include "default.h"
#include <stddef.h>

void TYPED(addToBit)(TYPE* array, size_t size, size_t i, TYPE v);

void TYPED(removeFromBit)(TYPE* array, size_t size, size_t i, TYPE v);

TYPE TYPED(getFromBit)(TYPE* array, size_t i);

void TYPED(setToBit)(TYPE* array, size_t size, size_t i, TYPE v);

TYPE TYPED(prefixSumInBit)(TYPE* array, size_t to);

TYPE TYPED(sumOfBitRange)(TYPE* array, size_t from, size_t to);

