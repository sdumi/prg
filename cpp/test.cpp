#include <iostream>
#include <check.h>
using namespace std;

START_TEST (test_1)
{
  /* unit test code */
  cout << endl << "my first test" << endl;
  fail("haha");
}
END_TEST
START_TEST (test_2)
{
  fail_unless(1>2, "ok this one is for good");
}
END_TEST
START_TEST (test_3)
{
  fail_unless(1>0, "oh not again");
}
END_TEST
START_TEST (test_4)
{
  cout << endl << "my 4th test" << endl;

  fail_unless(1>3, "oh not again");
}
END_TEST




/////////////////////////////////////////////////
Suite *money_suite (void)
{
  Suite *s = suite_create ("Money");

  /* Core test case */
  TCase *tc_core = tcase_create ("Core");
  tcase_add_test (tc_core, test_1);
  tcase_add_test (tc_core, test_2);
  tcase_add_test (tc_core, test_3);
  tcase_add_test (tc_core, test_4);
  suite_add_tcase (s, tc_core);

  return s;
}
/////////////////////////////////////////////////
int main (void)
{
  int number_failed;
  Suite *s = money_suite ();
  SRunner *sr = srunner_create (s);
  srunner_run_all (sr, CK_NORMAL);//CK_NORMAL, CK_VERBOSE
  number_failed = srunner_ntests_failed (sr);
  srunner_free (sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
