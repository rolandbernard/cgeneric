
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "sort.h"

#define MAX(A, B) ((A) < (B) ? (B) : (A))
#define MIN(A, B) ((A) > (B) ? (B) : (A))

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

static void TYPED(introSortWithDepth)(TYPE* array, size_t size, size_t depth) {
    if (size <= MAX_INSERT_SORT) {
        TYPED(insertionSort)(array, size);
    } else if (depth == 0) {
        TYPED(heapSort)(array, size);
    } else {
        TYPED(medianOfThree)(array, 0, size / 2, size - 1);
        size_t p = TYPED(partition)(array, size / 2, size - 1);
        TYPED(introSortWithDepth)(array, p, depth - 1);
        TYPED(introSortWithDepth)(array + p + 1, size - 1 - p, depth - 1);
    }
}

static size_t TYPED(floorLog2)(size_t size) {
#if defined(__GCC__) || defined(__clang__)
    if (size == 0) {
        return 0;
    } else {
        return  63 - __builtin_clzl(size);
    }
#else
    size_t n = 0;
    while (size > 1) {
        n++;
        size /= 2;
    }
    return n;
#endif
}

void TYPED(introSort)(TYPE* array, size_t size) {
    TYPED(introSortWithDepth)(array, size, MAX_QUICK_SORT_DEPTH * TYPED(floorLog2)(size));
}

void TYPED(sort)(TYPE* array, size_t size) {
    TYPED(introSort)(array, size);
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

static void TYPED(performMergeWithBuffer)(TYPE* array, size_t k, size_t size, TYPE* buffer) {
    if (k <= size - k) {
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
    } else {
        memcpy(buffer, array + k, sizeof(TYPE) * (size - k));
        size_t i = k;
        size_t j = size;
        for (size_t h = size; h > 0;) {
            h--;
            if (j > k && (i <= 0 || LESS_EQUAL(array[i - 1], buffer[j - k - 1]))) {
                j--;
                array[h] = buffer[j - k];
            } else {
                i--;
                array[h] = array[i];
            }
        }
    }
}

static void TYPED(mergeWithBuffer)(TYPE* array, size_t k, size_t size, TYPE* buffer) {
    size_t from = TYPED(upperBound)(array, k, array[k]);
    size_t to = k + TYPED(lowerBound)(array + k, size - k, array[k - 1]);
    TYPED(performMergeWithBuffer)(array + from, k - from, to - from, buffer);
}

void TYPED(inplaceMerge)(TYPE* array, size_t k, size_t size) {
    TYPE* buffer = ALLOC(TYPE, MIN(k, size - k));
    TYPED(mergeWithBuffer)(array, k, size, buffer);
    FREE(buffer);
}

static void TYPED(mergeSortWithBuffer)(TYPE* array, TYPE* buffer, size_t size) {
    if (size <= MAX_INSERT_SORT) {
        TYPED(insertionSort)(array, size);
    } else {
        TYPED(mergeSortWithBuffer)(array, buffer, size / 2);
        TYPED(mergeSortWithBuffer)(array + size / 2, buffer, size - size / 2);
        TYPED(mergeWithBuffer)(array, size / 2, size, buffer);
    }
}

void TYPED(mergeSort)(TYPE* array, size_t size) {
    TYPE* buffer = ALLOC(TYPE, size / 2);
    TYPED(mergeSortWithBuffer)(array, buffer, size);
    FREE(buffer);
}

void TYPED(stableSort)(TYPE* array, size_t size) {
    TYPED(mergeSort)(array, size);
}

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

#undef GAP_SEQ

void TYPED(binaryInsertionSort)(TYPE* array, size_t size) {
    for (size_t i = 1; i < size; i++) {
        TYPE tmp = array[i];
        size_t j = TYPED(upperBound)(array, i, tmp);
        for (size_t k = i; k > j; k--) {
            array[k] = array[k - 1];
        }
        array[j] = tmp;
    }
}

#define STACK_LEN(N) (stack[top - N] - stack[top - 1 - N])

void TYPED(timSort)(TYPE* array, size_t size) {
    size_t off = MAX(5, TYPED(floorLog2)(size)) - 5;
    size_t minrun = size >> off;
    if (((minrun << off) ^ size) != 0) {
        minrun++;
    }
    TYPE* buffer = ALLOC(TYPE, size / 2);
    size_t* stack = ALLOC(size_t, size / minrun);
    stack[0] = 0;
    size_t top = 1;
    size_t scan = 0;
    while (scan < size) {
        size_t start = scan;
        if (scan + minrun < size) {
            scan++;
            if(!LESS_EQUAL(array[scan - 1], array[scan])) {
                scan++;
                while (scan < size && !LESS_EQUAL(array[scan - 1], array[scan])) {
                    scan++;
                }
                if (scan - start >= minrun) {
                    for (size_t i = 0; i < (scan - start) / 2; i++) {
                        TYPED(swap)(array, start + i, scan - 1 - i);
                    }
                }
            } else {
                scan++;
                while (scan < size && LESS_EQUAL(array[scan - 1], array[scan])) {
                    scan++;
                }
            }
        }
        if (scan - start < minrun) {
            scan = MIN(start + minrun, size);
            TYPED(binaryInsertionSort)(array + start, scan - start);
        }
        stack[top] = scan;
        top++;
        while (
            (top > 2 && STACK_LEN(1) >= STACK_LEN(2))
            || (top > 3 && STACK_LEN(1) + STACK_LEN(2) >= STACK_LEN(3))
        ) {
            if (top > 3 && STACK_LEN(3) < STACK_LEN(1)) {
                top--;
                size_t off = stack[top - 3];
                size_t k = stack[top - 2] - off;
                size_t n = stack[top - 1] - off;
                TYPED(mergeWithBuffer)(array + off, k, n, buffer);
                stack[top - 2] = stack[top - 1];
                stack[top - 1] = stack[top];
            } else {
                top--;
                size_t off = stack[top - 2];
                size_t k = stack[top - 1] - off;
                size_t n = stack[top] - off;
                TYPED(mergeWithBuffer)(array + off, k, n, buffer);
                stack[top - 1] = stack[top];
            }
        }
    }
    while (top > 2) {
        if (top > 3 && STACK_LEN(3) < STACK_LEN(1)) {
            top--;
            size_t off = stack[top - 3];
            size_t k = stack[top - 2] - off;
            size_t n = stack[top - 1] - off;
            TYPED(mergeWithBuffer)(array + off, k, n, buffer);
            stack[top - 2] = stack[top - 1];
            stack[top - 1] = stack[top];
        } else {
            top--;
            size_t off = stack[top - 2];
            size_t k = stack[top - 1] - off;
            size_t n = stack[top] - off;
            TYPED(mergeWithBuffer)(array + off, k, n, buffer);
            stack[top - 1] = stack[top];
        }
    }
    FREE(stack);
    FREE(buffer);
}

#undef STACK_LEN

#undef MAX
#undef MIN

