#include <stdlib.h>
#include <assert.h>
#include <stdio.h>


#define STR(x) #x

#define MACRO(x) (x ? printf("\n") : printf("ERROR!\nFile name: %s\nFunction name: %s\nLine: %d\nCase: %s\n", __FILE__, __PRETTY_FUNCTION__, __LINE__, STR(x)))


int multiply(int a, int b) {
    return a*b;
}

int main(int argc, const char *argv[]) {
    MACRO(multiply(2,3)==6);
    MACRO(multiply(2,3)==5);
    MACRO(multiply(4,5)==20);
    MACRO(multiply(4,5)==19);
    return EXIT_SUCCESS;
}

