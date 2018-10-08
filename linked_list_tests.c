#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "CUnit/Basic.h"
#include "linked_list.h"
#include "iterator.h"

static int elem_cmp_int(elem_t a, elem_t b)
{
  return b.integer - a.integer;
}

static int init_suite(void)
{
  return 0;
}

static int clean_suite(void)
{
  return 0;
}

static void test_iterator_create_destroy()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
  CU_ASSERT_PTR_NOT_NULL(iter);
  ioopm_iterator_destroy(iter);
  ioopm_linked_list_destroy(list);
}


static void test_iterator_has_next()
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


static void test_iterator_next()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
  elem_t elem = {.integer = 0};
  ioopm_iterator_insert(iter, elem);
  CU_ASSERT_TRUE(ioopm_iterator_next(iter).integer == 0);
  ioopm_iterator_destroy(iter);
  ioopm_linked_list_destroy(list);
}


static void test_iterator_remove()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
  elem_t elem = {.integer = 0};
  ioopm_iterator_insert(iter, elem);
  CU_ASSERT_TRUE(ioopm_iterator_remove(iter).integer == 0);
  ioopm_iterator_destroy(iter);
  ioopm_linked_list_destroy(list);
}


static void test_iterator_insert()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
  elem_t elem;
  for (int i = 0; i < 20; ++i)
    {
      elem.integer = i;
      ioopm_iterator_insert(iter, elem);
      CU_ASSERT_TRUE(ioopm_iterator_next(iter).integer == i);
    }
  ioopm_iterator_destroy(iter);
  ioopm_linked_list_destroy(list);
}


static void test_iterator_reset()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
  elem_t elem = {.integer = 0};
  for (int i = 0; i < 20; ++i)
    {
      elem.integer = i;
      ioopm_iterator_insert(iter, elem);
    }
  CU_ASSERT_EQUAL(ioopm_iterator_current(iter).integer, 19);
  for (int i = 0; i < 20; i++)
    {
      CU_ASSERT_EQUAL(ioopm_iterator_next(iter).integer, 19 - i);
    }
  ioopm_iterator_reset(iter);
  CU_ASSERT_EQUAL(ioopm_iterator_current(iter).integer, 19);
  ioopm_iterator_destroy(iter);
  ioopm_linked_list_destroy(list);
}


static void test_iterator_current()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  ioopm_list_iterator_t *iter = ioopm_list_iterator(list);
  elem_t elem = {.integer = 0};
  ioopm_iterator_insert(iter, elem);
  CU_ASSERT_TRUE(ioopm_iterator_current(iter).integer == 0);
  ioopm_iterator_next(iter);
  CU_ASSERT_TRUE(ioopm_iterator_current(iter).void_ptr == NULL);
  ioopm_iterator_reset(iter);
  CU_ASSERT_TRUE(ioopm_iterator_current(iter).integer == 0);
  ioopm_iterator_destroy(iter);
  ioopm_linked_list_destroy(list);
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
  elem_t elem = {.integer = 0};
  for (int i = 0; i < nodes; i++)
    {
      elem.integer = i;
      CU_ASSERT_FALSE(ioopm_linked_list_contains(list, elem, elem_cmp_int));
      ioopm_linked_list_prepend(list, elem);
      CU_ASSERT_TRUE(ioopm_linked_list_get(list, 0).integer == elem.integer);
      CU_ASSERT_TRUE(ioopm_linked_list_contains(list, elem, elem_cmp_int));
    }
  for (int i = nodes - 1; i >= 0; i--)
    {
      elem.integer = i;
      ioopm_linked_list_prepend(list, elem);
      CU_ASSERT_TRUE(ioopm_linked_list_get(list, 0).integer == elem.integer);
      CU_ASSERT_TRUE(ioopm_linked_list_contains(list, elem, elem_cmp_int));
    }
  ioopm_linked_list_destroy(list);
}


static void test_insert_append()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  elem_t elem = {.integer = 0};
  for (int i = 0; i < nodes; i++)
    {
      elem.integer = i;
      CU_ASSERT_FALSE(ioopm_linked_list_contains(list, elem, elem_cmp_int));
      ioopm_linked_list_append(list, elem);
      CU_ASSERT_TRUE(ioopm_linked_list_get(list, i).integer == elem.integer);
      CU_ASSERT_TRUE(ioopm_linked_list_contains(list, elem, elem_cmp_int));
    }
  for (int i = nodes - 1; i >= 0; i--)
    {
      elem.integer = i;
      ioopm_linked_list_append(list, elem);
      CU_ASSERT_TRUE(ioopm_linked_list_get(list, i).integer == elem.integer);
      CU_ASSERT_TRUE(ioopm_linked_list_contains(list, elem, elem_cmp_int));
    }
  ioopm_linked_list_destroy(list);
}


static void test_insert_insert()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  elem_t elem = {.integer = 0};
  for (int i = 0; i < nodes; i++)
    {
      elem.integer = i;
      CU_ASSERT_FALSE(ioopm_linked_list_contains(list, elem, elem_cmp_int));
      ioopm_linked_list_insert(list, i, elem);
      CU_ASSERT_TRUE(ioopm_linked_list_get(list, i).integer == elem.integer);
      CU_ASSERT_TRUE(ioopm_linked_list_contains(list, elem, elem_cmp_int));
    }
  for (int i = nodes - 1; i >= 0; i--)
    {
      elem.integer = i;
      ioopm_linked_list_insert(list, i, elem);
      CU_ASSERT_TRUE(ioopm_linked_list_get(list, i).integer == elem.integer);
      CU_ASSERT_TRUE(ioopm_linked_list_contains(list, elem, elem_cmp_int));
    }
  ioopm_linked_list_destroy(list);
}


static void test_remove()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  elem_t elem = {.integer = 0};
  for (int i = 0; i < nodes; i++)
    {
      elem.integer = i;
      ioopm_linked_list_insert(list, i, elem);
    }
  for (int i = nodes - 1; i >= 0; i--)
    {
      elem.integer = i;
      CU_ASSERT_TRUE(ioopm_linked_list_contains(list, elem, elem_cmp_int));
      ioopm_linked_list_remove(list, i);
      CU_ASSERT_FALSE(ioopm_linked_list_contains(list, elem, elem_cmp_int));
    }
  ioopm_linked_list_destroy(list);
}


static void test_get()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  elem_t elem = {.integer = 0};
  ioopm_linked_list_insert(list, 0, elem);
  CU_ASSERT_TRUE(ioopm_linked_list_get(list, 0).integer == 0);
  ioopm_linked_list_get(list, 1);
  ioopm_linked_list_destroy(list);  
}


static void test_size()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  elem_t elem = {.integer = 0};
  for (int i = 0; i < nodes; i++)
    {
      elem.integer = i;
      ioopm_linked_list_insert(list, i, elem);
      CU_ASSERT_TRUE(ioopm_linked_list_size(list) ==  i + 1);
    }
  ioopm_linked_list_destroy(list);
}


static void test_is_empty()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  elem_t elem = {.integer = 0};
  CU_ASSERT_TRUE(ioopm_linked_list_is_empty(list));
  elem.integer = 5;
  ioopm_linked_list_insert(list, 0, elem);
  CU_ASSERT_FALSE(ioopm_linked_list_is_empty(list));
  ioopm_linked_list_destroy(list);
}


static void test_clear()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  elem_t elem = {.integer = 0};
  elem.integer = 5;
  ioopm_linked_list_insert(list, 0, elem);
  ioopm_linked_list_clear(list);
  CU_ASSERT_TRUE(ioopm_linked_list_is_empty(list));
  ioopm_linked_list_destroy(list);
}


static bool less_than(elem_t a, void *b)
{
  return a.integer < ((elem_t *)b)->integer ? true : false;
}


static void test_list_all()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  elem_t elem = {.integer = 0};
  for (int i = 0; i < 100; i++)
    {
      elem.integer = i;
      ioopm_linked_list_prepend(list, elem);
    }
  int test = 150;
  CU_ASSERT_TRUE(ioopm_linked_list_all(list, less_than, (void *)&test));
  elem.integer = 150;
  ioopm_linked_list_prepend(list, elem);
  CU_ASSERT_FALSE(ioopm_linked_list_all(list, less_than, (void *)&test));
  ioopm_linked_list_destroy(list);
}


static bool is_divisor_of(elem_t a, void *b)
{
  return !(a.integer % ((elem_t *)b)->integer);
}


static void test_list_any()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  elem_t elem = {.integer = 0};
  for (int i = 1; i < 100; i++)
    {
      elem.integer = i;
      ioopm_linked_list_prepend(list, elem);
    }
  int test_int = 111;
  CU_ASSERT_FALSE(ioopm_linked_list_any(list, is_divisor_of, (void *)&test_int));
  elem.integer= test_int*11;
  ioopm_linked_list_append(list, elem);
  CU_ASSERT_TRUE(ioopm_linked_list_any(list, is_divisor_of, (void *)&test_int));
  ioopm_linked_list_destroy(list);  
}


static void fun_sum(elem_t a, void *b)
{
  *(int *)b += a.integer;
}


static void test_apply_to_all()
{
  ioopm_list_t *list = ioopm_linked_list_create();
  elem_t elem = {.integer = 0};
  int sum = 0;
  ioopm_linked_apply_to_all(list, fun_sum, (void *)&sum);
  CU_ASSERT_EQUAL(sum, 0);
  for (int i = 1; i < 100; i++)
    {
      elem.integer = i;
      ioopm_linked_list_prepend(list, elem);
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
      (NULL == CU_add_test(pSuiteNW, "test of get", test_get)) ||
      (NULL == CU_add_test(pSuiteNW, "test of size", test_size)) ||
      (NULL == CU_add_test(pSuiteNW, "test of is_empty", test_is_empty)) ||
      (NULL == CU_add_test(pSuiteNW, "test of clear", test_clear)) ||
      (NULL == CU_add_test(pSuiteNW, "test of all", test_list_all)) ||
      (NULL == CU_add_test(pSuiteNW, "test of any", test_list_any)) ||
      (NULL == CU_add_test(pSuiteNW, "test of apply all", test_apply_to_all)) ||
      (NULL == CU_add_test(pSuiteNW, "test_iterator of create/destroy", test_iterator_create_destroy)) ||
      (NULL == CU_add_test(pSuiteNW, "test_iterator of has_next", test_iterator_has_next)) ||
      (NULL == CU_add_test(pSuiteNW, "test_iterator of next", test_iterator_next)) ||
      (NULL == CU_add_test(pSuiteNW, "test_iterator of remove", test_iterator_remove)) ||
      (NULL == CU_add_test(pSuiteNW, "test_iterator of insert", test_iterator_insert)) ||
      (NULL == CU_add_test(pSuiteNW, "test_iterator of reset", test_iterator_reset)) ||
      (NULL == CU_add_test(pSuiteNW, "test_iterator of current", test_iterator_current))       

      ) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
