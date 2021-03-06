#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash_table.h"

typedef struct entry entry_t;

struct entry
{
  elem_t key;            
  elem_t value;   
  entry_t *next;                                                   
};

struct hash_table
{
  entry_t **buckets;
  size_t buckets_size;
  ioopm_hash_function hash_function;
  ioopm_apply_function compare_key_func;
  ioopm_apply_function compare_value_func;
  size_t size;
};

static const size_t primes[] = {17, 31, 67, 127, 257, 509, 1021, 2053, 4099, 8191, 16381, 32749, 65521, 131071, 262139, 524287, 1048573, 2097143, 4194301, 8388593, 16777213, 33554393};

static const int num_primes = 22;
static entry_t *PREV_ENTRY;


ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function hash_function, ioopm_apply_function compare_key_func, ioopm_apply_function compare_value_func)
{
  ioopm_hash_table_t *new_hash_table = calloc(1, sizeof(ioopm_hash_table_t));
  new_hash_table->buckets            = calloc(primes[0], sizeof(entry_t *));
  new_hash_table->buckets_size       = primes[0];
  new_hash_table->size               = 0;
  new_hash_table->hash_function      = hash_function;
  new_hash_table->compare_key_func   = compare_key_func;
  new_hash_table->compare_value_func = compare_value_func;
  return new_hash_table;
}


static entry_t **find_previous_entry_for_key(entry_t **address, elem_t key, ioopm_apply_function compare_key)
{
  if (*address == NULL)
    {
      return NULL;
    }
  else
    {
      entry_t *first_entry = *address;
      entry_t *next_entry = first_entry->next;
      entry_t **result = address;
      
      if (compare_key(key, (elem_t) {.void_ptr = NULL}, &first_entry->key))
        {
          return result;
        }
      
      while (next_entry != NULL)
        {
          if (compare_key(key, (elem_t) {.void_ptr = NULL}, &next_entry->key))
            {
              return result;
            }
          result = &next_entry;
          next_entry = next_entry->next;
        }
      
      return NULL;
    }
}


static entry_t *entry_create(elem_t key, elem_t value, entry_t *next)
{
  entry_t *new_entry = calloc(1, sizeof(entry_t));
  new_entry->key = key;
  new_entry->value = value;
  new_entry->next = next;
  return new_entry;                      
}


static void modulo(int *a, int b)
{
  *a = abs(*a) % b;
}


static int get_next_bucket_prime(int current_size)
{
  int i = 0;
  while (i < num_primes && current_size >= (int) primes[i])
    {
      i++;
    }
  return primes[i];
}


static bool ioopm_hash_table_rehash(elem_t key, elem_t value, void *new_ht)
{
  ioopm_hash_table_insert(new_ht, key, value);
  return true;
}


static void ioopm_hash_table_resize(ioopm_hash_table_t *ht)
{
  int load_factor = ht->size / ht->buckets_size;
  if (load_factor > MAX_LOAD_FACTOR)
    { 
      ioopm_hash_table_t new_ht;
      new_ht.buckets_size = get_next_bucket_prime(ht->buckets_size);
      new_ht.size = 0;
      new_ht.hash_function = ht->hash_function;
      new_ht.compare_key_func = ht->compare_key_func;
      new_ht.compare_value_func = ht->compare_value_func;
      new_ht.buckets = calloc(new_ht.buckets_size, sizeof(entry_t));
      
      ioopm_hash_table_apply_to_all(ht, ioopm_hash_table_rehash, &new_ht);
      
      ioopm_hash_table_clear(ht);
      free(ht->buckets);
      *ht = new_ht;
    }
}


void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value)
{
  ioopm_hash_table_resize(ht);
  
  int bucket = ht->hash_function(key);
  modulo(&bucket, ht->buckets_size);
  
  entry_t **entry = find_previous_entry_for_key(&ht->buckets[bucket], key, ht->compare_key_func);
  if (entry == NULL)
    {
      ht->size += 1;
      if (ht->buckets[bucket] == NULL)
        {
          ht->buckets[bucket] = entry_create(key, value, NULL);
        }
      else
        {
          ht->buckets[bucket] = entry_create(key, value, ht->buckets[bucket]);
        }
    }
  else
    {
      (*entry)->value = value;
    }
}


elem_t *ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key)
{
  int bucket = ht->hash_function(key);
  modulo(&bucket, ht->buckets_size);
  
  entry_t **entry = find_previous_entry_for_key(&ht->buckets[bucket], key, ht->compare_key_func);
  if (entry == NULL)
    {
      return NULL;
    }
  else
    {
      return &(*entry)->value;
    }
}


static void entry_destroy(entry_t *pointer)
{
  free(pointer);
}


elem_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key)
{
  int bucket = ht->hash_function(key);
  modulo(&bucket, ht->buckets_size);
  
  entry_t **entry = find_previous_entry_for_key(&ht->buckets[bucket], key, ht->compare_key_func);
  if (entry == NULL)
    {
      return (elem_t) {.void_ptr = NULL};
    }
  else
    {
      elem_t removed_value;
      if ((*entry) != ht->buckets[bucket])
        {
          entry_t *next = (*entry)->next;
          removed_value = next->value;	  
          (*entry) = (*entry)->next;
          entry_destroy(next);
          ht->size -= 1;
          
          return removed_value;
        }
      else
        {
          removed_value = (*entry)->value;
          entry_destroy(*entry);
          ht->buckets[bucket] = NULL;
          ht->size -= 1;
          
          return removed_value;
        }
    }
}


void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{
  ioopm_hash_table_clear(ht);
  free(ht->buckets);
  free(ht);
}


size_t ioopm_hash_table_size(ioopm_hash_table_t *ht)
{
  return ht->size;
}


bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht)
{
  return ht->size == 0;
}


void ioopm_hash_table_clear(ioopm_hash_table_t *ht)
{
  for (int bucket = ht->buckets_size - 1; bucket >= 0; --bucket)
    {
      entry_t *entry = ht->buckets[bucket];
      entry_t *next;
      
      while (entry != NULL)
        {
          next = entry->next;
          entry_destroy(entry);
          entry = next;
          ht->size -= 1;
        }

      ht->buckets[bucket] = NULL;
    }
} 


ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht)
{
  ioopm_list_t *keys = ioopm_linked_list_create();
  for (int i = 0; i < (int) ht->buckets_size; ++i)
    {
      entry_t *next = ht->buckets[i];
      while (next != NULL)
        {
          ioopm_linked_list_append(keys, next->key);
          next = next->next;
        }
    }
  return keys;
}


ioopm_list_t *ioopm_hash_table_values(ioopm_hash_table_t *ht)
{
  ioopm_list_t *values = ioopm_linked_list_create();
  for (int i = 0; i < (int) ht->buckets_size; ++i)
    {
      entry_t *next = ht->buckets[i];
      while (next != NULL)
        {
          ioopm_linked_list_append(values, next->value);
          next = next->next;
        }
    }
  return values;
}


bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key)
{
  return ioopm_hash_table_any(ht, ht->compare_key_func, &key);
}


bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, elem_t value)
{
  return ioopm_hash_table_any(ht, ht->compare_value_func, &value);
}


bool ioopm_hash_table_all(ioopm_hash_table_t *h, ioopm_apply_function pred, void *arg)
{
  int size = ioopm_hash_table_size(h);
  ioopm_list_t *keys = ioopm_hash_table_keys(h);
  ioopm_list_t *values = ioopm_hash_table_values(h);
  bool result = true;  
  for (int i = 0; i < size && result; i++)
    {
      result = result && pred(ioopm_linked_list_remove(keys, 0), ioopm_linked_list_remove(values, 0) , arg);
    }
  ioopm_linked_list_destroy(keys);
  ioopm_linked_list_destroy(values);
  return result;  
}


bool ioopm_hash_table_any(ioopm_hash_table_t *h, ioopm_apply_function pred, void *arg)
{
  int size = ioopm_hash_table_size(h);
  ioopm_list_t *keys = ioopm_hash_table_keys(h);
  ioopm_list_t *values = ioopm_hash_table_values(h);
  for (int i = 0; i < size; i++)
    {
      if (pred(ioopm_linked_list_remove(keys, 0), ioopm_linked_list_remove(values, 0), arg))
        {
          ioopm_linked_list_destroy(keys);
          ioopm_linked_list_destroy(values);
          return true;
        }
    }
  ioopm_linked_list_destroy(keys);
  ioopm_linked_list_destroy(values);
  return false;
}


void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *h, ioopm_apply_function apply_fun, void *arg)
{
  for (size_t i = 0; i < h->buckets_size; ++i)
    {
      entry_t *next = h->buckets[i];
      while (next != NULL) 
        {
          apply_fun(next->key, next->value, arg);
          next = next->next;
        }
    }
}


/// ONLY USED FOR TESTSING
size_t ioopm_hash_table_buckets_size(ioopm_hash_table_t *ht)
{
  return ht->buckets_size;
}
