//---------------------------------------------------------------------
// sorted_snackbar.c
// CS223 - Spring 2022
// Ask the user for a list of snacks and store them in alphabetical order
// Name: Jasmine Lei
// Date: 11 February 2022
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct snack {
  char name[32];
  int quantity;
  float cost;
  struct snack* next;
};

// Insert a new node to a list (implemented as a linked list).
// The new node should store the given properties
// Param snacks: the first item in the list (NULL if empty)
// Param name: the snack name (max length is 32 characters)
// Param quantity: the snack quantity
// Param cost: the snack cost
// Returns the first item in the list
struct snack* insert_sorted(struct snack* snacks,
    const char* name, int quantity, float cost) {
  struct snack * new_snack = NULL;
  new_snack = malloc(sizeof(struct snack));
  if (new_snack == NULL) {
    printf("Failed malloc, returning unchanged list.\n");
    return snacks;
  }
  strcpy(new_snack->name, name);
  new_snack->quantity = quantity;
  new_snack->cost = cost;
  new_snack->next = NULL;

  if (snacks == NULL) {
    // this new snack is the first to be added to the list
    return new_snack;
  }

  if (strcmp(snacks->name, new_snack->name) > 0) {
    // new_snack goes at the front of the list
    new_snack->next = snacks;
    return new_snack;
  }
  // otherwise find the correct position to maintain alpha order;
  // also handles case of insertion at end of list
  struct snack * temp = snacks;
  while (temp->next != NULL && strcmp(temp->next->name, new_snack->name) <= 0) {
    temp = temp->next;
  }
  // new snack should now be inserted after temp
  new_snack->next = temp->next;
  temp->next = new_snack;
  return snacks;  // first item in list unchanged
}

// Delete (e.g. free) all nodes in the given list of snacks
// Param snacks: the first node in the list (NULL if empty)
void clear(struct snack* snacks) {
  if (snacks == NULL) {
    return;
  }
  struct snack * temp = snacks;
  while (snacks != NULL) {
    temp = snacks->next;
    free(snacks);
    snacks = temp;
  }
  // here, all nodes freed and snacks == NULL, as desired
}

int main() {
  int snack_amount;
  char name[32];
  int quantity;
  float cost;
  struct snack * snacks = NULL;

  printf("Enter a number of snacks: ");
  scanf("%d", &snack_amount);

  // fill with snacks
  for (int i = 0; i < snack_amount; i++) {
    printf("Enter a name: ");
    scanf(" %s", name);
    printf("Enter a cost: ");
    scanf("%f", &cost);
    printf("Enter a quantity: ");
    scanf("%d", &quantity);
    snacks = insert_sorted(snacks, name, quantity, cost);
  }

  // print current list of snacks
  printf("\nWelcome to the Snack Bar.\n\n");
  struct snack * temp = snacks;
  int i = 0;
  while (temp != NULL) {
    printf("%d) %-32s cost: $%-10.2f\t quantity: %d\n", i, temp->name,
        temp->cost, temp->quantity);
    temp = temp->next;
    i++;
  }

  clear(snacks);
  return 0;
}
