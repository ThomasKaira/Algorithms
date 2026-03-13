#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "AlgsCore.h"
#include <stdbool.h>

#define MAX_SIZE 100

int* createArray(int size, int minVal, int maxVal)
{ 
  int* array = (int*)malloc(size * sizeof(int));
  srand(time(NULL));

  for(int i = 0; i < size; i++)
  {
    int randVal = (rand() % (maxVal - minVal + 1)) + minVal;
    array[i] = randVal;
    //printf("Placed %d at index %d\n", randVal, i);
  }
  return array;
}

int swap(int* xp, int* yp)
{
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
  return 1;
}

void PrintArray(int arr[], int n)
{
  for(int i = 0; i < n; i++)
  {
    printf("Index %d is %d\n", i, arr[i]);
  }
}

int Valid2Int(char* in1, char* in2, int* out1, int* out2)
{
  //printf("Input: %s %s\n", in1, in2);
  if(atoi(in1) == 0 || atoi(in2) == 0)
  {
    printf("Numerical values only\n");
    return 0;
  }
  else if(atoi(in1) < 1 || atoi(in2) < 1)
  {
    printf("Positive values only\n");
    return 0;
  }
  
  *out1 = atoi(in1);
  *out2 = atoi(in2);
  return 1;
}

int ValidInt(char* in, int* out)
{
  if(atoi(in) == 0)
  {
    printf("Numerical values only\n");
    return 0;
  }
  else if(atoi(in) < 1)
  {
    printf("Positive values only\n");
    return 0;
  }
  
  *out = atoi(in);
  return 1;
}

int ValidYN(char* in, char* out)
{
  if((in[0] == 'y' || in[0] == 'Y' || in[0] == 'n' || in[0] == 'N') && strlen(in) == 1)
  {
    *out = in[0];
    return 1;
  }
  printf("Only Y or N (not case sensitive)\n");
  return 0;
}

void BubbleSort(int* arr, int n, bool verbose)
{
  int swaps = 0;
  int comparisons = 0;
  
  int i, j;
  bool swapped;
  //i loop defines lower bound of bubble sort.
  for(i = 0; i < n - 1; i++)
  {
    swapped = false;
    //j loop defines upper bound of bubble sort.
    for(int j = 0; j < n - i - 1; j++)
    {
      comparisons++;
      if(arr[j] > arr[j + 1])
      {
        if(verbose)
          printf("Swapping elements at position %d and %d\n", arr[j], arr[j + 1]);
        swaps += swap(&arr[j], &arr[j + 1]);
        swapped = true;
      }
    }//j for loop end
    
    if(swapped == false)
    {
      break;
    }
  }//i for loop end
  
  printf("Array sorted using %d swaps, %d comparisons.\n", swaps, comparisons);
}

void InsertionSort(int* arr, int n, bool verbose)
{
  int swaps = 0;
  for(int i = 1; i < n; i++)
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
  printf("Array sorted using %d swaps\n", swaps);
}

void SelectionSort(int* arr, int n, bool verbose)
{
  int swaps = 0;
  int comparisons = 0;
  for(int i = 0; i < n - 1; i++)
  {
    int min_idx = i;
    
    for(int j = i + 1; j < n; j++)
    {
      comparisons++;
      if(arr[j] < arr[min_idx])
      {
        min_idx = j;
        if(verbose)
          printf("New lowest found: %d\n", arr[min_idx]);
      }
    }
    int temp = arr[i];
    arr[i] = arr[min_idx];
    arr[min_idx] = temp;
    if(verbose)
      printf("Lowest found %d placed at index %d\n", arr[min_idx], i);
    swaps++;
  }
  
  printf("Array sorted using %d swaps, %d comparisons.\n", swaps, comparisons);
}

node* create_node(int val)
{
  node* newNode = (node*)malloc(sizeof(node));
  
  if(newNode == NULL)
    return NULL;
  
  newNode->data = val;
  newNode->next = NULL;
  return newNode;
}

int insert_top(node** top, int val)
{
  //Create a new node
  node* newNode = create_node(val);
  if(!newNode)
    return -1;
  
  //If the list is empty, make this node the top
  if(*top == NULL)
  {
    *top = newNode;
    return 0;
  }
  
  //Otherwise, add this node to the list as the new top
  newNode->next = *top;
  *top = newNode;
  return 0;
}

int delete_top(node** top)
{
  node* temp = *top;
  *top = (*top)->next;
  free(temp);
  return 0;
}

double_link_node* create_DL_node(int val)
{
  double_link_node* newNode = (double_link_node*)malloc(sizeof(double_link_node));
  
  if(newNode == NULL)
    return NULL;
  
  newNode->data = val;
  newNode->prev = NULL;
  newNode->next = NULL;
  return newNode;
}

int insert_tail(double_link_node** tail, int val)
{
  //Create a new node
  double_link_node* newNode = create_DL_node(val);
  if(!newNode)
    return -1;
  
  //If the list is empty, make this node the top
  if(*tail == NULL)
  {
    *tail = newNode;
    return 0;
  }
  
  //Otherwise, add this node to the list as the new top
  newNode->next = *tail;
  (*tail)->prev = newNode;
  *tail = newNode;
  return 0;
}

int insert_head(double_link_node** head, int val)
{
  //Create a new node
  double_link_node* newNode = create_DL_node(val);
  if(!newNode)
    return -1;
  
  //If the list is empty, make this node the top
  if(*head == NULL)
  {
    *head = newNode;
    return 0;
  }
  
  double_link_node* temp = *head;
  while(temp->next != NULL)
  {
    temp = temp->next;
  }
  temp->next = newNode;
  newNode->prev = temp;
  //Otherwise, add this node to the list as the new top

  return 0;
}

int stack_isEmpty(node** stack)
{
  return *stack == NULL;
}

void stack_push(node** stack, int val)
{
  if(insert_top(stack, val))
  {
    printf("Stack Overflow!!!\n");
  }
}

int stack_pop(node** stack)
{
  if(stack_isEmpty(stack))
  {
    printf("Stack Underflow\n");
    return -1;
  }
  
  delete_top(stack);
  return 0;
}

int stack_peek(node** stack)
{
  if(!stack_isEmpty(stack))
  {
    return (*stack)->data;
  }
  else
  {
    return -1;
  }
}

void stack_print(node** stack)
{
  node* temp = *stack;
  while(temp != NULL)
  {
    printf("%d-> ", temp->data);
    temp = temp->next;
  }
  printf("\n");
}

