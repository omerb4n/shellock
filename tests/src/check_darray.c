#include <check.h>
#include "../../src/darray.h"        
#include <stdlib.h>


START_TEST(test_darray_new) {
  DArray_t darray = darray_new(0);

  ck_assert_int_eq(darray_size(darray), 0);
  darray_free(darray);
} END_TEST

START_TEST(test_darray_set) {
  DArray_t darray = darray_new(1);

  ck_assert_int_eq(darray_size(darray), 1);
  darray_set(darray, 0, 0);
  ck_assert_int_eq(darray_size(darray), 1);
  ck_assert_int_eq(darray_data(darray)[0], 0);

  /* Check expanding when needed */
  darray_set(darray, 1, 1);
  ck_assert_int_eq(darray_size(darray), 2);
  ck_assert_int_eq(darray_data(darray)[1], 1);

  /* Check expanding by size*2 */
  darray_set(darray, 2, 2);
  ck_assert_int_eq(darray_size(darray), 4);
  ck_assert_int_eq(darray_data(darray)[2], 2);

  /* Check expanding by requested index */
  darray_set(darray, 10, 10);
  ck_assert_int_eq(darray_size(darray), 10 + 1);
  ck_assert_int_eq(darray_data(darray)[10], 10);
  darray_free(darray);
} END_TEST


Suite *darray_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("darray");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_darray_new);
  tcase_add_test(tc_core, test_darray_set);
  suite_add_tcase(s, tc_core);

  return s;
}

int main() {
  int no_failed = 0;                   
  Suite *s;                            
  SRunner *runner;                     

  s = darray_suite();                   
  runner = srunner_create(s);          

  srunner_run_all(runner, CK_NORMAL);  
  no_failed = srunner_ntests_failed(runner); 
  srunner_free(runner);                      
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;  
}