
#include "bit.h"

#define LSB(N) ((N) & -(N))

TYPE* TYPED(createBit)(size_t size) {
    TYPE* values = ALLOC(TYPE, size);
    TYPED(initBit)(values, size);
    return values;
}

void TYPED(initBit)(TYPE* array, size_t size) {
    for (size_t i = 0; i < size; i++) {
        array[i] = ZERO;
    }
}

void TYPED(addToBit)(TYPE* array, size_t size, size_t i, TYPE v) {
    while (i < size) {
        array[i] = ADDITION(array[i], v);
        i += LSB(i + 1);
    }
}

void TYPED(removeFromBit)(TYPE* array, size_t size, size_t i, TYPE v) {
    while (i < size) {
        array[i] = SUBTRACTION(array[i], v);
        i += LSB(i + 1);
    }
}

TYPE TYPED(getFromBit)(TYPE* array, size_t i) {
    return TYPED(sumOfBitRange)(array, i, i + 1);
}

void TYPED(setToBit)(TYPE* array, size_t size, size_t i, TYPE v) {
    TYPE value = TYPED(getFromBit)(array, i);
    TYPED(addToBit)(array, size, i, SUBTRACTION(v, value));
}

TYPE TYPED(prefixSumInBit)(TYPE* array, size_t to) {
    TYPE sum = array[to];
    while (to >= LSB(to + 1)) {
        to -= LSB(to + 1);
        sum = ADDITION(sum, array[to]);
    }
	return sum;
}

TYPE TYPED(sumOfBitRange)(TYPE* array, size_t from, size_t to) {
    if (to == 0) {
        return ZERO;
    } else if (from == 0) {
        return TYPED(prefixSumInBit)(array, to - 1);
    } else {
        return SUBTRACTION(TYPED(prefixSumInBit)(array, to - 1), TYPED(prefixSumInBit)(array, from - 1));
    }
}

#undef LSB

