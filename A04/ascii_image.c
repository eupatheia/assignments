/* ascii_image.c
 * Takes a command line argument for a filename, turns the RGB values into a
 * 2D array, and prints an ASCII image based on those values
 * Jasmine Lei
 * 17 February 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include "read_ppm.h"

// helper function to determine which ascii character to print
void print_char(double intensity) {
  if (intensity >=0 && intensity < 26) {
    printf("@");
  } else if (intensity >= 26 && intensity < 51) {
    printf("#");
  } else if (intensity >= 51 && intensity < 76) {
    printf("%%");
  } else if (intensity >= 76 && intensity < 101) {
    printf("*");
  } else if (intensity >= 101 && intensity < 126) {
    printf("o");
  } else if (intensity >= 126 && intensity < 151) {
    printf(";");
  } else if (intensity >= 151 && intensity < 176) {
    printf(":");
  } else if (intensity >= 176 && intensity < 201) {
    printf(",");
  } else if (intensity >= 201 && intensity < 226) {
    printf(".");
  } else {
    printf(" ");
  }
}

int main(int argc, char** argv) {
  struct ppm_pixel ** pixels = NULL;
  char* filename;
  double intensity;
  int width;
  int height;

  if (argc != 2) {
    // wrong number of arguments
    printf("usage: ./ascii_image <filename>\n");
    exit(1);
  }
  filename = argv[1];

  // attempt to read ppm file into a 2D array
  pixels = read_ppm(filename, &width, &height);
  if (pixels == NULL) {
    printf("Error: failed read_ppm.  Exiting...\n");
    exit(1);
  }

  printf("Reading %s with width %d and height %d\n", filename, width, height);

  // print ascii image pixel-by-pixel
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      intensity = (pixels[i][j].red + pixels[i][j].green +
          pixels[i][j].blue) / 3.0;
      print_char(intensity);
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
