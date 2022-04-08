#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include "read_ppm.h"

int main(int argc, char* argv[]) {
  int size = 480;
  float xmin = -2.0;
  float xmax = 0.47;
  float ymin = -1.12;
  float ymax = 1.12;
  int maxIterations = 1000;
  struct ppm_pixel ** pixels = NULL;
  struct ppm_pixel * palette = NULL;
  unsigned int basered, basegreen, baseblue;
  float xfrac, yfrac, x0, y0, x, y, xtmp;
  int iter;
  double timer;
  struct timeval tstart, tend;
  char new_file[100];

  // process command line arguments
  int opt;
  while ((opt = getopt(argc, argv, ":s:l:r:t:b:")) != -1) {
    switch (opt) {
      case 's': size = atoi(optarg); break;
      case 'l': xmin = atof(optarg); break;
      case 'r': xmax = atof(optarg); break;
      case 't': ymax = atof(optarg); break;
      case 'b': ymin = atof(optarg); break;
      case '?': printf("usage: %s -s <size> -l <xmin> -r <xmax> -b <ymin> -t <ymax>\n", argv[0]); break;
    }
  }
  printf("Generating mandelbrot with size %dx%d\n", size, size);
  printf("  X range = [%.4f,%.4f]\n", xmin, xmax);
  printf("  Y range = [%.4f,%.4f]\n", ymin, ymax);

  // attempt to allocate a 2D array of pixels
  pixels = malloc(sizeof(struct ppm_pixel *) * size);
  if (pixels == NULL) {
    printf("Error: failed malloc.  Exiting...\n");
    exit(1);
  }
  for (int i = 0; i < size; i++) {
    pixels[i] = malloc(sizeof(struct ppm_pixel) * size);
    if (pixels[i] == NULL) {
      printf("Error: failed malloc.  Exiting...\n");
      exit(1);
    }
  }

  // generate palette
  palette = malloc(sizeof(struct ppm_pixel) * maxIterations);
  if (palette == NULL) {
    printf("Error: failed malloc.  Exiting...\n");
    exit(1);
  }
  srand(time(0));
  basered = rand() % 255;
  basegreen = rand() % 255;
  baseblue = rand() % 255;
  for (int i = 0; i < maxIterations; i++) {
    palette[i].red = basered + rand() % 100 - 50;
    palette[i].green = basegreen + rand() % 100 - 50;
    palette[i].blue = baseblue + rand() % 100 - 50;
  }

  gettimeofday(&tstart, NULL);

  // compute image
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      xfrac = (float) i / size;
      yfrac = (float) j / size;
      x0 = xmin + xfrac * (xmax - xmin);
      y0 = ymin + yfrac * (ymax - ymin);

      x = 0;
      y = 0;
      iter = 0;
      while (iter < maxIterations && x*x + y*y < 2*2) {
        xtmp = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = xtmp;
	iter++;
      }
      if (iter < maxIterations) {
        // escaped
	pixels[i][j].red = palette[iter].red;
	pixels[i][j].green = palette[iter].green;
	pixels[i][j].blue = palette[iter].blue;
      } else {
	// did not escape, use color black
        pixels[i][j].red = 0;
        pixels[i][j].green = 0;
        pixels[i][j].blue = 0;
      }
    }
  }

  gettimeofday(&tend, NULL);
  timer = tend.tv_sec - tstart.tv_sec + (tend.tv_usec - tstart.tv_usec)/1.e6;
  printf("Computed mandelbrot set (%dx%d) in %g seconds\n", size, size, timer);

  // write to file
  new_file[0] = '\0';
  sprintf(new_file, "mandelbrot-%d-%lu.ppm", size, time(0));
  printf("Writing file %s\n", new_file);
  write_ppm(new_file, pixels, size, size);

  // free allocated array memory
  for (int i = 0; i < size; i++) {
    free(pixels[i]);
    pixels[i] = NULL;
  }
  free(pixels);
  pixels = NULL;
  free(palette);
  palette = NULL;

  return 0;
}
