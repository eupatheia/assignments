/* snackbar.c
 * Jasmine Lei
 * 27 January 2022
 * Simulates purchasing from a snack bar
 */

#include <stdio.h>
#include <string.h>

// stores info about a snack item
struct snack {
	char name[75];
	float cost;
	int quantity;
};

int main() {
	struct snack snackbar[3];
	float money;
  int choice;
  struct snack * to_buy = NULL;

	// create all snacks
	strcpy(snackbar[0].name, "Coco Puffs");
	snackbar[0].cost = 1.5;
	snackbar[0].quantity = 4;

	strcpy(snackbar[1].name, "Manchego Cheese");
	snackbar[1].cost = 15.5;
	snackbar[1].quantity = 6;

	strcpy(snackbar[2].name, "Magic Beans");
	snackbar[2].cost = 0.5;
	snackbar[2].quantity = 0;

	printf("Welcome to The Snack Bar.\n\n");
	printf("How much money do you have? ");
	scanf("%g", &money);
	printf("\n");
	// print all snacks
	for (int i = 0; i < 3; i++) {
  	printf("%d) %-20s cost: $%.2f\t quantity: %d\n", i, snackbar[i].name,
        snackbar[i].cost, snackbar[i].quantity);
	}
  printf("\n");
  printf("What snack would you like to buy? [0/1/2] ");
  scanf("%d", &choice);
	// determine chosen snack
  if (choice == 0) {
    to_buy = &snackbar[0];
  } else if (choice == 1) {
    to_buy = &snackbar[1];
  } else if (choice == 2) {
    to_buy = &snackbar[2];
  } else {
    printf("You haven't chosen a valid snack.\n");
    return 0;
  }

  if (to_buy->quantity == 0) {
    printf("Sorry, we are out of %s.\n", to_buy->name);
  } else if (money >= to_buy->cost) {
    printf("You bought %s.\n", to_buy->name);
    printf("You have $%.2f left.\n", (money - to_buy->cost));
  } else {
    printf("Sorry, you can't afford it.\n\n");
  }
	return 0;
}
