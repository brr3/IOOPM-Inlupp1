#include <stdlib.h>
#include <stdio.h>
#include "hash_table.h"


ioopm_hash_table_t *ioopm_hash_table_create()
{
  /// Allocate space for a ioopm_hash_table_t = 17 pointers to
  /// entry_t's, which will be set to NULL
  ioopm_hash_table_t *result = calloc(1, sizeof(ioopm_hash_table_t));
  return result;
}

static entry_t *find_previous_entry_for_key(entry_t *address, int key)
{
  entry_t *first_entry = address;
  entry_t *cursor = first_entry;
  
  while (cursor != NULL)
    {
      if (cursor->key == key)
        {
          return cursor; /// Ends the whole function!
        } 
      cursor = cursor->next; /// Step forward to the next entry, and repeat loop
    }
  return cursor;
}


static entry_t *entry_create(int key, char *value, entry_t *next)
{
  entry_t *new_entry = calloc(1, sizeof(entry_t));

  new_entry->key = key;
  new_entry->value = value;
  new_entry->next = next;

  return new_entry; 
}


void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value)
{
  /// Calculate the bucket for this entry
  int bucket = key % 17;
  /// Search for an existing entry for a key
  entry_t *entry = find_previous_entry_for_key(&ht->buckets[bucket], key);
  printf("%p \n", next);
  entry_t *next = entry->next;

  /// Check if the next entry should be updated or not
  if (next != NULL && next->key == key)
    {
      next->value = value;
    }
  else
    {
      entry->next = entry_create(key, value, next);
    }
}

