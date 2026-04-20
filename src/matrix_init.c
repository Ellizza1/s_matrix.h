#include "s_matrix.h"

void matrix_init(matrix_t* result, int i) {
  for (int j = 0; j < i; j++) {
    free(result->matrix[j]);
  }
  free(result->matrix);
  result->matrix = NULL;
  result->rows = 0;
  result->columns = 0;
}