
#include "default.h"
#include <stddef.h>

void TYPED(swap)(TYPE* array, size_t i, size_t j);

void TYPED(insertionSort)(TYPE* array, size_t size);

void TYPED(heapify)(TYPE* array, size_t i, size_t size);

void TYPED(buildHeap)(TYPE* array, size_t size);

void TYPED(heapSort)(TYPE* array, size_t size);

size_t TYPED(partition)(TYPE* array, size_t k, size_t size);

void TYPED(quickSort)(TYPE* array, size_t size);

void TYPED(introSort)(TYPE* array, size_t size);

void TYPED(sort)(TYPE* array, size_t size);

void TYPED(quickSelect)(TYPE* array, size_t k, size_t size);

void TYPED(medianSelect)(TYPE* array, size_t k, size_t size);

size_t TYPED(medianPivot)(TYPE* array, size_t size);

size_t TYPED(upperBound)(TYPE* array, size_t size, TYPE value);

size_t TYPED(lowerBound)(TYPE* array, size_t size, TYPE value);

void TYPED(inplaceMerge)(TYPE* array, size_t k, size_t size);

void TYPED(mergeSort)(TYPE* array, size_t size);

void TYPED(stableSort)(TYPE* array, size_t size);

void TYPED(shellSort)(TYPE* array, size_t size);

void TYPED(binaryInsertionSort)(TYPE* array, size_t size);

void TYPED(timSort)(TYPE* array, size_t size);

