#include "tcases.h"

START_TEST(test_create_matrix_normal) {
  matrix_t mat;
  int status = s_create_matrix(3, 4, &mat);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(mat.rows, 3);
  ck_assert_int_eq(mat.columns, 4);
  ck_assert_ptr_nonnull(mat.matrix);
  for (int i = 0; i < 3; i++) {
    ck_assert_ptr_nonnull(mat.matrix[i]);
  }
  s_remove_matrix(&mat);
}
END_TEST

START_TEST(test_create_matrix_1x1) {
  matrix_t mat;
  int status = s_create_matrix(1, 1, &mat);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(mat.rows, 1);
  ck_assert_int_eq(mat.columns, 1);
  ck_assert_ptr_nonnull(mat.matrix);
  ck_assert_ptr_nonnull(mat.matrix[0]);

  s_remove_matrix(&mat);
}
END_TEST

START_TEST(test_create_matrix_zero_rows) {
  matrix_t mat;
  int status = s_create_matrix(0, 5, &mat);

  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_create_matrix_negative_columns) {
  matrix_t mat;
  int status = s_create_matrix(3, -2, &mat);

  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_create_matrix_null_result) {
  int status = s_create_matrix(3, 3, NULL);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_create_matrix_large) {
  matrix_t mat;
  int status = s_create_matrix(100, 100, &mat);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(mat.rows, 100);
  ck_assert_int_eq(mat.columns, 100);
  ck_assert_ptr_nonnull(mat.matrix);

  s_remove_matrix(&mat);
}
END_TEST

START_TEST(test_create_matrix_double_create) {
  matrix_t mat;

  int status1 = s_create_matrix(2, 2, &mat);
  ck_assert_int_eq(status1, 0);
  int status2 = s_create_matrix(3, 3, &mat);
  ck_assert_int_eq(status2, 0);
  ck_assert_int_eq(mat.rows, 3);
  ck_assert_int_eq(mat.columns, 3);

  s_remove_matrix(&mat);
}
END_TEST

START_TEST(test_create_matrix_initialization) {
  matrix_t mat;
  int status = s_create_matrix(3, 3, &mat);

  ck_assert_int_eq(status, 0);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      double val = mat.matrix[i][j];
      (void)val;
    }
  }

  s_remove_matrix(&mat);
}
END_TEST

START_TEST(test_create_matrix_huge) {
  matrix_t mat;

  int status = s_create_matrix(1000, 1000, &mat);

  if (status == 0) {
    ck_assert_int_eq(mat.rows, 1000);
    ck_assert_int_eq(mat.columns, 1000);
    ck_assert_ptr_nonnull(mat.matrix);
    s_remove_matrix(&mat);
  } else {
    ck_assert_int_eq(status, 1);
  }
}
END_TEST

START_TEST(test_create_matrix_zero_rows_positive_columns) {
  matrix_t mat = {NULL, 121, 121};
  int status = s_create_matrix(0, 5, &mat);

  ck_assert_int_eq(status, 1);

  ck_assert_int_eq(mat.rows, 0);
  ck_assert_int_eq(mat.columns, 0);
  ck_assert_ptr_null(mat.matrix);
}
END_TEST

START_TEST(test_create_matrix_positive_rows_zero_columns) {
  matrix_t mat = {NULL, 133, 133};
  int status = s_create_matrix(5, 0, &mat);

  ck_assert_int_eq(status, 1);
  ck_assert_int_eq(mat.rows, 0);
  ck_assert_int_eq(mat.columns, 0);
  ck_assert_ptr_null(mat.matrix);
}
END_TEST

START_TEST(test_create_matrix_zero_both) {
  matrix_t mat = {NULL, 145, 145};
  int status = s_create_matrix(0, 0, &mat);

  ck_assert_int_eq(status, 1);
  ck_assert_int_eq(mat.rows, 0);
  ck_assert_int_eq(mat.columns, 0);
  ck_assert_ptr_null(mat.matrix);
}
END_TEST

TCase* tcase_create_matrix(void) {
  TCase* tc = tcase_create("s_create_matrix");

  tcase_add_test(tc, test_create_matrix_normal);
  tcase_add_test(tc, test_create_matrix_1x1);
  tcase_add_test(tc, test_create_matrix_zero_rows);
  tcase_add_test(tc, test_create_matrix_negative_columns);
  tcase_add_test(tc, test_create_matrix_null_result);
  tcase_add_test(tc, test_create_matrix_large);
  tcase_add_test(tc, test_create_matrix_double_create);
  tcase_add_test(tc, test_create_matrix_initialization);
  tcase_add_test(tc, test_create_matrix_huge);
  tcase_add_test(tc, test_create_matrix_zero_rows_positive_columns);
  tcase_add_test(tc, test_create_matrix_positive_rows_zero_columns);
  tcase_add_test(tc, test_create_matrix_zero_both);

  return tc;
}

START_TEST(test_eq_matrix_equal) {
  matrix_t A, B;
  s_create_matrix(2, 2, &A);
  s_create_matrix(2, 2, &B);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      A.matrix[i][j] = i + j + 0.123456;
      B.matrix[i][j] = i + j + 0.123456;
    }
  }

  ck_assert_int_eq(s_eq_matrix(&A, &B), SUCCESS);

  s_remove_matrix(&A);
  s_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_different_size) {
  matrix_t A, B;
  s_create_matrix(2, 2, &A);
  s_create_matrix(3, 3, &B);

  ck_assert_int_eq(s_eq_matrix(&A, &B), FAILURE);

  s_remove_matrix(&A);
  s_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_different_elements) {
  matrix_t A, B;
  s_create_matrix(2, 2, &A);
  s_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1.0;
  B.matrix[0][0] = 1.000001;

  ck_assert_int_eq(s_eq_matrix(&A, &B), FAILURE);

  s_remove_matrix(&A);
  s_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_within_precision) {
  matrix_t A, B;
  s_create_matrix(1, 1, &A);
  s_create_matrix(1, 1, &B);

  A.matrix[0][0] = 1.123456789;
  B.matrix[0][0] = 1.123456;

  ck_assert_int_eq(s_eq_matrix(&A, &B), SUCCESS);

  s_remove_matrix(&A);
  s_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_null) {
  matrix_t A;
  s_create_matrix(2, 2, &A);

  ck_assert_int_eq(s_eq_matrix(NULL, &A), FAILURE);
  ck_assert_int_eq(s_eq_matrix(&A, NULL), FAILURE);
  ck_assert_int_eq(s_eq_matrix(NULL, NULL), FAILURE);

  s_remove_matrix(&A);
}
END_TEST

START_TEST(test_eq_matrix_invalid) {
  matrix_t A = {NULL, 2, 2};
  matrix_t B = {NULL, 2, 2};

  ck_assert_int_eq(s_eq_matrix(&A, &B), FAILURE);
}
END_TEST

START_TEST(test_eq_matrix_large) {
  matrix_t A, B;
  s_create_matrix(50, 50, &A);
  s_create_matrix(50, 50, &B);

  for (int i = 0; i < 50; i++) {
    for (int j = 0; j < 50; j++) {
      double val = (i + j) * 0.5;
      A.matrix[i][j] = val;
      B.matrix[i][j] = val;
    }
  }

  ck_assert_int_eq(s_eq_matrix(&A, &B), SUCCESS);

  s_remove_matrix(&A);
  s_remove_matrix(&B);
}
END_TEST

TCase* tcase_eq_matrix(void) {
  TCase* tc = tcase_create("s_eq_matrix");

  tcase_add_test(tc, test_eq_matrix_equal);
  tcase_add_test(tc, test_eq_matrix_different_size);
  tcase_add_test(tc, test_eq_matrix_different_elements);
  tcase_add_test(tc, test_eq_matrix_within_precision);
  tcase_add_test(tc, test_eq_matrix_null);
  tcase_add_test(tc, test_eq_matrix_invalid);
  tcase_add_test(tc, test_eq_matrix_large);

  return tc;
}

START_TEST(test_remove_matrix_normal) {
  matrix_t mat;
  s_create_matrix(3, 3, &mat);
  ck_assert_ptr_nonnull(mat.matrix);
  ck_assert_int_eq(mat.rows, 3);
  ck_assert_int_eq(mat.columns, 3);

  s_remove_matrix(&mat);

  ck_assert_ptr_null(mat.matrix);
  ck_assert_int_eq(mat.rows, 0);
  ck_assert_int_eq(mat.columns, 0);
}
END_TEST

START_TEST(test_remove_matrix_null) {
  matrix_t mat = {NULL, 0, 0};

  s_remove_matrix(&mat);

  ck_assert_ptr_null(mat.matrix);
  ck_assert_int_eq(mat.rows, 0);
  ck_assert_int_eq(mat.columns, 0);
}
END_TEST

START_TEST(test_remove_matrix_double_free) {
  matrix_t mat;
  s_create_matrix(2, 2, &mat);
  s_remove_matrix(&mat);
  s_remove_matrix(&mat);

  ck_assert_ptr_null(mat.matrix);
  ck_assert_int_eq(mat.rows, 0);
  ck_assert_int_eq(mat.columns, 0);
}
END_TEST

START_TEST(test_remove_matrix_null_pointer) {
  s_remove_matrix(NULL);

  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_remove_matrix_reuse) {
  matrix_t mat;

  for (int i = 0; i < 5; i++) {
    s_create_matrix(i + 1, i + 1, &mat);
    ck_assert_ptr_nonnull(mat.matrix);
    s_remove_matrix(&mat);
    ck_assert_ptr_null(mat.matrix);
  }
}
END_TEST

TCase* tcase_remove_matrix(void) {
  TCase* tc = tcase_create("s_remove_matrix");

  tcase_add_test(tc, test_remove_matrix_normal);
  tcase_add_test(tc, test_remove_matrix_null);
  tcase_add_test(tc, test_remove_matrix_double_free);
  tcase_add_test(tc, test_remove_matrix_null_pointer);
  tcase_add_test(tc, test_remove_matrix_reuse);

  return tc;
}

START_TEST(test_sum_matrix_normal) {
  matrix_t A, B, result;
  s_create_matrix(2, 2, &A);
  s_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  B.matrix[0][0] = 0.5;
  B.matrix[0][1] = 1.5;
  B.matrix[1][0] = 2.5;
  B.matrix[1][1] = 3.5;

  int status = s_sum_matrix(&A, &B, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_double_eq_tol(result.matrix[0][0], 1.5, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][1], 3.5, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][0], 5.5, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][1], 7.5, 1e-6);

  s_remove_matrix(&A);
  s_remove_matrix(&B);
  s_remove_matrix(&result);
}
END_TEST

START_TEST(test_sum_matrix_negative) {
  matrix_t A, B, result;
  s_create_matrix(1, 3, &A);
  s_create_matrix(1, 3, &B);

  A.matrix[0][0] = -1.0;
  A.matrix[0][1] = -2.0;
  A.matrix[0][2] = -3.0;
  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 2.0;
  B.matrix[0][2] = 3.0;

  int status = s_sum_matrix(&A, &B, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_double_eq_tol(result.matrix[0][0], 0.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][1], 0.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][2], 0.0, 1e-6);

  s_remove_matrix(&A);
  s_remove_matrix(&B);
  s_remove_matrix(&result);
}
END_TEST

START_TEST(test_sum_matrix_different_size) {
  matrix_t A, B, result;
  s_create_matrix(2, 2, &A);
  s_create_matrix(3, 3, &B);

  int status = s_sum_matrix(&A, &B, &result);

  ck_assert_int_eq(status, 2);

  s_remove_matrix(&A);
  s_remove_matrix(&B);
}
END_TEST

START_TEST(test_sum_matrix_invalid_A) {
  matrix_t A = {NULL, 0, 0};
  matrix_t B, result;
  s_create_matrix(2, 2, &B);

  int status = s_sum_matrix(&A, &B, &result);

  ck_assert_int_eq(status, 1);

  s_remove_matrix(&B);
}
END_TEST

START_TEST(test_sum_matrix_null_result) {
  matrix_t A, B;
  s_create_matrix(2, 2, &A);
  s_create_matrix(2, 2, &B);

  int status = s_sum_matrix(&A, &B, NULL);

  ck_assert_int_eq(status, 1);

  s_remove_matrix(&A);
  s_remove_matrix(&B);
}
END_TEST

START_TEST(test_sum_matrix_large) {
  matrix_t A, B, result;
  int rows = 10, cols = 10;
  s_create_matrix(rows, cols, &A);
  s_create_matrix(rows, cols, &B);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      A.matrix[i][j] = i + j;
      B.matrix[i][j] = (i + j) * 0.5;
    }
  }

  int status = s_sum_matrix(&A, &B, &result);

  ck_assert_int_eq(status, 0);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      double expected = (i + j) * 1.5;
      ck_assert_double_eq_tol(result.matrix[i][j], expected, 1e-6);
    }
  }

  s_remove_matrix(&A);
  s_remove_matrix(&B);
  s_remove_matrix(&result);
}
END_TEST

START_TEST(test_sum_matrix_zero) {
  matrix_t A, B, result;
  s_create_matrix(3, 3, &A);
  s_create_matrix(3, 3, &B);

  int status = s_sum_matrix(&A, &B, &result);

  ck_assert_int_eq(status, 0);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], 0.0, 1e-6);
    }
  }

  s_remove_matrix(&A);
  s_remove_matrix(&B);
  s_remove_matrix(&result);
}
END_TEST

TCase* tcase_sum_matrix(void) {
  TCase* tc = tcase_create("s_sum_matrix");

  tcase_add_test(tc, test_sum_matrix_normal);
  tcase_add_test(tc, test_sum_matrix_negative);
  tcase_add_test(tc, test_sum_matrix_different_size);
  tcase_add_test(tc, test_sum_matrix_invalid_A);
  tcase_add_test(tc, test_sum_matrix_null_result);
  tcase_add_test(tc, test_sum_matrix_large);
  tcase_add_test(tc, test_sum_matrix_zero);

  return tc;
}

START_TEST(test_sub_matrix_normal) {
  matrix_t A, B, result;
  s_create_matrix(2, 2, &A);
  s_create_matrix(2, 2, &B);

  A.matrix[0][0] = 5.0;
  A.matrix[0][1] = 6.0;
  A.matrix[1][0] = 7.0;
  A.matrix[1][1] = 8.0;

  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 2.0;
  B.matrix[1][0] = 3.0;
  B.matrix[1][1] = 4.0;

  int status = s_sub_matrix(&A, &B, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_double_eq_tol(result.matrix[0][0], 4.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][1], 4.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][0], 4.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][1], 4.0, 1e-6);

  s_remove_matrix(&A);
  s_remove_matrix(&B);
  s_remove_matrix(&result);
}
END_TEST

START_TEST(test_sub_matrix_negative) {
  matrix_t A, B, result;
  s_create_matrix(1, 3, &A);
  s_create_matrix(1, 3, &B);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  B.matrix[0][0] = 4.0;
  B.matrix[0][1] = 5.0;
  B.matrix[0][2] = 6.0;

  int status = s_sub_matrix(&A, &B, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_double_eq_tol(result.matrix[0][0], -3.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][1], -3.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][2], -3.0, 1e-6);

  s_remove_matrix(&A);
  s_remove_matrix(&B);
  s_remove_matrix(&result);
}
END_TEST

START_TEST(test_sub_matrix_same) {
  matrix_t A, result;
  s_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1.5;
  A.matrix[0][1] = 2.5;
  A.matrix[1][0] = 3.5;
  A.matrix[1][1] = 4.5;

  int status = s_sub_matrix(&A, &A, &result);

  ck_assert_int_eq(status, 0);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], 0.0, 1e-6);
    }
  }

  s_remove_matrix(&A);
  s_remove_matrix(&result);
}
END_TEST

START_TEST(test_sub_matrix_zero) {
  matrix_t A, B, result;
  s_create_matrix(2, 2, &A);
  s_create_matrix(2, 2, &B);

  A.matrix[0][0] = 10.0;
  A.matrix[0][1] = 20.0;
  A.matrix[1][0] = 30.0;
  A.matrix[1][1] = 40.0;

  int status = s_sub_matrix(&A, &B, &result);

  ck_assert_int_eq(status, 0);

  ck_assert_double_eq_tol(result.matrix[0][0], 10.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][1], 20.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][0], 30.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][1], 40.0, 1e-6);

  s_remove_matrix(&A);
  s_remove_matrix(&B);
  s_remove_matrix(&result);
}
END_TEST

START_TEST(test_sub_matrix_different_size) {
  matrix_t A, B, result;
  s_create_matrix(2, 3, &A);
  s_create_matrix(3, 2, &B);

  int status = s_sub_matrix(&A, &B, &result);

  ck_assert_int_eq(status, 2);

  s_remove_matrix(&A);
  s_remove_matrix(&B);
}
END_TEST

START_TEST(test_sub_matrix_invalid_B) {
  matrix_t A, B = {NULL, 0, 0}, result;
  s_create_matrix(2, 2, &A);

  int status = s_sub_matrix(&A, &B, &result);

  ck_assert_int_eq(status, 1);

  s_remove_matrix(&A);
}
END_TEST

START_TEST(test_sub_matrix_precision) {
  matrix_t A, B, result;
  s_create_matrix(1, 2, &A);
  s_create_matrix(1, 2, &B);

  A.matrix[0][0] = 1.123456;
  A.matrix[0][1] = 2.123456;
  B.matrix[0][0] = 1.123455;
  B.matrix[0][1] = 2.123455;

  int status = s_sub_matrix(&A, &B, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_double_eq_tol(result.matrix[0][0], 0.000001, 1e-9);
  ck_assert_double_eq_tol(result.matrix[0][1], 0.000001, 1e-9);

  s_remove_matrix(&A);
  s_remove_matrix(&B);
  s_remove_matrix(&result);
}
END_TEST

TCase* tcase_sub_matrix(void) {
  TCase* tc = tcase_create("s_sub_matrix");

  tcase_add_test(tc, test_sub_matrix_normal);
  tcase_add_test(tc, test_sub_matrix_negative);
  tcase_add_test(tc, test_sub_matrix_same);
  tcase_add_test(tc, test_sub_matrix_zero);
  tcase_add_test(tc, test_sub_matrix_different_size);
  tcase_add_test(tc, test_sub_matrix_invalid_B);
  tcase_add_test(tc, test_sub_matrix_precision);

  return tc;
}

START_TEST(test_mult_number_positive) {
  matrix_t A, result;
  s_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  int status = s_mult_number(&A, 2.5, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_double_eq_tol(result.matrix[0][0], 2.5, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][1], 5.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][0], 7.5, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][1], 10.0, 1e-6);

  s_remove_matrix(&A);
  s_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_number_negative) {
  matrix_t A, result;
  s_create_matrix(1, 3, &A);

  A.matrix[0][0] = 2.0;
  A.matrix[0][1] = -4.0;
  A.matrix[0][2] = 6.0;

  int status = s_mult_number(&A, -3.0, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_double_eq_tol(result.matrix[0][0], -6.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][1], 12.0, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][2], -18.0, 1e-6);

  s_remove_matrix(&A);
  s_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_number_zero) {
  matrix_t A, result;
  s_create_matrix(2, 2, &A);

  A.matrix[0][0] = 100.0;
  A.matrix[0][1] = 200.0;
  A.matrix[1][0] = 300.0;
  A.matrix[1][1] = 400.0;

  int status = s_mult_number(&A, 0.0, &result);

  ck_assert_int_eq(status, 0);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], 0.0, 1e-6);
    }
  }

  s_remove_matrix(&A);
  s_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_number_fraction) {
  matrix_t A, result;
  s_create_matrix(1, 2, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 3.0;

  int status = s_mult_number(&A, 0.333333, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_double_eq_tol(result.matrix[0][0], 0.333333, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][1], 0.999999, 1e-6);

  s_remove_matrix(&A);
  s_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_number_invalid_matrix) {
  matrix_t A = {NULL, 0, 0}, result;

  int status = s_mult_number(&A, 5.0, &result);

  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_mult_number_null_result) {
  matrix_t A;
  s_create_matrix(2, 2, &A);

  int status = s_mult_number(&A, 5.0, NULL);

  ck_assert_int_eq(status, 1);

  s_remove_matrix(&A);
}
END_TEST

START_TEST(test_mult_number_identity) {
  matrix_t A, result;
  s_create_matrix(3, 3, &A);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = (i == j) ? 1.0 : 0.0;
    }
  }

  int status = s_mult_number(&A, 7.0, &result);

  ck_assert_int_eq(status, 0);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      double expected = (i == j) ? 7.0 : 0.0;
      ck_assert_double_eq_tol(result.matrix[i][j], expected, 1e-6);
    }
  }

  s_remove_matrix(&A);
  s_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_number_by_one) {
  matrix_t A, result;
  s_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1.5;
  A.matrix[0][1] = 2.5;
  A.matrix[1][0] = 3.5;
  A.matrix[1][1] = 4.5;

  int status = s_mult_number(&A, 1.0, &result);

  ck_assert_int_eq(status, 0);

  ck_assert_double_eq_tol(result.matrix[0][0], 1.5, 1e-6);
  ck_assert_double_eq_tol(result.matrix[0][1], 2.5, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][0], 3.5, 1e-6);
  ck_assert_double_eq_tol(result.matrix[1][1], 4.5, 1e-6);

  s_remove_matrix(&A);
  s_remove_matrix(&result);
}
END_TEST

TCase* tcase_mult_number(void) {
  TCase* tc = tcase_create("s_mult_number");

  tcase_add_test(tc, test_mult_number_positive);
  tcase_add_test(tc, test_mult_number_negative);
  tcase_add_test(tc, test_mult_number_zero);
  tcase_add_test(tc, test_mult_number_fraction);
  tcase_add_test(tc, test_mult_number_invalid_matrix);
  tcase_add_test(tc, test_mult_number_null_result);
  tcase_add_test(tc, test_mult_number_identity);
  tcase_add_test(tc, test_mult_number_by_one);

  return tc;
}