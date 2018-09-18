#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "hash_table.h"


ioopm_hash_table_t test_insert(ioopm_hash_table_t *ht, int key, char *value)
{
  ioopm_hash_table_insert(ht, key, value);
  printf("Value at key %d: %s\n", key, ht->buckets[key % 17].value);
  return *ht;
}


void test_insert2()
{
  ioopm_hash_table_t *h = ioopm_hash_table_create();
  int key = 1;
  char *value1 = "abc";
  char *value2 = "cde";
  int bucket = key % 17;
  ioopm_hash_table_insert(h, key, value1);
  printf("Value 1 at key %d: %s\n", key, h->buckets[bucket].value);
  ioopm_hash_table_insert(h, key, value2);
  printf("Value 2 at key %d: %s\n", key, h->buckets[bucket].value);
}


void test_insert3()
{
  ioopm_hash_table_t *h = ioopm_hash_table_create();
  int key1 = 1;
  int key2 = 2;
  char *value1 = "abc";
  char *value2 = "cde";
  int bucket1 = key1 % 17;
  int bucket2 = key2 % 17;
  ioopm_hash_table_insert(h, key1, value1);
  printf("Value 1 at key %d: %s\n", key1, h->buckets[bucket1].value);
  ioopm_hash_table_insert(h, key2, value2);
  printf("Value 2 at key %d: %s\n", key2, h->buckets[bucket2].value);
}


void test_insert4()
{
  ioopm_hash_table_t *h = ioopm_hash_table_create();
  int key1 = 1;
  int key2 = 18;
  char *value1 = "abc";
  char *value2 = "cde";
  int bucket1 = key1 % 17;
  int bucket2 = key2 % 17;
  ioopm_hash_table_insert(h, key1, value1);
  printf("Value 1 at key %d: %s\n", key1, h->buckets[bucket1].value);
  ioopm_hash_table_insert(h, key2, value2);
  printf("Value 2 at key %d: %s\n", key2, h->buckets[bucket2].value);
}


bool test_lookup(ioopm_hash_table_t *ht, int key)
{
  char **value_ptr = ioopm_hash_table_lookup(ht, key);
  char *value = NULL; // no value yet
  if (value_ptr != NULL)
    {
      // key was in ht
      value = *value_ptr; // Value now points to the string the key maps to in ht
      printf("Value for key %d found: %s\n", key, value);
      // *value_ptr = "Some other string"; // We just updated the value!
      return true;
    }
  else
    {
      printf("Key not found.\n");
      return false;
    }
}


int main(void)
{
  ioopm_hash_table_t *ht_empty = ioopm_hash_table_create();
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  puts("Test 1 (insert 1 value)");
  *ht = test_insert(ht, 1, "abc");
  *ht = test_insert(ht, 2, "cde");
  
  puts("Test 2 (insert 2 values with same key)");
  test_insert2();
  
  puts("Test 3 (insert 2 values with different keys)");
  test_insert3();
  
  puts("Test 4 (insert 2 values with different keys but same bucket)");
  test_insert4();
  
  puts("Test 5 (lookup key in hash table with 2 entries)");
  assert(test_lookup(ht, 1) == true);
  assert(test_lookup(ht, 2) == true);

  puts("Test 6 (lookup key in hash table with 2 entries where 1 has been overwritten)");
  *ht = test_insert(ht, 1, "cde");
  assert(test_lookup(ht, 1) == true);
  
  puts("Test 7 (lookup key in empty hash table)");
  assert(test_lookup(ht_empty, 1) == false);
  return 0;
}
