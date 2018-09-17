#include <stdlib.h>
#include <stdio.h>
#include "hash_table.h"


void test_lookup1()
{
  ioopm_hash_table_t *h = ioopm_hash_table_create();
  int key = 1;
  char *value = "a";
  ioopm_hash_table_insert(h, key, value);
}


int main(void)
{
  ioopm_hash_table_t *h = ioopm_hash_table_create();
  int key = 1;
  char *value = "abc";
  int bucket = key % 17;
  printf("Initial value: %s", value);
  ioopm_hash_table_insert(h, key, value);
  printf("Value at key %d: %s", key, h->buckets[bucket].value);
  return 0;
}
