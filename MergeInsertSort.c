#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include "AlgsCore.h"

#define MIN_VAL 1

int Merge(int* arr, int l, int m, int r, bool verbose);
void MergeInsertSort(int* arr, int l, int r, int threshold);
void InsertionSort(int* arr, int l, int r, bool verbose);

char Array_SizeStr[10];
char Max_ValStr[10];
char ThresholdStr[10];
char num_testsStr[10];
char print_sortedStr[10];

unsigned int ARRAY_SIZE, MAX_VAL, THRES;
unsigned int swaps, recursions, num_tests, inversions;
clock_t start, end;
char print_sorted;

FILE *f;

int main()
{
  int c;                //Used to clear the input buffer
  int input_valid = 0;  //Set to 1 for a valid input, 0 for invalid
  
  //Take a validated input to decide how big and how varied the random array will be
  printf("How many indices and what is the largest number you want?\n");
  do
  {
    scanf("%s %s", Array_SizeStr, Max_ValStr);
    while(c = getchar() != '\n');         //Clears the input buffer
    input_valid = Valid2Int(Array_SizeStr, Max_ValStr, &ARRAY_SIZE, &MAX_VAL);

  } while(input_valid == 0);
  
  input_valid = 0;
  
  //Take a validated input to decide at what point we switch from merge to insertion method
  printf("What threshold do you wish to switch methods at?\n");
  do
  {
    scanf("%s", ThresholdStr);
    while(c = getchar() != '\n');
    input_valid = ValidInt(ThresholdStr, &THRES);
  } while(input_valid == 0);
  
  input_valid = 0;
  
  //Take a validated input for if the sorted array should be printed.
  //This will limit the algorithm to run only once to prevent terminal spam.
  printf("Do you want to view the final sorted array and run only once? (Y/N)\n");
  do
  {
    scanf("%s", print_sortedStr);
    while(c = getchar() != '\n');
    input_valid = ValidYN(print_sortedStr, &print_sorted);
  }while(input_valid == 0);
  
  num_tests = 1;    //We know at this point at least one test will run.
  input_valid = 0;
  
  //Take a validated input for how many times the algorithm should be run to test its performance.
  if(print_sorted == 'n' || print_sorted == 'N')
  {
    printf("How many tests do you want to run?\n");
    do
    {
      scanf("%s", num_testsStr);
      while(c = getchar() != '\n');
      input_valid = ValidInt(num_testsStr, &num_tests);
    }while(input_valid == 0);
  }
  
  while(num_tests > 0)
  {
    //Set up our metrics variables.
    swaps = 0;
    recursions = 0;
    double time = 0;
    
    //Generate an array of random integers according to the given specifications.
    int* myArray = createArray(ARRAY_SIZE, MIN_VAL, MAX_VAL);
    
    //Run the sorting algorithm and capture its start and end times.
    start = clock();
    MergeInsertSort(myArray, 0, ARRAY_SIZE - 1, THRES);
    end = clock();
    
    //Compute the execution time in seconds
    time = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    //Print the metrics, including execution time in milliseconds, number of swaps, and number of recursions
    if(print_sorted == 'Y'|| print_sorted == 'y')
      PrintArray(myArray, ARRAY_SIZE);
    printf("Sort occurred in %f ms\n", (time * 1000));
    printf("Array sorted using %d swaps, %d recursions\n", swaps, recursions);
    
    //Print array size, threshold, and execution time to an external file
    f = fopen("MergeInsertOutput.txt", "a");
    if(f == NULL)
    {
      printf("File open failed");
    }
    else
    {
      fprintf(f, "Array Size: %d, Threshold: %d, Time: %f ms\n", ARRAY_SIZE, THRES, time * 1000);
      fclose(f);
    }
    
    free(myArray);
    num_tests--;
    sleep(1);     //Re-seeds our randomizer.
  }
  exit(0);
}

int Merge(int* arr, int l, int m, int r, bool verbose, int* invs)
{
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;
  int swaps = 0;
  int inversions = 0;
  
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
      swaps++;
      arr[k] = R[j];
      j++;
      inversions++;
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
  *invs = inversions;
  return swaps;
}

void MergeInsertSort(int* arr, int l, int r, int threshold)
{
  
  if(l < r)
  {
    
    if((r - l + 1) <= threshold)
    {
      InsertionSort(arr, l, r, false);
      return;
    }
    
    int m = l + (r - l) / 2;
    //printf("m = %d, recursions %d\n", m, recursions);
    MergeInsertSort(arr, l, m, threshold);
    MergeInsertSort(arr, m + 1, r, threshold);
    
    swaps += Merge(arr, l, m, r, false, &inversions);
    recursions++;
    
    
  }
  
}

void InsertionSort(int* arr, int l, int r, bool verbose)
{
  for(int i = l; i <= r; i++)
  {
    int key = arr[i];
    int j = i - 1;
    if(verbose)
      printf("Key is %d\n", key);
    
    while(j >= 0 && arr[j] > key)
    {
      swaps += swap(&arr[j], &arr[j + 1]);
      j-= 1;

      if(verbose)
        printf("Swapped elements in %d, %d\n", i, j);
    }
  }
  //printf("Array sorted using %d swaps\n", swaps);
  //PrintArray(arr, n);
  //printf("\n");
}


