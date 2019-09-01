#include <stdio.h>

#include "gen_num.h"

#define START_POSITION 13
#define SUCCESS 0
#define FAILURE 1

#define CALC_RET_VAL(value) \
   (((value) > START_POSITION) ? SUCCESS : FAILURE)

int main(int argc, const char *argv[])
{
   int value;

   /*??????????????*/
   gen_num();
   gen_num();
   gen_num();
   value = gen_num() + START_POSITION;

   printf("Hello, world!\n");
   printf("=====\t%d\t========\n", value);
   return CALC_RET_VAL(value);
}
