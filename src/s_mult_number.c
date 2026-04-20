#include "s_matrix.h"

int s_mult_number(matrix_t* A, double number, matrix_t* result) {
  if (A == NULL || A->matrix == NULL) {
    return 1;
  }
  if (A->rows <= 0 || A->columns <= 0 || result == NULL) {
    return 1;
  }

  int res = 0;

  int create_status = s_create_matrix(A->rows, A->columns, result);
  if (create_status != 0) {
    res = 1;
  }

  for (int i = 0; i < A->rows && !res; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }

  return res;
}