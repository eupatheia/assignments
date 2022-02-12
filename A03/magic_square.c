//---------------------------------------------------------------------
// magic_square.c
// CS223 - Spring 2022
// Identify whether a matrix is a magic square
// Name: Jasmine Lei
// Date: 11 February 2022
//

#include <stdio.h>
#include <stdlib.h>

int main() {
  int rows, cols;
  int magic_const = 0;
  int* matrix = NULL;

  scanf(" %d", &rows);
  scanf(" %d", &cols);

  // must be an n x n matrix
  if (rows != cols) {
    printf("M is NOT a magic square!\n");
    exit(0);
  }

  matrix = malloc(sizeof(int) * rows * rows);
  if (matrix == NULL) {
    printf("Malloc error.  Exiting...\n");
    exit(1);
  }
  // read in values
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < rows; j++) {
      scanf(" %d", &matrix[i * rows + j]);
    }
  }

  // re-print matrix to make sure everything was read correctly
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < rows; j++) {
      printf("%d ", matrix[i * rows + j]);
    }
    printf("\n");
  }

  // get sum of first row
  for (int i = 0; i < rows; i++) {
    magic_const += matrix[i];
  }
  // printf("magic constant = %d\n", magic_const);

  // check for matching sum in all other rows
  for (int i = 1; i < rows; i++) {
    int sum = 0;
    for (int j = 0; j < rows; j++) {
      sum += matrix[i * rows + j];
    }
    // printf("row sum = %d\n", sum);
    if (sum != magic_const) {
      printf("M is NOT a magic square!\n");
      free(matrix);
      matrix = NULL;
      exit(0);
    }
  }

  // check for matching sum in every column
  for (int i = 0; i < rows; i++) {
    int sum = 0;
    for (int j = 0; j < rows; j++) {
      sum += matrix[j * rows + i];
    }
    // printf("col sum = %d\n", sum);
    if (sum != magic_const) {
      printf("M is NOT a magic square!\n");
      free(matrix);
      matrix = NULL;
      exit(0);
    }
  }

  // check for matching sum in both diagonals
  int sum = 0;
  for (int i = 0; i < rows; i++) {
    sum += matrix[i * rows + i];
  }
  // printf("diagonal sum = %d\n", sum);
  if (sum != magic_const) {
    printf("M is NOT a magic square!\n");
    free(matrix);
    matrix = NULL;
    exit(0);
  }

  sum = 0;
  for (int i = 0; i < rows; i++) {
    sum += matrix[i * rows + (rows - 1 - i)];
  }
  // printf("diagonal sum = %d\n", sum);
  if (sum != magic_const) {
    printf("M is NOT a magic square!\n");
    free(matrix);
    matrix = NULL;
    exit(0);
  }

  printf("M is a magic square (magic constant = %d)\n", magic_const);

  free(matrix);
  matrix = NULL;

  return 0;
}
