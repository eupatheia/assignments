/* word.c
 * Gets a 4-letter word from user input and stores the characters as an
 * unsigned int, then prints the number in decimal and hexadecimal
 * Jasmine Lei
 * 25 February 2022
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  char word[5];
  unsigned int chars[4];
  unsigned int num;

  printf("Enter 4 characters: ");
  scanf(" %s", word);

  for (int i = 3; i >= 0; i--) {
    chars[i] = word[i];
    chars[i] = (chars[i] << ((3 - i) * 8));
    printf("Debug: %c = 0x%08X\n", word[i], chars[i]);
  }
  num = chars[0] | chars[1] | chars[2] | chars[3];
  printf("Your number is: %u (0x%08X)\n", num, num);

  return 0;
}
