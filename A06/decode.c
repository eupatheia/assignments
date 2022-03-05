/* decode.c
 * Reads a ppm file and outputs the message stored in the least
 * significant bits of each color
 * Jasmine Lei
 * 04 March 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "read_ppm.h"

int main(int argc, char** argv) {
  struct ppm_pixel ** pixels = NULL;
  char* filename;
  int width, height;
  int bit_counter = 0;
  int i = 0;  // row counter
  int j = 0;  // column counter
  int k = 0;  // color counter
  int num = 0;

  if (argc != 2) {
    // wrong number of arguments
    printf("usage: ./decode <filename>\n");
    exit(1);
  }
  filename = argv[1];

  // attempt to read ppm file into a 2D array
  pixels = read_ppm(filename, &width, &height);
  if (pixels == NULL) {
    printf("Error: failed read from file.  Exiting...\n");
    exit(1);
  }
  printf("Reading %s with width %d and height %d\n", filename, width, height);
  printf("Max number of characters in the image: %d\n", ((width * height * 3) / 8));

  // read least significant bits pixel-by-pixel, color by color,
  // convert every 8 bits to a char and stop at '\0'
  while (i < height) {
    // least significant bit is 0 if even, 1 if odd
    int bit = pixels[i][j].colors[k] % 2;
    num += bit * pow(2, 7 - bit_counter);

    // output new character every 8 bits read
    if (bit_counter == 7) {
      if (num != '\0') {
        printf("%c", num);
        num = 0;
        bit_counter = 0;
      } else {
        // stop w/o printing if reached null character
        break;
      }
    } else {
      bit_counter++;
    }

    // loop around 3 color values
    k++;
    if (k == 3) {
      // start new column/pixel
      j++;
      k = 0;
    }
    if (j == width) {
      // start new row
      i++;
      j = 0;
    }
  }

  printf("\n");

  // free allocated array memory
  for (int i = 0; i < height; i++) {
    free(pixels[i]);
    pixels[i] = NULL;
  }
  free(pixels);
  pixels = NULL;

  return 0;
}
