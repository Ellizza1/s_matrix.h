#include "s_matrix.h"

int s_determinant(matrix_t* A, double* result) {
  if (A == NULL || A->matrix == NULL || result == NULL) {
    return 1;
  }

  if (A->rows <= 0 || A->columns <= 0) {
    return 1;
  }

  if (A->rows != A->columns) {
    return 2;
  }

  int n = A->rows;
  double det = 1.0;

  matrix_t tmp = {0};
  if (s_create_matrix(n, n, &tmp) != 0) {
    return 1;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      tmp.matrix[i][j] = A->matrix[i][j];
    }
  }

  for (int i = 0; i < n; i++) {
    // поиск максимального элемента в колонке
    int max_row = i;
    for (int k = i + 1; k < n; k++) {
      if (fabs(tmp.matrix[k][i]) > fabs(tmp.matrix[max_row][i])) {
        max_row = k;
      }
    }

    // если столбец нулевой  det = 0
    if (fabs(tmp.matrix[max_row][i]) < 1e-7) {
      det = 0.0;
      break;
    }

    // меняем строки местами
    if (i != max_row) {
      double* temp_row = tmp.matrix[i];
      tmp.matrix[i] = tmp.matrix[max_row];
      tmp.matrix[max_row] = temp_row;
      det *= -1;
    }

    // умножаем на диагональный элемент
    det *= tmp.matrix[i][i];

    // обнуляем элементы ниже
    for (int k = i + 1; k < n; k++) {
      double factor = tmp.matrix[k][i] / tmp.matrix[i][i];

      for (int j = i; j < n; j++) {
        tmp.matrix[k][j] -= factor * tmp.matrix[i][j];
      }
    }
  }

  *result = det;

  s_remove_matrix(&tmp);
  return 0;
}