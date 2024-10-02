#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

extern int sum(int x0, size_t N, int *X);

int main()
{
    int x0 = 0;
    int y = 0;
    int *X = NULL;
    size_t N = 0;
    while ( scanf("%"SCNd32" %"SCNu64, &x0, &N) > 0 ) {
        X = calloc(N, sizeof *X);
        for (size_t i=0; i<N; ++i) {
            scanf("%"SCNd32, &X[i]);
        }
        y = sum(x0, N, X);
        printf("%"PRId32"\n", y);
    }
    return 0;
}
