#ifndef ARRAY2_H
#define ARRAY2_H
/* Simple 2D array with a head element so that a[x][y] works without a stroke.
 * All done in a sinle allocation, with only a slight memory overhead.
 */

#include <stdlib.h>

#define a2_t(T) T * *

#define a2_init(T, a, x, y) do {             \
    T * b = (T*)malloc((sizeof(T*) * x)      \
                             + (x            \
                               * y           \
                               * sizeof(T)   \
                               )             \
    );                                       \
    a = (T**)b;                              \
    for (size_t i = 0; i < (size_t)x; i++) { \
        a[i] = (T*)((char*)b                 \
                  + (sizeof(T*) * x)         \
                  + (sizeof(T) * i * y));    \
    }                                        \
} while (0)

#define a2_destroy(a) free(a)

#endif
