/* read_ppm.c
 * Reads in a PPM file with ASCII values and returns a 2D array of struct
 * ppm_pixel
 * Jasmine Lei
 * 17 February 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

struct ppm_pixel** read_ppm(const char* filename, int* width, int* height) {
  FILE* file;
  char word[100];
  struct ppm_pixel ** pixels = NULL;
  unsigned char r, g, b;

  file = fopen(filename, "r");
  if (file == NULL) {
    return NULL;
  }

  // check for correct format
  fgets(word, 3, file);
  if (strcmp(word, "P3") != 0) {
    printf("Error: not an ASCII ppm file.\n");
    return NULL;
  }
  // check that dimensions match the arguments
  fgets(word, 100, file);
  fgets(word, 100, file);
  // skip over comments
  while (word[0] == '#') {
    fgets(word, 100, file);
  }
  sscanf(word, "%d %d", width, height);
  // assuming max val is less than 256, and discard
  fgets(word, 100, file);

  // allocate space for 2D array of arrays
  pixels = malloc(sizeof(struct ppm_pixel *) * *height);
  if (pixels == NULL) {
    return NULL;
  }
  for (int i = 0; i < *height; i++) {
    pixels[i] = malloc(sizeof(struct ppm_pixel) * *width);
    if (pixels[i] == NULL) {
      return NULL;
    }
  }

  for (int i = 0; i < *height; i++) {
    for (int j = 0; j < *width; j++) {
      fscanf(file, " %hhu %hhu %hhu", &r, &g, &b);
      pixels[i][j].red = r;
      pixels[i][j].green = g;
      pixels[i][j].blue = b;
    }
  }

  fclose(file);
  return pixels;
}
