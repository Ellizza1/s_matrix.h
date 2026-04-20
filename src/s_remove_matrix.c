#include "s_matrix.h"

void s_remove_matrix(matrix_t* A) {
  if (A == NULL || A->matrix == NULL) {
    return;
  }

  for (int i = 0; i < A->rows; i++) {
    if (A->matrix[i] != NULL) {
      free(A->matrix[i]);
      A->matrix[i] = NULL;
    }
  }

  free(A->matrix);
  A->matrix = NULL;

  A->rows = 0;
  A->columns = 0;
}