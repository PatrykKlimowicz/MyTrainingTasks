#include <stdio.h>
#include <stdlib.h>

#include "mult.h"

int main(int argc, const char *argv[]) {
    
    printf("Result: %d\n", multiply(atoi(argv[1]), atoi(argv[2])));

    return 0;
}
