/*
========================================
Algorytm blokujacy to algorytm Leibniz'a
========================================

[12:29:59]  [patryk@patryk: ~/mazurek/lab8 $]  [  ]
  **** ./l 
Metoda Wallis'a Pi = 3.141593 - obliczenia wykonane przez watek nr. 2.
Metoda Leibniz'a Pi = 3.141593 - obliczenia wykonane przez watek nr. 0.
Czas wykonywania obliczen: 
Wallis: 1.000000
Leibniz: 3.000000

[12:30:03]  [patryk@patryk: ~/mazurek/lab8 $]  [  ]
  **** ./l 
Metoda Wallis'a Pi = 3.141593 - obliczenia wykonane przez watek nr. 1.
Metoda Leibniz'a Pi = 3.141593 - obliczenia wykonane przez watek nr. 0.
Czas wykonywania obliczen: 
Wallis: 0.000000
Leibniz: 2.000000

[12:30:07]  [patryk@patryk: ~/mazurek/lab8 $]  [  ]
  **** ./l 
Metoda Wallis'a Pi = 3.141593 - obliczenia wykonane przez watek nr. 1.
Metoda Leibniz'a Pi = 3.141593 - obliczenia wykonane przez watek nr. 3.
Czas wykonywania obliczen: 
Wallis: 1.000000
Leibniz: 2.000000

[12:30:12]  [patryk@patryk: ~/mazurek/lab8 $]  [  ]
  **** ./l 
Metoda Wallis'a Pi = 3.141593 - obliczenia wykonane przez watek nr. 1.
Metoda Leibniz'a Pi = 3.141593 - obliczenia wykonane przez watek nr. 0.
Czas wykonywania obliczen: 
Wallis: 1.000000
Leibniz: 3.000000

[12:30:20]  [patryk@patryk: ~/mazurek/lab8 $]  [  ]
  ****

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define ACCURACY 200000000

// Metoda Wallis'a obliczania wartosci liczby Pi.
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

// Metoda Leibniza obliczania wartosci liczby Pi.
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

// Program glowny.
int main(int argc, char *argv[])
{
    double tmp1, tmp2;
    double p1, p2;
    time_t begin_t, end_t;
    float czas_1, czas_2;

#pragma omp parallel sections private(p1, p2)
    {

#pragma omp section
        {
            begin_t = time(NULL);
            count_pi1(&p1);
            printf("Metoda Wallis'a Pi = %f - obliczenia wykonane przez "
                   "watek nr. %d.\n",
                   p1, omp_get_thread_num());
            end_t = time(NULL);
            czas_1 = difftime(end_t, begin_t);
        }

#pragma omp section
        {
            begin_t = time(NULL);
            count_pi2(&p2);
            printf("Metoda Leibniz'a Pi = %f - obliczenia wykonane przez "
                   "watek nr. %d.\n",
                   p2, omp_get_thread_num());
            end_t = time(NULL);
            czas_2 = difftime(end_t, begin_t);
        }
    }

    printf("Czas wykonywania obliczen: \nWallis: %f\nLeibniz: %f\n", czas_1, czas_2);

    return 0;
}
