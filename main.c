#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include "CUnit/Basic.h"
#include "hash_table.h"


int init_suite(void)
{
  return 0;
}

int clean_suite(void)
{
  return 0;
}


/*
static bool test_lookup(ioopm_hash_table_t *ht, int key)
{
  char **value_ptr = ioopm_hash_table_lookup(ht, key);
  char *value = NULL; // no value yet
  if (value_ptr != NULL)
    {
      value = *value_ptr; // Value now points to the string the key maps to in ht
      printf("Value for key %d found: %s\n", key, value);
      // *value_ptr = "Some other string"; // We just updated the value!
      return true;
    }
  else
    {
      printf("Key %d not found.\n", key);
      errno = EINVAL;
      return false;
    }
}
*/


static void test_create_destroy()
{
   ioopm_hash_table_t *ht = ioopm_hash_table_create();
   CU_ASSERT_PTR_NOT_NULL(ht); 
   ioopm_hash_table_destroy(ht);
}


static void test_lookup_empty()
{
   ioopm_hash_table_t *ht = ioopm_hash_table_create();
   for (int i = 0; i < 18; ++i) /// 18 is a bit magical 
     {
       CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, i));
     }
   CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, -1));
   CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, -18));
   ioopm_hash_table_destroy(ht);
}


static void test_lookup_insert_1()
{
  int key = 5;
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  ioopm_hash_table_insert(ht, key, "abc");
  CU_ASSERT_PTR_NOT_NULL(ioopm_hash_table_lookup(ht, key));
  ioopm_hash_table_destroy(ht);
}


static void test_lookup_insert_2()
{
  int key = 5;
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  ioopm_hash_table_insert(ht, key, "abc");
  ioopm_hash_table_insert(ht, key, "cde");
  CU_ASSERT_PTR_NOT_NULL(ioopm_hash_table_lookup(ht, key));
  ioopm_hash_table_destroy(ht);
}


static void test_lookup_insert_3()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  for (int key = 0; key < 18; ++key)
    {
      ioopm_hash_table_insert(ht, key, "abc");
      CU_ASSERT_PTR_NOT_NULL(ioopm_hash_table_lookup(ht, key));
    }
  for (int key = 0; key > -36; --key)
    {
      ioopm_hash_table_insert(ht, key, "cde");
      CU_ASSERT_PTR_NOT_NULL(ioopm_hash_table_lookup(ht, key));
    }
  ioopm_hash_table_destroy(ht);
}


static void test_lookup_remove_1()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  for (int key = 0; key > -18; --key)
    {
      ioopm_hash_table_insert(ht, key, "abc");
      CU_ASSERT_PTR_NOT_NULL(ioopm_hash_table_lookup(ht, key));
    }
  for (int key = 0; key > -18; --key)
    {
      ioopm_hash_table_remove(ht, key);
      CU_ASSERT_PTR_NULL(ioopm_hash_table_lookup(ht, key));
    }
  ioopm_hash_table_destroy(ht);
}

static void test_size()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 0);
  for (int i = 0; i < 16; i++)
    {
      ioopm_hash_table_insert(ht, i, "abc");
      
    }
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 16);
  for (int i = 0; i < 16; i++)
    {
      ioopm_hash_table_insert(ht, i*17, "abc");
    }
  CU_ASSERT_EQUAL(ioopm_hash_table_size(ht), 31); //Endast 31 då vi redan haft en entry med key = 0.
}


int main(int argc, char *argv[])
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
      (NULL == CU_add_test(pSuiteNW, "test of size: size", test_size))) {
    CU_cleanup_registry();
    return CU_get_error();
  }
  
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}

