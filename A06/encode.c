#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

int main(int argc, char** argv) {
  struct ppm_pixel ** pixels = NULL;
  char* filename, *message;
  char new_file[100];
  char* end;  // index of end of filename
  int width, height, max;
  int i = 0;  // row counter
  int j = 0;  // column counter
  int k = 0;  // color counter
  char ch;
  unsigned int bit, prev_bit, mask = 0x80;

  if (argc != 2) {
    // wrong number of arguments
    printf("usage: ./encode <filename>\n");
    exit(1);
  }
  filename = argv[1];

  // attempt to read ppm file into a 2D array
  pixels = read_ppm(filename, &width, &height);
  printf("Reading %s with width %d and height %d\n", filename, width, height);
  if (pixels == NULL) {
    printf("Error: failed read from file.  Exiting...\n");
    exit(1);
  }
  // max number of characters, not including the null char at end
  max = (width * height * 3) / 8;
  printf("Max number of non-null characters in the image: %d\n", max - 1);
  message = malloc(sizeof(char) * max);

  // get user-defined message
  printf("Enter a phrase: ");
  // read max-1 characters, fgets puts '\0' at end
  fgets(message, max, stdin);

  // <= strlen() because counting null character at index strlen
  for (int n = 0; n <= strlen(message); n++) {
    ch = message[n];
    // printf("\n\n0x%04X = %c\n", ch, ch);
    // each char takes up 8 bits, i.e. 8 changed values
    for (int m = 0; m < 8; m++) {
      // printf("%d-%d-%d\n", i, j, k);
      // 1 in mask at correct bit
      // printf("mask: 0x%04X\n", mask);
      // get the bit at that position
      bit = mask & ch;
      bit = bit >> (7 - m);
      // printf("bit: 0x%04X\n", bit);
      // get the existing bit
      prev_bit = 0x1 & pixels[i][j].colors[k];
      // printf("prev_bit: 0x%04X\n", prev_bit);
      // if not matching, change the existing bit

      // printf("current pixel color value: 0x%04X\n", pixels[i][j].colors[k]);
      if (bit != prev_bit) {
        // bitwise xor with 0x1 flips the last bit
        // because x ^ 0 = x and x ^ 1 = opposite-of-x
        pixels[i][j].colors[k] = pixels[i][j].colors[k] ^ 0x1;
        // printf("changed pixel color value: 0x%04X\n", pixels[i][j].colors[k]);
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
      mask = mask >> 1;
    }
    mask = 0x80;
  }

  // write to file
  strncpy(new_file, filename, 100);
  end = strstr(new_file, ".ppm");
  *end = '\0';
  strcat(new_file, "-encoded.ppm");
  printf("Writing file %s\n", new_file);
  write_ppm(new_file, pixels, width, height);

  // free allocated array memory
  for (int i = 0; i < height; i++) {
    free(pixels[i]);
    pixels[i] = NULL;
  }
  free(pixels);
  pixels = NULL;

  // free message array
  free(message);
  message = NULL;

  return 0;
}
