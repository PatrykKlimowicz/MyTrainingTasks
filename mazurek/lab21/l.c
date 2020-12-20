#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <malloc.h>

#define NUM_LOOPS 1500
#define SIZE 4096 * 4096
#define alignment 256

int main(int argc, char *argv[])
{
    unsigned char *a, *b, *d;
    time_t begin_t, end_t;

    // Inicjujemy wektory i macierz.
    b = (unsigned char *)memalign(alignment, (SIZE * sizeof(unsigned char)));
    a = (unsigned char *)memalign(alignment, (SIZE * sizeof(unsigned char)));
    d = (unsigned char *)memalign(alignment, (SIZE * sizeof(unsigned char)));

    begin_t = time(NULL);
    int k, i;
    for (k = 0; k < NUM_LOOPS; k++)
        for (i = 0; i < SIZE; i++)
            d[i] = a[i] * b[i];

    end_t = time(NULL);
    printf("Czas obliczen: %f.\n", difftime(end_t, begin_t));

    // Zwalniamy pamięć.
    free(a);
    free(b);
    free(d);

    return 0;
}