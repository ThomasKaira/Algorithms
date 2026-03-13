#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "AlgsCore.h"

#define NUM_NODES 20

int main()
{
  //We will build a queue using two stacks.
  node* enqueueStack = NULL;
  node* dequeueStack = NULL;
  
  //We build the the enqueue stack. (This is considered the input data and has no Big-O)
  for(int i = 0; i < NUM_NODES; i++)
  {
    stack_push(&enqueueStack, i);
    printf("%d Queued.\n", enqueueStack->data);
  }
  
  //The enqueue stack will have the first element added at the bottom.
  //Prints have no Big-O from the perspective of the core algorithm.
  printf("In Stack: (top)");
  stack_print(&enqueueStack);
  
  //Transfer all elements from the enqueue stack to the dequeue stack
  //This operation has O(n) as 2n elements will be worked. 
  while(enqueueStack != NULL)
  {
    int temp = enqueueStack->data;
    stack_pop(&enqueueStack);
    stack_push(&dequeueStack, temp);
  }
  
  //The dequeue stack will have the first element from the enqueue stack at the top.
  printf("Out stack: (top)");
  stack_print(&dequeueStack);
  
  //Pop all elements from the dequeue stack. We don't necessarily want to pop them all at once.
  //Each pop operation is O(1) as we always pop from the top of the stack.
  while(dequeueStack != NULL)
  {
    printf("%d Dequeued.\n", dequeueStack->data);
    stack_pop(&dequeueStack);
  }
}



