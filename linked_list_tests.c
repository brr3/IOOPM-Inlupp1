#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "CUnit/Basic.h"
#include "linked_list.h"


int init_suite(void)
{
  return 0;
}

int clean_suite(void)
{
  return 0;
}


static void test_create_destroy()
{
   ioopm_list_t *list = ioopm_linked_list_create();
   CU_ASSERT_PTR_NOT_NULL(list);
   ioopm_linked_list_destroy(list);
}


static void test_insert_prepend()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  for (int i = 0; i < nodes; i++)
    {
      ioopm_linked_list_prepend(list, i);
      CU_ASSERT_TRUE(ioopm_linked_list_get(list, 0) == i);
      CU_ASSERT_TRUE(ioopm_linked_list_contains(list, i));
    }
  for (int i = nodes - 1; i >= 0; i--)
    {
      ioopm_linked_list_prepend(list, i);
      CU_ASSERT_TRUE(ioopm_linked_list_get(list, 0) == i);
      CU_ASSERT_TRUE(ioopm_linked_list_contains(list, i));
    }
  ioopm_linked_list_destroy(list);
}


static void test_insert_append()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  for (int i = 0; i < nodes; i++)
    {
      ioopm_linked_list_append(list, i);
      CU_ASSERT_TRUE(ioopm_linked_list_get(list, i) == i);
      CU_ASSERT_TRUE(ioopm_linked_list_contains(list, i));
    }
  for (int i = nodes - 1; i >= 0; i--)
    {
      ioopm_linked_list_append(list, i);
      CU_ASSERT_TRUE(ioopm_linked_list_get(list, i) == i);
      CU_ASSERT_TRUE(ioopm_linked_list_contains(list, i));
    }
  ioopm_linked_list_destroy(list);
}


static void test_insert_insert()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  for (int i = 0; i < nodes; i++)
    {
      ioopm_linked_list_insert(list, i, i);
      CU_ASSERT_TRUE(ioopm_linked_list_get(list, i) == i);
      CU_ASSERT_TRUE(ioopm_linked_list_contains(list, i));
    }
  for (int i = nodes - 1; i >= 0; i--)
    {
      ioopm_linked_list_insert(list, i, i);
      CU_ASSERT_TRUE(ioopm_linked_list_get(list, i) == i);
      CU_ASSERT_TRUE(ioopm_linked_list_contains(list, i));
    }
  ioopm_linked_list_destroy(list);
}


static void test_remove()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  for (int i = 0; i < nodes; i++)
    {
     ioopm_linked_list_insert(list, i, i);
    }
  for (int i = nodes - 1; i >= 0; i--)
    {
      ioopm_linked_list_remove(list, i);
      CU_ASSERT_FALSE(ioopm_linked_list_contains(list, i));
    }
  ioopm_linked_list_destroy(list);
}


static void test_size()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  for (int i = 0; i < nodes; i++)
    {
     ioopm_linked_list_insert(list, i, i);
     CU_ASSERT_TRUE(ioopm_linked_list_size(list) == i + 1);
    }
  ioopm_linked_list_destroy(list);
}


int main(void)
{
  CU_pSuite pSuiteNW = NULL;
  
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();
  
  pSuiteNW = CU_add_suite("nextWord Suite", init_suite, clean_suite);
  
  if (NULL == pSuiteNW) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  
  if (NULL == CU_add_test(pSuiteNW, "test of create/destroy", test_create_destroy) ||
      (NULL == CU_add_test(pSuiteNW, "test of insert: prepend", test_insert_prepend)) ||
      (NULL == CU_add_test(pSuiteNW, "test of insert: append", test_insert_append)) ||
      (NULL == CU_add_test(pSuiteNW, "test of insert: insert", test_insert_insert)) ||
      (NULL == CU_add_test(pSuiteNW, "test of remove", test_remove)) ||
      (NULL == CU_add_test(pSuiteNW, "test of size", test_size))) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
