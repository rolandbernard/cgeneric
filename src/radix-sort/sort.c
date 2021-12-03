
#include "sort.h"

void TYPED(radixSwap)(TYPE* array, size_t i, size_t j) {
    TYPE tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}

static void TYPED(radixSortDepth)(TYPE* array, size_t size, size_t depth) {
#ifndef REVERSED_KEYS
#ifndef VARIABLE_LENGTH
    size_t length = LENGTH;
#else
    size_t length = 0;
    for (size_t i = 0; i < size; i++) {
        if (LENGTH(array[i]) > length) {
            length = LENGTH(array[i]);
        }
    }
#endif
    if (size > 1 && depth < length) {
#else
    if (size > 1 && depth > 0) {
        depth--;
#endif
        size_t counts[KEY_SIZE];
        for (size_t i = 0; i < KEY_SIZE; i++) {
            counts[i] = 0;
        }
        for (size_t i = 0; i < size; i++) {
            counts[GET_KEY(array[i], depth)]++;
        }
        size_t prefix[KEY_SIZE];
        prefix[0] = 0;
        for (size_t i = 1; i < KEY_SIZE; i++) {
            prefix[i] = prefix[i - 1] + counts[i - 1];
        }
        for (size_t j = 0; j < KEY_SIZE; j++) {
            for (size_t i = prefix[j]; i < prefix[j] + counts[j];) {
                size_t key = GET_KEY(array[i], depth);
                if (prefix[key] != i) {
                    TYPED(radixSwap)(array, i, prefix[key]);
                } else {
                    i++;
                }
                counts[key]--;
                prefix[key]++;
            }
        }
        size_t last = 0;
        for (size_t i = 0; i < KEY_SIZE; i++) {
#ifndef REVERSED_KEYS
            TYPED(radixSortDepth)(array + last, prefix[i] - last, depth + 1);
#else
            TYPED(radixSortDepth)(array + last, prefix[i] - last, depth);
#endif
            last = prefix[i];
        }
    }
}

void TYPED(radixSort)(TYPE* array, size_t size) {
#ifndef REVERSED_KEYS
    TYPED(radixSortDepth)(array, size, 0);
#else
#ifndef VARIABLE_LENGTH
    size_t length = LENGTH;
#else
    size_t length = 0;
    for (size_t i = 0; i < size; i++) {
        if (LENGTH(array[i]) > length) {
            length = LENGTH(array[i]);
        }
    }
#endif
    TYPED(radixSortDepth)(array, size, length);
#endif
}

static void TYPED(stableRadixSortDepth)(TYPE* array, size_t size, TYPE* buffer, size_t depth) {
#ifndef VARIABLE_LENGTH
    size_t length = LENGTH;
#else
    size_t length = 0;
    for (size_t i = 0; i < size; i++) {
        if (LENGTH(array[i]) > length) {
            length = LENGTH(array[i]);
        }
    }
#endif
    if (size > 1 && depth < length) {
        size_t counts[KEY_SIZE + 1];
        for (size_t i = 0; i <= KEY_SIZE; i++) {
            counts[i] = 0;
        }
        for (size_t i = 0; i < size; i++) {
            counts[GET_KEY(array[i], depth) + 1]++;
            buffer[i] = array[i];
        }
        for (size_t i = 2; i <= KEY_SIZE; i++) {
            counts[i] += counts[i - 1];
        }
        for (size_t i = 0; i < size; i++) {
            size_t key = GET_KEY(buffer[i], depth);
            array[counts[key]] = buffer[i];
            counts[key]++;
        }
        size_t last = 0;
        for (size_t i = 0; i < KEY_SIZE; i++) {
            TYPED(stableRadixSortDepth)(array + last, counts[i] - last, buffer, depth + 1);
            last = counts[i];
        }
    }
}

void TYPED(stableRadixSort)(TYPE* array, size_t size) {
    TYPE* buffer = ALLOC(TYPE, size);
#ifndef REVERSED_KEYS
    TYPED(stableRadixSortDepth)(array, size, buffer, 0);
#else
#ifndef VARIABLE_LENGTH
    size_t length = LENGTH;
#else
    size_t length = 0;
    for (size_t i = 0; i < size; i++) {
        if (LENGTH(array[i]) > length) {
            length = LENGTH(array[i]);
        }
    }
#endif
    for (size_t j = 0; j < length; j++) {
        size_t counts[KEY_SIZE + 1];
        for (size_t i = 0; i <= KEY_SIZE; i++) {
            counts[i] = 0;
        }
        for (size_t i = 0; i < size; i++) {
            counts[GET_KEY(array[i], j) + 1]++;
            buffer[i] = array[i];
        }
        for (size_t i = 2; i <= KEY_SIZE; i++) {
            counts[i] += counts[i - 1];
        }
        for (size_t i = 0; i < size; i++) {
            size_t key = GET_KEY(buffer[i], j);
            array[counts[key]] = buffer[i];
            counts[key]++;
        }
    }
#endif
    FREE(buffer);
}

