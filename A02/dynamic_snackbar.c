/*
 * Allows user to define snacks (name, cost, quantity) and prints them out
 * Jasmine Lei
 * 04 February 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct snack {
  char name[32];
  float cost;
  int quantity;
};

int main() {
  int snack_amount;
  struct snack * snacks;

  printf("Enter a number of snacks: ");
  scanf("%d", &snack_amount);
  snacks = malloc(sizeof(struct snack) * snack_amount);
  // check for successful malloc
  if (snacks == NULL) {
    printf("Unsucessful malloc.  Exiting...\n");
    exit(1);
  }

  // fill with snacks
  for (int i = 0; i < snack_amount; i++) {
    printf("Enter a name: ");
    scanf(" %s", snacks[i].name);
    printf("Enter a cost: ");
    scanf("%f", &snacks[i].cost);
    printf("Enter a quantity: ");
    scanf("%d", &snacks[i].quantity);
  }

  // print current list of snacks
  printf("\nWelcome to the Snack Bar.\n\n");
  for (int i = 0; i < snack_amount; i++) {
    printf("%d) %-32s cost: $%-10.2f\t quantity: %d\n", i, snacks[i].name,
        snacks[i].cost, snacks[i].quantity);
  }

  free(snacks);
  snacks = NULL;
  return 0;
}
