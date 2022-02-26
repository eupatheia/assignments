/* test_ppm.c
 * Tests read_ppm.c using a hard-coded file name, "feep-raw.ppm"
 * Jasmine Lei
 * 25 February 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

int main() {
  struct ppm_pixel ** pixels = NULL;
  char* filename = "feep-raw.ppm";
  int width;
  int height;

  // attempt to read ppm file into a 2D array
  pixels = read_ppm(filename, &width, &height);
  if (pixels == NULL) {
    printf("Error: failed read_ppm.  Exiting...\n");
    exit(1);
  }

  // print array contents for error checking
  printf("Testing file %s: %d %d\n", filename, width, height);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      printf("(%d,%d,%d) ", pixels[i][j].red, pixels[i][j].green,
          pixels[i][j].blue);
    }
    printf("\n");
  }

  // free allocated array memory
  for (int i = 0; i < height; i++) {
    free(pixels[i]);
    pixels[i] = NULL;
  }
  free(pixels);
  pixels = NULL;

  return 0;
}
