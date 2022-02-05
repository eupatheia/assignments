/*
 * Repeats a given word for a given number of times, if enough memory available
 * Jasmine Lei
 * 04 February 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char word[32];
  int count;
  char* repeated;

  printf("Enter a word: ");
  scanf(" %s", word);
  printf("Enter a count: ");
  scanf(" %d", &count);

  repeated = malloc(sizeof(char) * strlen(word) * count);
  // check for successful malloc
  if (repeated == NULL) {
    printf("Cannot allocate new string.  Exiting...\n");
    exit(1);
  }

  // new string with word repeated count times
  for (int i = 0; i < count; i++) {
    strcat(repeated, word);
  }
  printf("%s\n", repeated);

  free(repeated);
  repeated = NULL;

  return 0;
}
