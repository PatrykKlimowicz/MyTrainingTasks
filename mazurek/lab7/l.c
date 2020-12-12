/*
Dla programu step_0403.c wykonać:
--- pomiary czasu wykonywania dla gromadzenia danych za pomocą reduction --- Dla Leibniza i Willisa
--- czasy wykonywania dla gromadzenia danych w tabeli (za pomoca tmp[i]) oraz sumowania wyniku poza #pragma for. 

Wyniki: 
2 z reduction      -|
                    |--- umieścić w dostarczonym kodzie.
dwa bez reduction  -|

Sugestia - zrobić sobie funcje count_pi3 count_pi4 dla wariantu z tabelą. 
Tabele zrobić jako zmienną globalną, a nie lokalną w funkcji.

========================================
============== WYNIKI ==================
========================================
Bez OpenMP:

Czas wpisywania do tablicy Wallis: 
4.000000
Czas sumowania tablicy Wallis: 
suma: 2.000000
Czas wpisywania do tablicy Leibnitz: 
6.000000
Czas sumowania tablicy Leibnitz: 
2.000000

Z OpenMP:

Metoda Wallis'a Pi = 3.141593.
Metoda Leibniz'a Pi = 3.141593.
Czas wykonywania obliczen: 
Wallis: 0.000000
Leibnitz: 1.000000
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <string.h>

#define ACCURACY 600000000
double array[ACCURACY] = {0};

// Metoda Wallis'a obliczania wartosci liczby Pi bez OpenMP.
void count_pi1()
{
    double tmp = 1.0, a_n;
    array[0] = tmp;
    long int i, N;

    N = ACCURACY;

    for (i = 1; i <= N; i++)
    {
        a_n = (double)(4.0 * i * i / (4.0 * i * i - 1.0));
        array[i] = a_n;
    }
}

// Metoda Leibniza obliczania wartosci liczby Pi bez OpenMP.
void count_pi2()
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

        array[i] = a_n;
    }
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
    float czas_1, czas_2;
    double suma = 0;
    float czas_sumowania;

    printf("Bez OpenMP:\n");

    begin_t = time(NULL);
    count_pi1();
    end_t = time(NULL);
    printf("Czas wpisywania do tablicy Wallis: \n%f\n", difftime(end_t, begin_t));

    begin_t = time(NULL);
    for (int i = 0; i < ACCURACY; ++i)
    {
        suma += array[i];
    }
    end_t = time(NULL);
    czas_sumowania = difftime(end_t, begin_t);
    printf("Czas sumowania tablicy Wallis: \nsuma: %f\n", czas_sumowania);

    memset(array, 0, sizeof(array));
    /* ========================================== */
    /* ========================================== */
    /* ========================================== */

    begin_t = time(NULL);
    count_pi2();
    end_t = time(NULL);
    printf("Czas wpisywania do tablicy Leibnitz: \n%f\n", difftime(end_t, begin_t));

    begin_t = time(NULL);
    suma = 0;
    for (int i = 0; i < ACCURACY; ++i)
    {
        suma += array[i];
    }
    end_t = time(NULL);
    czas_sumowania = difftime(end_t, begin_t);
    printf("Czas sumowania tablicy Leibnitz: \n%f\n", czas_sumowania);

    /* ========================================== */
    /* ========================================== */
    /* ========================================== */

    printf("Z OpenMP:");

    begin_t = time(NULL);
    count_pi1_omp(&p1);
    end_t = time(NULL);
    czas_1 = difftime(end_t, begin_t);

    begin_t = time(NULL);
    count_pi2_omp(&p2);
    end_t = time(NULL);
    czas_2 = difftime(end_t, begin_t);

    printf("Metoda Wallis'a Pi = %f.\n", p1);
    printf("Metoda Leibniz'a Pi = %f.\n", p2);
    printf("Czas wykonywania obliczen: \nWallis: %f\nLeibnitz: %f\n", czas_1, czas_2);

    return 0;
}
