#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include "hash_table.h"


static ioopm_hash_table_t test_insert(ioopm_hash_table_t *ht, int key, char *value)
{
  ioopm_hash_table_insert(ht, key, value);
  printf("Value at key %d: %s\n", key, ht->buckets[key % No_Buckets].next->value);
  return *ht;
}


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


static ioopm_hash_table_t test_remove(ioopm_hash_table_t *ht, int key)
{
  if(test_lookup(ht, key))
    {
      char *removed_value = ioopm_hash_table_remove(ht, key);
      printf("Value %s removed!\n", removed_value);
      assert(!test_lookup(ht, key));
      return *ht;
    } else
    {
      return *ht;
    }
}


static void test_destroy(ioopm_hash_table_t *ht)
{
  ioopm_hash_table_destroy(ht);
  //ioopm_hash_table_destroy_r(ht, ht->buckets[0].next, 0);
}


int main(void)
{
  ioopm_hash_table_t *ht_empty = ioopm_hash_table_create();
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  printf("Hash function bucket count is %d.\n", No_Buckets);
  puts("INSERT TESTS");
  puts("TEST 1 : Insert value with key 1 into empty hash table");
  *ht = test_insert(ht, 1, "abc");
  puts("TEST 2 : Insert value with a different key (2) into our hash table with 1 entry");
  *ht = test_insert(ht, 2, "cde");
  puts("TEST 3 : Insert value that maps to the same bucket (key 18 => bucket 1, assuming No_Buckets = 17) as our first entry in our hash table with 2 entries");
  *ht = test_insert(ht, 18, "fgh");
  puts("TEST 4 : Insert value with the same key (2) as a previous entry in our hash table with 3 entries");
  *ht = test_insert(ht, 2, "success");

  puts("");
  puts("LOOKUP TESTS");
  puts("TEST 1 : Lookup key 1");
  assert(test_lookup(ht, 1));
  puts("TEST 2 : Lookup key 18");
  assert(test_lookup(ht, 18));
  puts("TEST 3 : Lookup key 2");
  assert(test_lookup(ht, 2));
  puts("TEST 4 : Lookup key (3) that does not exist in our hash table");
  assert(!test_lookup(ht, 3));
  puts("TEST 5 : Lookup key 3 in an empty hash table");
  assert(!test_lookup(ht_empty, 3));

  puts("");
  puts("REMOVE TESTS");
  puts("TEST 1 : Remove key 1");
  *ht = test_remove(ht, 1);
  puts("TEST 2 : Remove key 18");
  *ht = test_remove(ht, 18);
  puts("TEST 3 : Remove key (3) that does not exist in our hash table");
  *ht = test_remove(ht, 3);
  puts("TEST 4 : Remove key 3 from an empty hash table");
  test_remove(ht_empty, 3);

  puts("");
  puts("DESTROY TESTS");
  puts("TEST 1 : Destroy our remaining hash table that contains 1 entry with key 2");
  test_destroy(ht);
  puts("TEST 2 : Destroy our empty hash table");
  test_destroy(ht_empty);
  
  return 0;
}
