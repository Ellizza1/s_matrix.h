#include "s_matrix.h"

int s_create_matrix(int rows, int columns, matrix_t* result) {
  if (rows <= 0 || columns <= 0 || result == NULL) {
    if (result != NULL) {
      result->matrix = NULL;
      result->rows = 0;
      result->columns = 0;
    }
    return 1;
  }

  result->rows = rows;
  result->columns = columns;
  result->matrix = NULL;

  int status = 0;

  result->matrix = (double**)malloc(rows * sizeof(double*));
  if (result->matrix == NULL) {
    result->rows = 0;
    result->columns = 0;
    return 1;
  }

  for (int i = 0; i < rows && !status; i++) {
    result->matrix[i] = (double*)malloc(columns * sizeof(double));
    if (result->matrix[i] == NULL) {
      matrix_init(result, i);
      return 1;
    }

    for (int j = 0; j < columns && !status; j++) {
      result->matrix[i][j] = 0.0;
    }
  }

  return status;
}
