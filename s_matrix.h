#ifndef S_MATRIX_H
#define S_MATRIX_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct {
  double** matrix;
  int rows;
  int columns;
} matrix_t;

int s_transpose(matrix_t* A, matrix_t* result);
int s_sub_matrix(matrix_t* A, matrix_t* B, matrix_t* result);
int s_sum_matrix(matrix_t* A, matrix_t* B, matrix_t* result);
void s_remove_matrix(matrix_t* A);
int s_create_matrix(int rows, int columns, matrix_t* result);

#endif