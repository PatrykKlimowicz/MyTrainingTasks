#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define ACCURACY 2000000
#define CHUNK_SIZE 1


int main(int argc, char *argv[])
{
    double pi;
    time_t begin_t, end_t;
    double tmp = 1.0, a_n;
    long int i;


    begin_t = time(NULL);
    #pragma omp for schedule(static, CHUNK_SIZE)
    for (i = 1; i <= ACCURACY; i++) {
        a_n = (double)(4.0*i*i / (4.0*i*i - 1.0));
        tmp = tmp * a_n;
    }

    pi = (double)(2.0 * tmp);
    end_t = time(NULL);
    printf("Metoda Wallis'a Pi = %f\n", pi);
  

    printf("Czas wykonywania: %f.\n\n", difftime(end_t, begin_t));

    return 0;
}