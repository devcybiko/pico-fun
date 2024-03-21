#ifndef __GDefines__
#define __GDefines__


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>
#include <time.h>

#define FREE(PTR) free(PTR)
#define NEW(TYPE) (TYPE *) calloc(1, sizeof(TYPE))
#define CALLOC(N, TYPE) (TYPE *)calloc(N, sizeof(TYPE));
#define MALLOC(N, TYPE) (TYPE *)malloc(N * sizeof(TYPE));
#define REALLOC(PTR, N) realloc(PTR, N * sizeof(*PTR));
#define FUNC(RET, NAME, ...) RET (*NAME)(__VA_ARGS__)

#define STRINGIZE(x) #x

#endif // __GDefines__