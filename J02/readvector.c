#include <stdio.h>
#include <stdlib.h>

// readvector opens and reads the given file
// The size of the vector should be stored in the parameter size
// The values should be returned in a flat float array
float* readvector(const char* filename, int *size) {
  FILE* file;
  char buffer[256];
  int num;
  float* vector;

  file = fopen(filename, "r");
  if (file == NULL) {
    printf("File not found.  Exiting...");
    exit(0);
  }
  fgets(buffer, 256, file);
  sscanf(buffer, "%d", &num);
  vector = malloc(sizeof(float) * num);

  for (int i = 0; i < num; i++) {
    fgets(buffer, 256, file);
    sscanf(buffer, "%f", &vector[i]);
  }
  fclose(file);
  *size = num;
  return vector;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    printf("usage: readvector <filename>\n");
    exit(0);
  }

  int size = 0;
  float* vector = readvector(argv[1], &size);

  for (int i = 0; i < size; i++) {
    printf("%f\n", vector[i]);
  }

  free(vector);
  vector = NULL;
  return 0;
}
