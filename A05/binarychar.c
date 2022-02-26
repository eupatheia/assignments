/* binarychar.c
 * Gets an 8-bit binary number from user input and
 * outputs the corresponding character
 * Jasmine Lei
 * 25 February 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
  char digits[12];
  int num = 0;

  printf("Enter 8 bits: ");
  scanf(" %s", digits);

  for (int i = 0; i < 8; i++) {
    num += (digits[i] - '0') * pow(2, 7 - i);
  }

  printf("Your character is: %c\n", num);

  return 0;
}
