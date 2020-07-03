#include <check.h>
#include "../../src/darray.h"        
#include <stdlib.h>


START_TEST(test_darray_init) {
  DArray darray;

  darray_init(&darray, 0);
  ck_assert_int_eq(darray.size, 0);
  darray_free(&darray);
} END_TEST

START_TEST(test_darray_set) {
  DArray darray;

  darray_init(&darray, 1);
  ck_assert_int_eq(darray.size, 1);
  darray_set(&darray, 0, 1);
  ck_assert_int_eq(darray.size, 1);
  darray_set(&darray, 2, 1);
  ck_assert_int_eq(darray.size, 2);
  darray_free(&darray);
} END_TEST


Suite *darray_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("darray");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_darray_init);
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