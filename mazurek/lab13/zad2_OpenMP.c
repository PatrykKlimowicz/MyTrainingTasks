// Wyniki:
// Z użyciem OpenMP: 5.247551s
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <papi.h>

#define NUM_LOOPS 100

int main(int argc, char *argv[]) {
    double **A;
    double *u, *v;
    long rows = 5000, columns = 5000;
    long i, j, k;
    unsigned long long start_usec, end_usec;
    float result;

    u = (double *)malloc(columns * sizeof(double));
    v = (double *)malloc(rows * sizeof(double));
    A = (double **)malloc(rows * sizeof(double *));

    for (i = 0; i < rows; i++)
        A[i] = (double *)malloc(columns * sizeof(double));

    for (i = 0; i < columns; i++) {
        u[i] = (double)(i / 1000.0f);

        for (j = 0; j < rows; j++)
            A[j][i] = (double)(i * j / 1000.0f);
    }

    start_usec = PAPI_get_real_usec();
    for (k = 0; k < NUM_LOOPS; k++) {
        #pragma omp parallel for shared(A, v, u, rows, columns) private(i, j)
        for (i = 0; i < rows; i++)
        {
            v[i] = 0.0f;
            for (j = 0; j < columns; j++)
                v[i] = v[i] + A[i][j] * u[j];
        }
    }
    end_usec = PAPI_get_real_usec();
    result = end_usec - start_usec;

    printf("Z użyciem OpenMP: %fs\n", result / 1000000);

    free(u);
    free(v);

    for (i = 0; i < rows; i++)
        free(A[i]);

    free(A);

    return 0;
}
