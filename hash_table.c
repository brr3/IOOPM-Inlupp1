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
  entry_t *next_entry = first_entry->next;
  entry_t *previous_entry = first_entry;
  
  while (next_entry != NULL)
    {
      if (next_entry->key == key)
        {
          //printf("----Cursor key found: %p\n", next_entry);
          return previous_entry; /// Ends the whole function!
        }
      previous_entry = next_entry;
      next_entry = next_entry->next; /// Step forward to the next entry, and repeat loop
    }
  //puts("----Key not found!");
  return first_entry;
}


static entry_t *entry_create(int key, char *value, entry_t *next)
{
  entry_t *new_entry = calloc(1, sizeof(entry_t));

  new_entry->key = key;
  new_entry->value = value;
  new_entry->next = next;
  //printf("new_entry key = %d\n", key);
  //printf("new_entry value = %s\n", value);
  //printf("new entry next = %p\n", next);
  //printf("new entry = %p\n", new_entry);

  return new_entry;                      
}


int check_key(int key)
{
  if (key < 0)
    {
      while (key < 0)
        {
          key = No_Buckets + key;
        }
      return key;
    } else
    {
      return key;
    }
}


void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value)
{
  key = check_key(key); 
  int bucket = key % No_Buckets;
  entry_t *entry = find_previous_entry_for_key(&ht->buckets[bucket], key);
  entry_t *next = entry->next;

 /// Check if the next entry should be updated or not
  if (next != NULL && next->key == key)
    {
      next->value = value;
    }
  else
    {
      entry->next = entry_create(key, value, next);
      //printf("Pointer at key %d: %p\n", key, ht->buckets[bucket].next->value);
    }
}


char **ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key)
{
  //key = check_key(key); DEMO
  entry_t *entry = find_previous_entry_for_key(&ht->buckets[key % No_Buckets], key);
  entry_t *next = entry->next;
  
  if (next != NULL && next->key == key)
    {    
      return &next->value;
    }
  else
    {
      return NULL; 
    }
}


static void entry_destroy(entry_t *pointer)
{
  free(pointer);
}


char *ioopm_hash_table_remove(ioopm_hash_table_t *ht, int key)                                               
{                                                                                                             
  /// Find the previous entry for key
  int bucket = key % No_Buckets;
  entry_t *temp = ht->buckets + bucket;
  entry_t *entry = find_previous_entry_for_key(temp, key);
  
  entry_t *next = entry->next;
                                                                                                              
  if (next != NULL && next->key == key)                                                                       
    {
      char *removed_value = next->value;
      entry->next = entry->next->next;
      entry_destroy(next);
      return removed_value;                                                                                    
    }                                                                                                         
  else                                                                                                        
    {                                                                                                         
      return NULL;                                                                                            
    }                                                                                                        
}


void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{
  int bucket = No_Buckets - 1;
  while (bucket >= 0)
    {
      entry_t *first_entry = &ht->buckets[bucket];
      entry_t *entry, *next;
      if (first_entry->next != NULL)
        {
          //puts("next != NULL");
          entry = first_entry->next;
          next = entry->next;
          while (next != NULL)
            {
              entry_destroy(entry);
              entry = next;
              next = entry->next;
            }
          entry_destroy(entry);
        }
      if (bucket == 0)
        {
          entry_destroy(first_entry);
        }
      --bucket;
    }
}


void ioopm_hash_table_destroy_r(ioopm_hash_table_t *ht, entry_t *entry, int bucket)
{
  if (bucket < No_Buckets)
    {
      entry_t *first_entry = &ht->buckets[bucket];
      //entry = ht->buckets[bucket].next;
      entry_t *next = entry->next;
      if (next == NULL)
        {
          entry_destroy(entry);
          entry_destroy(first_entry);
          int next_bucket = bucket + 1;
          return ioopm_hash_table_destroy_r(ht, ht->buckets[next_bucket].next, next_bucket);
        } else
        {
          entry_destroy(entry);
          return ioopm_hash_table_destroy_r(ht, next, bucket);
        }
    } else
    {
      return;
    }
}

