#ifndef TCASES_H
#define TCASES_H

#include <check.h>
#include <math.h>
#include <stdlib.h>

#include "../s_matrix.h"

TCase* tcase_create_matrix(void);
TCase* tcase_eq_matrix(void);
TCase* tcase_remove_matrix(void);
TCase* tcase_sum_matrix(void);
TCase* tcase_sub_matrix(void);
TCase* tcase_mult_number(void);
TCase* tcase_mult_matrix(void);
TCase* tcase_transpose(void);
TCase* tcase_determinant(void);
TCase* tcase_calc_complements(void);
TCase* tcase_inverse_matrix(void);

#endif
