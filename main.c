#include <stdlib.h>
#include <stdio.h>
#include "hash_table.h"


void test_insert1()
{
  ioopm_hash_table_t *h = ioopm_hash_table_create();
  int key = 1;
  char *value = "abc";
  int bucket = key % 17;
  ioopm_hash_table_insert(h, key, value);
  printf("Value at key %d: %s\n", key, h->buckets[bucket].value);
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


int main(void)
{
  //puts("Test 1 Insert");
  //test_insert1();
  //puts("Test 2 Insert");
  //test_insert2();
  puts("Test 3 Insert");
  test_insert3();
  return 0;
}
