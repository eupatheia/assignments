#ifndef SINGLE_MANDELBROT_H
#define SINGLE_MANDELBROT_H

extern void generatePalette(struct ppm_pixel * palette, int maxIterations);
extern void computeMandelbrot(int size, int i, int j, float xmin, float xmax,
    float ymin, float ymax, int maxIterations, struct ppm_pixel ** pixels,
    struct ppm_pixel * palette);

#endif
