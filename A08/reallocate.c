#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "rand.h"

int main (int argc, char* argv[]) {
  void * init = sbrk(0);
  for (int i = 0; i < 10; i++) {
    int * memory = NULL;
    memory = malloc(100);
    if (memory == NULL) {
      printf("failled malloc\n");
      exit(0);
    }
    *memory = 123;
    free(memory);
  }
  void * current = sbrk(0);
  printf("The initial top of the heap is %p.\n", init);
  printf("The current top of the heap is %p.\n", current);
  int allocated = (int) (current - init);
  printf("Increased by %d (0x%x) bytes\n", allocated, allocated);
  return 0;
}
