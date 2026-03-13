#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "AlgsCore.h"
#define MIN_VAL 1

int ARRAY_SIZE;
int MAX_VAL;
clock_t start, end;


int main()
{
  double time = 0;
  
  printf("How many indices and what is the largest number you want?\n");
  scanf("%d %d", &ARRAY_SIZE, &MAX_VAL);
  
  int* myArray = createArray(ARRAY_SIZE, MIN_VAL, MAX_VAL);
  
  start = clock();
  InsertionSort(myArray, ARRAY_SIZE, false);
  end = clock();
  
  time = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("Sort occurred in %f ms\n", (time * 1000));
  PrintArray(myArray, ARRAY_SIZE);
  
  free(myArray);
  exit(0);
}
