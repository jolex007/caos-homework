#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int* A;

extern void very_important_function(size_t N);

int main()
{
    size_t N = 0;
    scanf("%"SCNu64, &N);
    
    A = calloc(N, sizeof(*A));
    
    for (size_t i = 0; i < N; ++i) {
        scanf("%"SCNd32, &A[i]);
    }

    very_important_function(N);
    
    free(A);
    printf("\n");

    return 0;
}
