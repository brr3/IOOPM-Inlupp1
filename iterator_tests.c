#include "iterator.h"
#include "linked_list.h"
#include <CUnit/Basic.h>

int init_suite(void)
{
  return 0;
}

int clean_suite(void)
{
  return 0;
}

void test_create_destroy()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
  CU_ASSERT_PTR_NOT_NULL(iter);
  ioopm_iterator_destroy(iter);
  ioopm_linked_list_destroy(list);
}

void test_has_next()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
  CU_ASSERT_FALSE(ioopm_iterator_has_next(iter));
  elem_t elem = {.integer = 0};
  ioopm_iterator_insert(iter, elem);
  CU_ASSERT_TRUE(ioopm_iterator_has_next(iter));
  ioopm_iterator_destroy(iter);
  ioopm_linked_list_destroy(list);
}

void test_next()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
  ioopm_iterator_destroy(iter);
  ioopm_linked_list_destroy(list);

}

void test_remove()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
  ioopm_iterator_destroy(iter);
  ioopm_linked_list_destroy(list);

}

void test_insert()
{
    ioopm_list_t *list = ioopm_linked_list_create();
    ioopm_list_iterator_t *iter = ioopm_list_iterator(list);

  ioopm_iterator_destroy(iter);
  ioopm_linked_list_destroy(list);

}

void test_reset()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
  ioopm_iterator_destroy(iter);
  ioopm_linked_list_destroy(list);

}

void test_current()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
  ioopm_iterator_destroy(iter);
  ioopm_linked_list_destroy(list);

}

int main(void)
{
  CU_pSuite pSuiteNW = NULL;

  if (CUE_SUCCESS != CU_initialize_registry())
    {
      return CU_get_error();
    }
  pSuiteNW = CU_add_suite("nextWord Suite", init_suite, clean_suite);
  
  if (NULL == pSuiteNW) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  if (
      (NULL == CU_add_test(pSuiteNW, "test of create/destroy", test_create_destroy)) ||
      (NULL == CU_add_test(pSuiteNW, "test of has_next", test_has_next)) ||
      (NULL == CU_add_test(pSuiteNW, "test of next", test_next)) ||
      (NULL == CU_add_test(pSuiteNW, "test of remove", test_remove)) ||
      (NULL == CU_add_test(pSuiteNW, "test of insert", test_insert)) ||
      (NULL == CU_add_test(pSuiteNW, "test of reset", test_reset)) ||
      (NULL == CU_add_test(pSuiteNW, "test of current", test_current))       
      )
    {
      CU_cleanup_registry();
      return CU_get_error();
    }
  
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
 
}
