#include "s_matrix.h"

int s_transpose(matrix_t* A, matrix_t* result) {
  if (!A || !A->matrix || !result) {
    return 1;
  }
  if (A->rows <= 0 || A->columns <= 0) {
    return 1;
  }

  int create_status = s_create_matrix(A->columns, A->rows, result);
  if (create_status != 0) {
    return 1;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[j][i] = A->matrix[i][j];
    }
  }

  return 0;
}
