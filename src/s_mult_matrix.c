#include "s_matrix.h"

int s_mult_matrix(matrix_t* A, matrix_t* B, matrix_t* result) {
  if (A == NULL || B == NULL || result == NULL || A->matrix == NULL ||
      B->matrix == NULL) {
    return 1;
  }
  if (A->rows <= 0 || A->columns <= 0 || B->rows <= 0 || B->columns <= 0) {
    return 1;
  }

  if (A->columns != B->rows) {
    return 2;
  }
  int res = 0;

  int create_status = s_create_matrix(A->rows, B->columns, result);
  if (create_status != 0) {
    s_remove_matrix(result);
    res = 1;
  }

  for (int i = 0; i < A->rows && !res; i++) {
    for (int j = 0; j < B->columns; j++) {
      result->matrix[i][j] = 0.0;

      for (int k = 0; k < A->columns; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }

  return res;
}