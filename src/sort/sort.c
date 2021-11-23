
#include <stddef.h>
#include <string.h>

#include "sort.h"

void TYPED(swap)(TYPE* array, size_t i, size_t j) {
    TYPE tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}

void TYPED(insertionSort)(TYPE* array, size_t size) {
    for (size_t i = 1; i < size; i++) {
        TYPE tmp = array[i];
        size_t j = i;
        while (j > 0 && !LESS_EQUAL(array[j - 1], tmp)) {
            array[j] = array[j - 1];
            j--;
        }
        array[j] = tmp;
    }
}

void TYPED(heapify)(TYPE* array, size_t i, size_t size) {
    size_t left = 2 * (i + 1) - 1;
    size_t right = 2 * (i + 1);
    size_t max = i;
    if (left < size && !LESS_EQUAL(array[left], array[max])) {
        max = left;
    }
    if (right < size && !LESS_EQUAL(array[right], array[max])) {
        max = right;
    }
    if (max != i) {
        TYPED(swap)(array, max, i);
        TYPED(heapify)(array, max, size);
    }
}

void TYPED(buildHeap)(TYPE* array, size_t size) {
    for (size_t i = size / 2; i > 0;) {
        i--;
        TYPED(heapify)(array, i, size);
    }
}

void TYPED(heapSort)(TYPE* array, size_t size) {
    TYPED(buildHeap)(array, size);
    for (size_t i = 0; i < size; i++) {
        TYPED(swap)(array, 0, size - 1 - i);
        TYPED(heapify)(array, 0, size - 1 - i);
    }
}

size_t TYPED(partition)(TYPE* array, size_t k, size_t size) {
    size_t i = 0;
    size_t j = size - 1;
    while (i <= j) {
        if (LESS_EQUAL(array[i], array[k])) {
            i++;
        } else if (LESS_EQUAL(array[k], array[j])) {
            j--;
        } else {
            TYPED(swap)(array, i, j);
            i++;
            j--;
        }
    }
    if (k < i) {
        TYPED(swap)(array, k, i - 1);
        return i - 1;
    } else {
        TYPED(swap)(array, k, j + 1);
        return j + 1;
    }
}

static void TYPED(medianOfThree)(TYPE* array, size_t left, size_t mid, size_t right) {
    if (!LESS_EQUAL(array[left], array[right])) {
        TYPED(swap)(array, left, right);
    }
    if (!LESS_EQUAL(array[left], array[mid])) {
        TYPED(swap)(array, left, mid);
    }
    if (!LESS_EQUAL(array[mid], array[right])) {
        TYPED(swap)(array, mid, right);
    }
}

void TYPED(quickSort)(TYPE* array, size_t size) {
    if (size <= MAX_INSERT_SORT) {
        TYPED(insertionSort)(array, size);
    } else {
        TYPED(medianOfThree)(array, 0, size / 2, size - 1);
        size_t p = TYPED(partition)(array, size / 2, size);
        TYPED(quickSort)(array, p);
        TYPED(quickSort)(array + p + 1, size - 1 - p);
    }
}

static void TYPED(introSort)(TYPE* array, size_t size, size_t depth) {
    if (size <= MAX_INSERT_SORT) {
        TYPED(insertionSort)(array, size);
    } else if (depth == 0) {
        TYPED(heapSort)(array, size);
    } else {
        TYPED(medianOfThree)(array, 0, size / 2, size - 1);
        size_t p = TYPED(partition)(array, size / 2, size - 1);
        TYPED(introSort)(array, p, depth - 1);
        TYPED(introSort)(array + p + 1, size - 1 - p, depth - 1);
    }
}

static size_t TYPED(floorLog2)(size_t size) {
    size_t n = 0;
    while (size > 1) {
        n++;
        size /= 2;
    }
    return n;
}

void TYPED(sort)(TYPE* array, size_t size) {
    TYPED(introSort)(array, size, MAX_QUICK_SORT_DEPTH * TYPED(floorLog2)(size));
}

void TYPED(quickSelect)(TYPE* array, size_t k, size_t size) {
    if (size > 1) {
        TYPED(medianOfThree)(array, 0, size / 2, size - 1);
        size_t p = TYPED(partition)(array, size / 2, size);
        if (k < p) {
            TYPED(quickSelect)(array, k, p);
        } else if (k > p) {
            TYPED(quickSelect)(array + p + 1, k - p - 1, size - p - 1);
        }
    }
}

void TYPED(medianSelect)(TYPE* array, size_t k, size_t size) {
    if (size > 1) {
        size_t p = 0; //TYPED(medianPivot)(array, size);
        p = TYPED(partition)(array, p, size);
        if (k < p) {
            TYPED(medianSelect)(array, k, p);
        } else if (k > p) {
            TYPED(medianSelect)(array + p + 1, k - p - 1, size - p - 1);
        }
    }
}

static size_t TYPED(smallPivot)(TYPE* array, size_t size) {
    TYPED(insertionSort)(array, size);
    return size / 2;
}

size_t TYPED(medianPivot)(TYPE* array, size_t size) {
    if (size < 5) {
        return TYPED(smallPivot)(array, size);
    } else {
        for (size_t i = 0; i < size; i += 5) {
            size_t r = i + 5;
            if (r > size) {
                r = size;
            }
            size_t median5 = i + TYPED(smallPivot)(array + i, r - i);
            TYPED(swap)(array, median5, i / 5);
        }
        TYPED(medianSelect)(array, size / 10, size / 5);
        return size / 10;
    }
}

size_t TYPED(upperBound)(TYPE* array, size_t size, TYPE value) {
    size_t i = 0;
    size_t j = size;
    while (i != j) {
        size_t h = (i + j) / 2;
        if (!LESS_EQUAL(array[h], value)) {
            j = h;
        } else {
            i = h + 1;
        }
    }
    return i;
}

size_t TYPED(lowerBound)(TYPE* array, size_t size, TYPE value) {
    size_t i = 0;
    size_t j = size;
    while (i != j) {
        size_t h = (i + j) / 2;
        if (LESS_EQUAL(value, array[h])) {
            j = h;
        } else {
            i = h + 1;
        }
    }
    return i;
}

static void TYPED(mergeWithBuffer)(TYPE* array, TYPE* buffer, size_t k, size_t size) {
    memcpy(buffer, array, sizeof(TYPE) * k);
    size_t i = 0;
    size_t j = k;
    for (size_t h = 0; h < size; h++) {
        if (i < k && (j >= size || LESS_EQUAL(buffer[i], array[j]))) {
            array[h] = buffer[i];
            i++;
        } else {
            array[h] = array[j];
            j++;
        }
    }
}

void TYPED(inplaceMerge)(TYPE* array, size_t k, size_t size) {
    TYPE* buffer = ALLOC(TYPE, k);
    TYPED(mergeWithBuffer)(array, buffer, k, size);
    FREE(buffer);
}

static void TYPED(mergeSortWithBuffer)(TYPE* array, TYPE* buffer, size_t size) {
    if (size <= MAX_INSERT_SORT) {
        TYPED(insertionSort)(array, size);
    } else {
        TYPED(mergeSortWithBuffer)(array, buffer, size / 2);
        TYPED(mergeSortWithBuffer)(array + size / 2, buffer, size - size / 2);
        TYPED(mergeWithBuffer)(array, buffer, size / 2, size);
    }
}

void TYPED(stableSort)(TYPE* array, size_t size) {
    TYPE* buffer = ALLOC(TYPE, size / 2);
    TYPED(mergeSortWithBuffer)(array, buffer, size);
    FREE(buffer);
}

#define MAX(A, B) ((A) < (B) ? (B) : (A))
#define GAP_SEQ(N) MAX((5 * N - 1) / 11, 1)

void TYPED(shellSort)(TYPE* array, size_t size) {
    size_t gap = size;
    do {
        gap = GAP_SEQ(gap);
        for (size_t offset = 0; offset < gap; offset++) {
            for (size_t i = offset; i < size; i += gap) {
                TYPE tmp = array[i];
                size_t j = i;
                while (j >= gap && !LESS_EQUAL(array[j - gap], tmp)) {
                    array[j] = array[j - gap];
                    j -= gap;
                }
                array[j] = tmp;
            }
        }
    } while (gap > 1);
}

#undef MAX

