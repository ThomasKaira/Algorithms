#include <stdbool.h>
#define MAX_SIZE 100
#ifndef ALGSCORE_H_INCLUDED
#define ALGSCORE_H_INCLUDED

//Core Functions
int* createArray(int size, int minVal, int maxVal);
int swap(int* xp, int* yp);
void PrintArray(int arr[], int n);
int Valid2Int(char* in1, char* in2, int* out1, int* out2);
int ValidInt(char* in, int* out);
int ValidYN(char* in, char* out);

//Sorting Algorithms
void BubbleSort(int* arr, int n, bool verbose);
void InsertionSort(int* arr, int n, bool verbose);
void SelectionSort(int* arr, int n, bool verbose);

//Data Structures
//Core Node structure and functionality
typedef struct Node
{
  struct Node* next;
  int data;
} node;

node* create_node(int val);
int insert_top(node** top, int val);
int delete_top(node** top);

typedef struct DoubleLink_Node
{
  struct DoubleLink_Node* prev;
  struct DoubleLink_Node* next;
  int data;
} double_link_node;

double_link_node* create_DL_node(int val);
int insert_tail(double_link_node** tail, int val);
int insert_head(double_link_node** head, int val);
int delete_tail(double_link_node** tail);
int delete_head(double_link_node** head);


//Stack
int stack_isEmpty(node** stack);
void stack_push(node** stack, int val);
int stack_pop(node** stack);
int stack_peek(node** stack);
void stack_print(node** stack);

#endif
