#include <stdlib.h>
#include <stdio.h>

#define NUM_TESTS 10

void TowerOfHanoi(int n, char sourceRod, char destRod, char midRod);

int num_moves;

int main()
{
  int tower_height = 1;
  for(int i = 0; i < NUM_TESTS; i++)
  {
    num_moves = 0;
    TowerOfHanoi(tower_height, 'A', 'C', 'B');
    printf("Tower of Hanoi completed in %d moves for %d discs\n", num_moves, tower_height); 
    tower_height++;
  }
  return 0;
}

void TowerOfHanoi(int n, char sourceRod, char destRod, char midRod)
{
  if (n == 0)
    return;
  num_moves++;
  TowerOfHanoi(n - 1, sourceRod, midRod, destRod);
  printf("Disc %d moved from rod %c to rod %c\n", n, sourceRod, destRod);
  TowerOfHanoi(n - 1, midRod, destRod, sourceRod);
}


