#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define ACCURACY 200000000

// Metoda Wallis'a obliczania wartosci liczby Pi bez OpenMP.
void count_pi1(double *pi)
{
    double tmp = 1.0, a_n;
    long int i, N;

    N = ACCURACY;

    for (i = 1; i <= N; i++)
    {
        a_n = (double)(4.0 * i * i / (4.0 * i * i - 1.0));
        tmp = tmp * a_n;
    }

    *pi = (double)(2.0 * tmp);
}

// Metoda Leibniza obliczania wartosci liczby Pi bez OpenMP.
void count_pi2(double *pi)
{
    double tmp = 0.0, a_n;
    long int i, N;

    N = ACCURACY;

    for (i = 0; i < N; i++)
    {
        if (i % 2 == 0)
        {
            a_n = (double)(1.0 / (2.0 * i + 1.0));
        }
        else
        {
            a_n = (double)(-1.0 / (2.0 * i + 1.0));
        }

        tmp = tmp + a_n;
    }

    *pi = (double)(4.0 * tmp);
}

// Metoda Wallis'a obliczania wartosci liczby Pi z wykorzystaniem OpenMP.
void count_pi1_omp(double *pi)
{
    double tmp = 1.0, a_n;
    long int i, N;

    N = ACCURACY;

#pragma omp parallel for default(none) shared(N) private(a_n, i) \
    reduction(*                                                  \
              : tmp)
    for (i = 1; i <= N; i++)
    {
        a_n = (double)(4.0 * i * i / (4.0 * i * i - 1.0));
        tmp = tmp * a_n;
    }

    *pi = (double)(2.0 * tmp);
}

// Metoda Leibniza obliczania wartosci liczby Pi z wykorzystaniem OpenMP.
void count_pi2_omp(double *pi)
{
    double tmp = 0.0, a_n;
    long int i, N;

    N = ACCURACY;

#pragma omp parallel for default(none) shared(N) private(a_n, i) \
    reduction(+                                                  \
              : tmp)
    for (i = 0; i < N; i++)
    {
        if (i % 2 == 0)
        {
            a_n = (double)(1.0 / (2.0 * i + 1.0));
        }
        else
        {
            a_n = (double)(-1.0 / (2.0 * i + 1.0));
        }

        tmp = tmp + a_n;
    }

    *pi = (double)(4.0 * tmp);
}

// Program glowny.
int main(int argc, char *argv[])
{
    double p1, p2;
    time_t begin_t, end_t;

    printf("Bez OpenMP:\n");

    begin_t = time(NULL);
    count_pi1(&p1);
    count_pi2(&p2);
    end_t = time(NULL);

    printf("Metoda Wallis'a Pi = %f.\n", p1);
    printf("Metoda Leibniz'a Pi = %f.\n", p2);
    printf("Czas wykonywania obliczen: %f.\n\n", difftime(end_t, begin_t));
    printf("Z OpenMP:");

    begin_t = time(NULL);
    count_pi1_omp(&p1);
    count_pi2_omp(&p2);
    end_t = time(NULL);

    printf("Metoda Wallis'a Pi = %f.\n", p1);
    printf("Metoda Leibniz'a Pi = %f.\n", p2);
    printf("Czas wykonywania obliczen: %f.\n\n", difftime(end_t, begin_t));

    return 0;
}