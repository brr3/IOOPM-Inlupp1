#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "hash_table.h"


ioopm_hash_table_t test_insert(ioopm_hash_table_t *ht, int key, char *value)
{
  ioopm_hash_table_insert(ht, key, value);
  printf("Value at key %d: %s\n", key, ht->buckets[key % 17].next->value);
  return *ht;
}


bool test_lookup(ioopm_hash_table_t *ht, int key)
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
      printf("Key not found.\n");
      return false;
    }
}


int main(void)
{
  ioopm_hash_table_t *ht_empty = ioopm_hash_table_create();
  ioopm_hash_table_t *ht = ioopm_hash_table_create();

  *ht = test_insert(ht, 1, "abc");
  test_insert(ht, 1, "cde");
  
  return 0;
}
