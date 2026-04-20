#include "s_matrix.h"

int s_inverse_matrix(matrix_t* A, matrix_t* result) {
  int status = 0;
  matrix_t complements = {0};
  matrix_t transpose = {0};
  double det = 0.0;

  // проверки входных данных
  if (A == NULL || A->matrix == NULL || result == NULL) {
    status = 1;
  } else if (A->rows <= 0 || A->columns <= 0) {
    status = 1;
  } else if (A->rows != A->columns) {
    status = 2;
  } else {
    status = s_determinant(A, &det);
    if (status == 0) {
      if (fabs(det) < 1e-7) {
        status = 2;
      } else {
        // матрица алгебраических дополнений
        status = s_calc_complements(A, &complements);
        if (status == 0) {
          // транспонирование
          status = s_transpose(&complements, &transpose);
          if (status == 0) {
            // умножение на 1/det
            status = s_mult_number(&transpose, 1.0 / det, result);
          }
        }
      }
    }
  }

  if (complements.matrix) {
    s_remove_matrix(&complements);
  }
  if (transpose.matrix) {
    s_remove_matrix(&transpose);
  }

  return status;
}