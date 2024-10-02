#include <stdint.h>

extern int *A;

extern void shrink(int64_t value) {
    volatile int32_t x;
    x = A[value];
}
