#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "../src/mult.h"

#define STR(x) #x
#define MY_EXPECT(x) if (!(x)) { printf("Error: (%s), %s:%s:%d.\n", STR(x), __PRETTY_FUNCTION__, __FILE__, __LINE__); }
#define MY_ASSERT(x) if (!(x)) { printf("Error: (%s), %s:%s:%d.\n", STR(x), __PRETTY_FUNCTION__, __FILE__, __LINE__); abort(); }


int main(int argc, const char *argv[]) {
    MY_EXPECT(multiply(2,3)==6);
    MY_EXPECT(multiply(2,3)==5);
    MY_EXPECT(multiply(4,5)==20);
    MY_EXPECT(multiply(4,5)==19);

   return 0;
}

