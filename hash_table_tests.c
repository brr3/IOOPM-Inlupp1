#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "CUnit/Basic.h"
#include "hash_table.h"
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
   ioopm_hash_table_t *ht = ioopm_hash_table_create();
   CU_ASSERT_PTR_NOT_NULL(ht); 
   ioopm_hash_table_destroy(ht);
}


static void test_lookup_empty()
{
   ioopm_hash_table_t *ht = ioopm_hash_table_create();
   for (int i = 0; i < No_Buckets + 1; ++i) 
     {
       CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, i));
       CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, i));
     }
   CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, -1));
   CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, -1));
   CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, -18));
   CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, -18));
   ioopm_hash_table_destroy(ht);
}


static void test_lookup_insert_1()
{
  int key = 5;
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  elem_t elem = {.string = "abc"};
  ioopm_hash_table_insert(ht, key, elem);
  CU_ASSERT_PTR_NOT_NULL(ioopm_hash_table_lookup(ht, key));
  ioopm_hash_table_destroy(ht);
}


static void test_lookup_insert_2()
{
  int key = 5;
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  elem_t elem = {.string = "abc"};
  ioopm_hash_table_insert(ht, key, elem);
  elem.string = "cde";
  ioopm_hash_table_insert(ht, key, elem);
  CU_ASSERT_PTR_NOT_NULL(ioopm_hash_table_lookup(ht, key));
  ioopm_hash_table_destroy(ht);
}


static void test_lookup_insert_3()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  elem_t elem = {.string = "abc"};
  for (int key = 0; key < No_Buckets + 1; ++key)
    {
      ioopm_hash_table_insert(ht, key, elem);
      CU_ASSERT_PTR_NOT_NULL(ioopm_hash_table_lookup(ht, key));
      CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, key));
    }
  for (int key = 0; key > -2 * No_Buckets; --key)
    {
      elem.string = "cde";
      ioopm_hash_table_insert(ht, key, elem);
      CU_ASSERT_PTR_NOT_NULL(ioopm_hash_table_lookup(ht, key));
      CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, key));
    }
  ioopm_hash_table_destroy(ht);
}


static void test_lookup_remove_1()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  elem_t elem = {.string = "abc"};
  for (int key = 0; key > -No_Buckets - 1; --key)
    {
      ioopm_hash_table_insert(ht, key, elem);
    }
  for (int key = 0; key > -No_Buckets - 1; --key)
    {
      ioopm_hash_table_remove(ht, key);
      CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, key));
    }
  ioopm_hash_table_destroy(ht);
}


static void test_size()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  elem_t elem = {.string = "abc"};
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);
  for (int i = 0; i < No_Buckets; i++)
    {
      ioopm_hash_table_insert(ht, i, elem);
    }
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), No_Buckets);
  for (int i = 0; i < No_Buckets; i++)
    {
      ioopm_hash_table_insert(ht, i+No_Buckets, elem);
    }
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), No_Buckets * 2);
  ioopm_hash_table_destroy(ht);
}


static void test_is_empty()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  elem_t elem = {.string = "abc"};
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_insert(ht, 0, elem);
  CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_remove(ht, 0);
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_insert(ht, No_Buckets, elem);
  CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_destroy(ht);
}


static void test_clear()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  elem_t elem = {.string = "abc"};
  for (int i = 0; i < No_Buckets; i++)
    {
      ioopm_hash_table_insert(ht, i, elem);
    }
  CU_ASSERT_FALSE(ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_clear(ht);
  CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
  ioopm_hash_table_destroy(ht);
}


static void test_keys()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  elem_t elem = {.string = "abc"};
  for (int i = 0; i < No_Buckets; i++)
    {
      ioopm_hash_table_insert(ht, i, elem);
    }
  ioopm_list_t *keys = ioopm_hash_table_keys(ht);
  for (int i = 0; (size_t) i < ioopm_hash_table_size(ht); ++i)
    {
      CU_ASSERT_TRUE(ioopm_linked_list_get(keys, i).integer == i);
    }
  ioopm_linked_list_destroy(keys);
  ioopm_hash_table_destroy(ht);
}


static void test_values()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  elem_t elem = {.string = "abc"};
  for (int i = 0; i < No_Buckets; i++)
    {
      ioopm_hash_table_insert(ht, i, elem);
    }
  ioopm_list_t *values = ioopm_hash_table_values(ht);
  for (int i = 0; (size_t) i < ioopm_hash_table_size(ht); ++i)
    {
      CU_ASSERT_TRUE(strcmp(ioopm_linked_list_remove(values, 0).string, "abc") == 0);
    }
  ioopm_linked_list_destroy(values);
  ioopm_hash_table_destroy(ht);
}


static bool comp_value(int key, elem_t value, void *extra)
{
  return !strcmp(value.string, ((elem_t *)extra)->string);
}


static void test_all()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  elem_t elem = {.string = "abc"};
  for (int i = 0; i < No_Buckets; i++)
    {
      ioopm_hash_table_insert(ht, i, elem);
    }
  CU_ASSERT_TRUE(ioopm_hash_table_all(ht, comp_value, (void *)&elem));
  ioopm_hash_table_destroy(ht);
}


static bool comp_key(int key, elem_t value, void *extra)
{
  return key == *((int *)extra);
}


static bool any_length_4(int key, elem_t value, void *arg)
{
  if (strlen(value.string) == 4)
    {
      return true;
    }
  return false;
}


static void test_any()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  int key = 42;
  elem_t elem = {.string = "abc"};
  for (int i = 0; i < No_Buckets; i++)
    {
      ioopm_hash_table_insert(ht, i, elem);
    }
  CU_ASSERT_FALSE(ioopm_hash_table_any(ht, comp_key, (void *) &key));
  
  ioopm_hash_table_insert(ht, key, elem);
  CU_ASSERT_TRUE(ioopm_hash_table_any(ht, comp_key, (void *) &key));

  void *dummy = NULL;
  CU_ASSERT_FALSE(ioopm_hash_table_any(ht, any_length_4, dummy));
  elem.string = "abcd";
  ioopm_hash_table_insert(ht, 500, elem);
  CU_ASSERT_TRUE(ioopm_hash_table_any(ht, any_length_4, dummy));
  
  ioopm_hash_table_destroy(ht);
}


static bool value_count(int key, elem_t value, void *result)
{
  *(int *)result += strlen(value.string);
  return true;
}


static void test_apply_all()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  elem_t elem = {.string = "abc"};
  for (int i = 0; i < No_Buckets; i++)
    {
      ioopm_hash_table_insert(ht, i, elem);
    }
  int result = 0;
  ioopm_hash_table_apply_to_all(ht, value_count, &result);
  CU_ASSERT_TRUE(result == 3*No_Buckets);

  ioopm_hash_table_destroy(ht);
}


static bool elem_cmp_string(int key_ignored, elem_t value, void *x)
{
  return strcmp(value.string, ((elem_t *)x)->string) == 0;
}


static void test_has_value()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  elem_t elem = {.string = "abc"};
  elem_t elem2 = {.string = "def"};
  ioopm_hash_table_insert(ht, 0, elem);
  ioopm_hash_table_insert(ht, 16, elem2);
  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, elem, elem_cmp_string));
  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, elem2, elem_cmp_string));
  elem.string = "ghi";
  CU_ASSERT_FALSE(ioopm_hash_table_has_value(ht, elem, elem_cmp_string));
  ioopm_hash_table_destroy(ht);
}


static void test_has_key()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  elem_t elem = {.string = "abc"};
  elem_t elem2 = {.string = "def"};
  ioopm_hash_table_insert(ht, 0, elem);
  ioopm_hash_table_insert(ht, 16, elem2);
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, 0));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, 16));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, 2));
  ioopm_hash_table_destroy(ht);
}

static void test_resize()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  elem_t elem = {.string = "test"};
  for (int i = 0; i < 170; i++)
    {
      ioopm_hash_table_insert(ht, i, elem);
    }
  //printf("Buckets size: %d\n", (int)ioopm_hash_table_buckets_size(ht));
  CU_ASSERT_EQUAL(ioopm_hash_table_buckets_size(ht), 17);
  for (int i = 170; i < 340; i++)
    {
      ioopm_hash_table_insert(ht, i, elem);
    }
  CU_ASSERT_EQUAL(ioopm_hash_table_buckets_size(ht), 31);
  
  ioopm_hash_table_destroy(ht);
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
      (NULL == CU_add_test(pSuiteNW, "test of lookup: empty ht", test_lookup_empty)) ||
      (NULL == CU_add_test(pSuiteNW, "test of lookup: insert_1", test_lookup_insert_1)) ||
      (NULL == CU_add_test(pSuiteNW, "test of lookup: insert_2", test_lookup_insert_2)) ||
      (NULL == CU_add_test(pSuiteNW, "test of lookup: insert_3", test_lookup_insert_3)) ||
      (NULL == CU_add_test(pSuiteNW, "test of lookup: remove_1", test_lookup_remove_1)) ||
      (NULL == CU_add_test(pSuiteNW, "test of size", test_size)) ||
      (NULL == CU_add_test(pSuiteNW, "test of is_empty", test_is_empty)) ||
      (NULL == CU_add_test(pSuiteNW, "test of clear", test_clear)) ||
      (NULL == CU_add_test(pSuiteNW, "test of keys", test_keys)) ||
      (NULL == CU_add_test(pSuiteNW, "test of values", test_values)) ||
      (NULL == CU_add_test(pSuiteNW, "test of any", test_any)) ||
      (NULL == CU_add_test(pSuiteNW, "test of all", test_all)) ||
      (NULL == CU_add_test(pSuiteNW, "test of apply to all", test_apply_all)) ||
      (NULL == CU_add_test(pSuiteNW, "test of has_value", test_has_value)) ||
      (NULL == CU_add_test(pSuiteNW, "test of has_key", test_has_key)) ||
      (NULL == CU_add_test(pSuiteNW, "test of resize", test_resize))
      ) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
