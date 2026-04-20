#include "s_matrix.h"

int s_calc_complements(matrix_t* A, matrix_t* result) {
  if (A == NULL || result == NULL || A->matrix == NULL) {
    return 1;
  }

  if (A->rows != A->columns) {
    return 2;
  }

  int status = s_create_matrix(A->rows, A->columns, result);
  if (status != 0) {
    return status;
  }

  if (A->rows == 1) {
    result->matrix[0][0] = 1.0;
    return 0;
  }

  for (int i = 0; i < A->rows && status == 0; i++) {
    for (int j = 0; j < A->columns && status == 0; j++) {
      matrix_t minor = {0};
      double minor_det = 0.0;

      // Получаем минор (матрица n-1 x n-1)
      status = s_get_minor(A, i, j, &minor);

      if (status == 0) {
        // Считаем определитель минора
        status = s_determinant(&minor, &minor_det);
      }

      if (status == 0) {
        //  M_ij * (-1)^(i+j)
        double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
        result->matrix[i][j] = sign * minor_det;
      }

      s_remove_matrix(&minor);
    }
  }

  if (status != 0) {
    s_remove_matrix(result);
  }

  return status;
}