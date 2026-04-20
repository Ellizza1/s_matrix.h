#include "s_matrix.h"

int s_get_minor(matrix_t* A, int row, int column, matrix_t* minor) {
  // Проверки параметров
  if (!A || !minor || !A->matrix) {
    return 1;
  }
  if (A->rows != A->columns || A->rows <= 1) {
    return 1;
  }  // Минор определен только для квадратных
  if (row < 0 || row >= A->rows || column < 0 || column >= A->columns) {
    return 1;
  }

  int n = A->rows;
  int status = s_create_matrix(n - 1, n - 1, minor);
  if (status != 0) return 1;

  int mi = 0, mj = 0;
  for (int i = 0; i < n; i++) {
    if (i == row) continue;

    mj = 0;
    for (int j = 0; j < n; j++) {
      if (j == column) continue;

      minor->matrix[mi][mj] = A->matrix[i][j];
      mj++;
    }
    mi++;
  }

  return 0;
}