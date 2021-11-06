
#include <stdlib.h>

#ifndef ALLOC
#define ALLOC(TYPE, SIZE) malloc((SIZE) * sizeof(TYPE))
#endif

#ifndef ZALLOC
#define ZALLOC(TYPE, SIZE) calloc(SIZE, sizeof(TYPE))
#endif

#ifndef REALLOC
#define REALLOC(TYPE, PTR, SIZE) realloc(PTR, (SIZE) * sizeof(TYPE))
#endif

#ifndef FREE
#define FREE(PTR) free(PTR)
#endif

