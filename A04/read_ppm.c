/* read_ppm.c
 * Reads in a PPM file with ASCII values and returns a 2D array of struct
 * ppm_pixel that stores RGB values
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
  char temp[50];
  struct ppm_pixel ** pixels = NULL;

  file = fopen(filename, "r");
  if (file == NULL) {
    return NULL;
  }

  // check for correct format
  fgets(word, 100, file);
  sscanf(word, "%s ", temp);
  if (strcmp(temp, "P3") != 0) {
    printf("Error: not an ASCII ppm file.\n");
    return NULL;
  }
  // check that dimensions match the arguments
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

  // populate array values
  for (int i = 0; i < *height; i++) {
    for (int j = 0; j < *width; j++) {
      fscanf(file, " %hhu %hhu %hhu", &pixels[i][j].red, &pixels[i][j].green,
          &pixels[i][j].blue);
    }
  }

  fclose(file);
  return pixels;
}
