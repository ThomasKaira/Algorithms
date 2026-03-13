#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "AlgsCore.h"

int main()
{
  node* stack = NULL;
  stack_push(&stack, 1);
  stack_push(&stack, 2);
  stack_push(&stack, 3);
  stack_push(&stack, 4);
  stack_push(&stack, 5);
  
  printf("Stack: (top)");
  stack_print(&stack);
  
  stack_pop(&stack);
  stack_pop(&stack);
  
  printf("Stack: (top)");
  stack_print(&stack);
  
  stack_push(&stack, 6);
  stack_push(&stack, 7);
  
  printf("Stack: (top)");
  stack_print(&stack);
}



