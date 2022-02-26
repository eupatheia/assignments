/* glitch.c
 * Takes a binary file and "glitches" it to a new file
 * Jasmine Lei
 * 25 February 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_ppm.h"

int main(int argc, char** argv) {
  struct ppm_pixel ** pixels = NULL;
  char* filename;
  char new_file[100];
  int width;
  int height;
  char* end;  // index of end of filename

  if (argc != 2) {
    // wrong number of arguments
    printf("usage: ./glitch <filename>\n");
    exit(1);
  }
  filename = argv[1];

  // attempt to read ppm file into a 2D array
  pixels = read_ppm(filename, &width, &height);
  printf("Reading %s with width %d and height %d\n", filename, width, height);
  if (pixels == NULL) {
    printf("Error: failed read_ppm.  Exiting...\n");
    exit(1);
  }

  // glitch image pixel-by-pixel
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      // for (int k = 0; k < 3; k++) {
      //   pixels[i][j].colors[k] = pixels[i][j].colors[k] << (rand() % 2);
      // }

      // pixels[i][j].red = pixels[i][j].red << 3;

      if (i < height - 50) {
        pixels[i][j].red = pixels[i + (j % 50)][j].red;
        pixels[i][j].green = pixels[i + (j % 50)][j].green;
        pixels[i][j].blue = pixels[i + (j % 50)][j].blue;
      }
      pixels[i][j].green = (pixels[i][j].blue & pixels[i][j].green);
      pixels[i][j].red = pixels[i][j].red << 8;
    }
  }

  // write to file
  strncpy(new_file, filename, 100);
  end = strstr(new_file, ".ppm");
  *end = '\0';
  strcat(new_file, "-glitch.ppm");
  printf("Writing file %s\n", new_file);
  write_ppm(new_file, pixels, width, height);

  // free allocated array memory
  for (int i = 0; i < height; i++) {
    free(pixels[i]);
    pixels[i] = NULL;
  }
  free(pixels);
  pixels = NULL;

  return 0;
}
