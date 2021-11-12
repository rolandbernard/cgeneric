
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

size_t TYPED(partition)(TYPE* array, size_t size) {
    size_t m = size / 2;
    TYPED(medianOfThree)(array, 0, m, size - 1);
    size_t i = 1;
    size_t j = size - 2;
    while (i <= j) {
        if (LESS_EQUAL(array[i], array[m])) {
            i++;
        } else if (LESS_EQUAL(array[m], array[j])) {
            j--;
        } else {
            TYPED(swap)(array, i, j);
            i++;
            j--;
        }
    }
    if (m < i) {
        TYPED(swap)(array, m, i - 1);
        return i - 1;
    } else {
        TYPED(swap)(array, m, j + 1);
        return j + 1;
    }
}

static void TYPED(introSort)(TYPE* array, size_t size, size_t depth) {
    if (size < MAX_INSERT_SORT) {
        TYPED(insertionSort)(array, size);
    } else if (depth == 0) {
        TYPED(heapSort)(array, size);
    } else {
        size_t p = TYPED(partition)(array, size);
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

