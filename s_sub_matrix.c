#include "s_matrix.h"

int s_sub_matrix(matrix_t* A, matrix_t* B, matrix_t* result) {
  if (A == NULL || A->matrix == NULL || B == NULL || B->matrix == NULL ||
      result == NULL) {
    return 1;
  }
  if (A->rows <= 0 || A->columns <= 0 || B->rows <= 0 || B->columns <= 0) {
    return 1;
  }

  if (A->rows != B->rows || A->columns != B->columns) {
    return 2;
  }

  int status = 0;
  int create_status = s_create_matrix(A->rows, A->columns, result);
  if (create_status != 0) {
    s_remove_matrix(result);
    status = 1;
  }

  for (int i = 0; i < A->rows && !status; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    }
  }

  return status;
}