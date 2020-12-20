#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

#define NUM_LOOPS 1024 * 100
#define SIZE 1024 * 128
#define alignment 256

int main(int argc, char *argv[])
{
    float *a, *b, *d;
    time_t begin_t, end_t;
    int k, i;
    // Inicjujemy wektory i macierz.
    a = (float *)memalign(alignment, (SIZE * sizeof(float)));
    b = (float *)memalign(alignment, (SIZE * sizeof(float)));
    d = (float *)memalign(alignment, (SIZE * sizeof(float)));

    begin_t = time(NULL);
    // #pragma omp simd aligned(a, b, d \
                        //  : alignment)
    for (k = 0; k < NUM_LOOPS; k++)
        for (i = 0; i < SIZE; i++)
            d[i] += a[i] * b[i];

    end_t = time(NULL);
    printf("Czas obliczen: %f.\n", difftime(end_t, begin_t));

    // Zwalniamy pamięć.
    free(a);
    free(b);
    free(d);

    return 0;
}