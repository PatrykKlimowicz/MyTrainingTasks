#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <papi.h>

#define NUM_LOOPS 200

int main(int argc, char *argv[])
{
    double **A;
    double *u, *v;
    long rows = 5000, columns = 5000;
    unsigned long long start_1, end_1, start_2, end_2, start_3, end_3;
    long i, j, k, l;

    // Inicjujemy wektory i macierz.
    u = (double *)malloc(columns * sizeof(double));
    v = (double *)malloc(rows * sizeof(double));

    A = (double **)malloc(rows * sizeof(double *));

    for (i = 0; i < rows; i++)
        A[i] = (double *)malloc(columns * sizeof(double));

    // Wypełniamy wektor u oraz macierz A dowolnymi wartościami.
    for (i = 0; i < columns; i++)
    {
        u[i] = (double)(i / 1000.0f);

        for (j = 0; j < rows; j++)
            A[j][i] = (double)(i * j / 1000.0f);
    }

    float arr[200] = {};
    // Pętla zewnętrzna.
    int x;
    for (k = 0, x = 0; k < NUM_LOOPS; k++, x++)
    {
        start_3 = PAPI_get_real_usec();
// Obliczamy v = A*u z wykorzystaniem dyrektyw OpenMP.
#pragma omp parallel for shared(A, v, u, rows, columns) private(i, j)
        for (i = 0; i < rows; i++)
        {
            v[i] = 0.0f;
            for (j = 0; j < columns; j++)
                v[i] = v[i] + A[i][j] * u[j];
        }
        end_3 = PAPI_get_real_usec();
        arr[x] = (float)(end_3 - start_3) / 1000000;
    }

    int a;
    for (a = 0; a < 200; ++a)
        printf("%f\n", arr[a]);

    // Zwalniamy pamięć.
    free(u);
    free(v);

    for (i = 0; i < rows; i++)
        free(A[i]);

    free(A);

    return 0;
}
