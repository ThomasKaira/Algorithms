#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "AlgsCore.h"
#define MIN_VAL 1

int ARRAY_SIZE;
int MAX_VAL;
clock_t start, end;

int swaps, recursions;

int Partition(int* arr, int l, int r);
void QuickSort(int* arr, int l, int r);

int main()
{
  swaps = 0;
  recursions = 0;
  double time = 0;
  
  printf("How many indices and what is the largest number you want?\n");
  
  scanf("%d %d", &ARRAY_SIZE, &MAX_VAL);
  
  int* myArray = createArray(ARRAY_SIZE, MIN_VAL, MAX_VAL);
  
  //PrintArray(myArray, ARRAY_SIZE);
  //printf("\n");
  start = clock();
  QuickSort(myArray, 0, (ARRAY_SIZE));
  end = clock();
  time = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("Sort occurred in %f ms\n", (time * 1000));
  //PrintArray(myArray, ARRAY_SIZE);
  
  printf("Array sorted using %d swaps, %d recursions\n", swaps, recursions);
  
  free(myArray);
  exit(0);
}

int Partition(int* arr, int l, int r)
{
  int swaps = 0;
  //Set our swap index to 1 before our starting index
  int i = l - 1;
  
  //Start our scan at the first element and continue until the end
  for(int j = l; j < r; j++)
  {
    //Increment swap index if element at scan index is less than pivot, and swap the two elements
    if(arr[j] < arr[r])
    {
      i++;
      swaps+= swap(&arr[i], &arr[j]);
    }
    
  }
  i++;
  if(arr[i] > arr[r])
    swaps += swap(&arr[i], &arr[r]);
  return i;
}


void QuickSort(int* arr, int l, int r)
{
    int swaps = 0;
    int recursions = 0;
    
    if(l < r)
    {
      //printf("Partitioning array\n");
      int par_idx = Partition(arr, l, r, &swaps);
      QuickSort(arr, l, par_idx - 1);
      QuickSort(arr, par_idx + 1, r);
      recursions++;    
      //printf("Pass %d:\n", recursions);
      //PrintArray(arr, r);
      //printf("\n");
    }
    
    printf("Array sorted using %d swaps, %d recursions\n", swaps, recursions);
}
