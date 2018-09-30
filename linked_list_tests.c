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
      CU_ASSERT_FALSE(ioopm_linked_list_contains(list, i));
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
      CU_ASSERT_FALSE(ioopm_linked_list_contains(list, i));
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
      CU_ASSERT_FALSE(ioopm_linked_list_contains(list, i));
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
      CU_ASSERT_TRUE(ioopm_linked_list_contains(list, i));
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


static void test_is_empty()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  CU_ASSERT_TRUE(ioopm_linked_list_is_empty(list));
  ioopm_linked_list_insert(list, 0, 5);
  CU_ASSERT_FALSE(ioopm_linked_list_is_empty(list));
  ioopm_linked_list_destroy(list);
}


static void test_clear()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_linked_list_insert(list, 0, 5);
  ioopm_linked_list_clear(list);
  CU_ASSERT_TRUE(ioopm_linked_list_is_empty(list));
  ioopm_linked_list_destroy(list);
}

static bool less_than(int a, void *b)
{
  return a < *(int *)b ? true : false;
}

static void test_list_all() // TODO
{
  ioopm_list_t *list = ioopm_linked_list_create();
  for (int i = 0; i < 100; i++)
    {
      ioopm_linked_list_prepend(list, i);
    }
  int test = 150;
  CU_ASSERT_TRUE(ioopm_linked_list_all(list, less_than, (void *)&test));
  ioopm_linked_list_prepend(list, test + 10);
  CU_ASSERT_FALSE(ioopm_linked_list_all(list, less_than, (void *)&test));
  ioopm_linked_list_destroy(list);
}

static bool is_divisor_of(int a, void *b)
{
  return !(a % *(int *)b);
}

static void test_list_any() // TODO
{
  ioopm_list_t *list = ioopm_linked_list_create();
  for (int i = 1; i < 100; i++)
    {
      ioopm_linked_list_prepend(list, i);
    }
  int test_int = 111;
  CU_ASSERT_FALSE(ioopm_linked_list_any(list, is_divisor_of, (void *)&test_int));
  ioopm_linked_list_append(list, (test_int*11));
  CU_ASSERT_TRUE(ioopm_linked_list_any(list, is_divisor_of, (void *)&test_int));
  ioopm_linked_list_destroy(list);  
}

static void fun_sum(int a, void *b)
{
  *(int *)b += a;
}

static void test_apply_to_all() // TODO 
{
  ioopm_list_t *list = ioopm_linked_list_create();
  int sum = 0;
  ioopm_linked_apply_to_all(list, fun_sum, (void *)&sum);
  CU_ASSERT_EQUAL(sum, 0);
  for (int i = 1; i < 100; i++)
    {
      ioopm_linked_list_prepend(list, i);
    }
  ioopm_linked_apply_to_all(list, fun_sum, (void *)&sum);
  CU_ASSERT_EQUAL(sum, 4950);
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
      (NULL == CU_add_test(pSuiteNW, "test of size", test_size)) ||
      (NULL == CU_add_test(pSuiteNW, "test of is_empty", test_is_empty)) ||
      (NULL == CU_add_test(pSuiteNW, "test of clear", test_clear)) ||
      (NULL == CU_add_test(pSuiteNW, "test of all", test_list_all)) ||
      (NULL == CU_add_test(pSuiteNW, "test of any", test_list_any)) ||
      (NULL == CU_add_test(pSuiteNW, "test of apply all", test_apply_to_all))
      ) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
