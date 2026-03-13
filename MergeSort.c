#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "AlgsCore.h"

#define MIN_VAL 1


void Merge(int* arr, int l, int m, int r, bool verbose, int* invs);
void MergeSort(int* arr, int l, int r, int* invs);

int main()
{
  double time = 0;
  
  int ARRAY_SIZE;
  int MAX_VAL;
  int inversions = 0;

  clock_t start, end;
  
  printf("How many indices and what is the largest number you want?\n");
  scanf("%d %d", &ARRAY_SIZE, &MAX_VAL);
  
  int* myArray = createArray(ARRAY_SIZE, MIN_VAL, MAX_VAL);
  start = clock();
  MergeSort(myArray, 0, ARRAY_SIZE - 1, &inversions);
  end = clock();
  
  time = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("Sort occurred in %f ms\n", (time * 1000));
  printf("Array contained %d inversions\n", inversions);
  PrintArray(myArray, ARRAY_SIZE);
  
  
  free(myArray);
  exit(0);
}

void Merge(int* arr, int l, int m, int r, bool verbose, int* invs)
{
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;
  
  //Build the left and right arrays.
  int L[n1], R[n2];
  for(i = 0; i < n1; i++)
    L[i] = arr[l + i];
    if(verbose)
      printf("Adding element %d into Left array index %d\n", arr[l + i], i);
  for(j = 0; j < n2; j++)
    R[j] = arr[m + 1 + j];
    if(verbose)
      printf("Adding element %d into Right array index %d\n", arr[m + 1 + j], j);
  
  i = 0;
  j = 0;
  k = l;
  
  //Sorting the sub-arrays
  while(i < n1 && j < n2)
  {
    if(L[i] < R[j]) //Sorted correctly
    {
      arr[k] = L[i];
      i++;
    }
    else //Inversion
    {
      *invs += 1;
      arr[k] = R[j];
      j++;
    }
    k++;
  }
  
  while(i < n1)
  {
    arr[k] = L[i];
    i++;
    k++;
  }
  
  while(j < n2)
  {
    arr[k] = R[j];
    j++;
    k++;
  }
}

void MergeSort(int* arr, int l, int r, int* invs)
{
 
  if(l < r)
  {
    int m = l + (r - l) / 2;
    MergeSort(arr, l, m, invs);
    MergeSort(arr, m + 1, r, invs);
    
    Merge(arr, l, m, r, false, invs);
  }
}
