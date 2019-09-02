#include <stdlib.h>
#include "functions.h"

// just playing with our functions
void what_a_magical_values(void)
{
    int * values,i;

    values=allocate(TABLE_SIZE);
    i = 666;
    values[8]=TABLE_SIZE;
    values[9]=i;

    print_values(values,TABLE_SIZE);

    inrcease_values(&values,TABLE_SIZE, 10);
    
    print_values(values,TABLE_SIZE);
    free(values);
}

int main(int argc, const char *argv[])
{
    what_a_magical_values();
    return EXIT_SUCCESS;
}
