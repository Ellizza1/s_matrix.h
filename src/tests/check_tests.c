#include "tcases.h"

Suite* s_matrix_suite(void) {
  Suite* s = suite_create("s_matrix");

  TCase* tc_create = tcase_create_matrix();
  suite_add_tcase(s, tc_create);

  TCase* tc_eq = tcase_eq_matrix();
  suite_add_tcase(s, tc_eq);

  TCase* tc_remove = tcase_remove_matrix();
  suite_add_tcase(s, tc_remove);

  TCase* tc_sum = tcase_sum_matrix();
  suite_add_tcase(s, tc_sum);

  TCase* tc_sub = tcase_sub_matrix();
  suite_add_tcase(s, tc_sub);

  TCase* tc_mult_num = tcase_mult_number();
  suite_add_tcase(s, tc_mult_num);

  TCase* tc_mult_mat = tcase_mult_matrix();
  suite_add_tcase(s, tc_mult_mat);

  TCase* tc_transpose = tcase_transpose();
  suite_add_tcase(s, tc_transpose);

  TCase* tc_det = tcase_determinant();
  suite_add_tcase(s, tc_det);

  TCase* tc_complements = tcase_calc_complements();
  suite_add_tcase(s, tc_complements);

  TCase* tc_inverse = tcase_inverse_matrix();
  suite_add_tcase(s, tc_inverse);

  return s;
}

int main(void) {
  int number_failed;
  Suite* s;
  SRunner* sr;

  s = s_matrix_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);

  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
