#include <stdio.h>
#include <string.h>

struct cake {
  float cost;
  char flavor[16];
  struct cake* next;
};

struct cake makeCake(const char* flavor, float cost) {
  struct cake newCake;
  strncpy(newCake.flavor, flavor, 16);
  newCake.cost = cost;
  newCake.next = NULL;
  return newCake;
}

void cheapestCake(struct cake * head) {
  struct cake * next = head;
  struct cake * cheapest = NULL;
  float min = next->cost;
  while(next != NULL) {
    printf("cake: %s ($%.02f)\n", next->flavor, next->cost);
    if (next->cost < min) {
      min = next->cost;
      cheapest = next;
    }
    next = next->next;
  }
  printf("The cheapest cake is %s\n", cheapest->flavor);
}

int main() {
  struct cake cake1 = makeCake("red velvet", 2.00);
  struct cake cake2 = makeCake("chocolate", 1.75);
  struct cake cake3 = makeCake("mocha", 3.50);
  struct cake cake4 = makeCake("tea", 2.50);

  cake1.next = &cake2;
  cake2.next = &cake3;
  cake3.next = &cake4;
  // draw stack and heap here

  cheapestCake(&cake1);
}
