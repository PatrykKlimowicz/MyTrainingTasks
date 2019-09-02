#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

int * allocate(int amount)
{
    return calloc(amount, sizeof(int));
}

void print_value(int * array, int pos)
{
    printf("array[%d]=%d\n",pos, array[pos]);
}

void print_values(int * array, int amount)
{
    int i;
    for (int i=0;i<amount;++i)
        print_value(array, i);
}

void inrcease_values(int ** array, int amount, int inc)
{
    int i;
    int * buffer = allocate(amount);
    int * tmp;
    for (i=0;i<amount;++i)
        buffer[i]=array[0][i]+inc+i;

    //let's swap arrays
    tmp=*array;
    *array=buffer;
    buffer=tmp;
    free(buffer);
}


