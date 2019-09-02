#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H

#define TABLE_SIZE 10

// allocate array and return it
int * allocate(int amount);

// print particular value
void print_value(int * array, int pos);

//print all requested values
void print_values(int * array, int amount);

//increase all values in array by inc
void increase_values(int ** array, int amount, int inc);

#endif // __FUNCTIONS_H
