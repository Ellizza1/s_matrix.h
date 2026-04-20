#include "s_matrix.h"

int s_eq_matrix(matrix_t* A, matrix_t* B) {
  int result = SUCCESS;
  if (A == NULL || A->matrix == NULL || B == NULL || B->matrix == NULL) {
    return FAILURE;
  }
  if (A->rows <= 0 || A->columns <= 0 || B->rows <= 0 || B->columns <= 0) {
    return FAILURE;
  }
  if (result == SUCCESS) {
    if (A->rows != B->rows || A->columns != B->columns) {
      result = FAILURE;
    }
  }

  if (result == SUCCESS) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 0.999999e-6) {
          result = FAILURE;
        }
      }
    }
  }

  return result;
}
