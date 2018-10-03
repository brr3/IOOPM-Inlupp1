#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash_table.h"


struct entry
{
  int key;       // holds the key                                                                                                                         
  elem_t value;   // holds the value                                                                                                                       
  entry_t *next; // points to the next entry (possibly NULL)                                                                                              
};

struct hash_table
{
  entry_t *buckets;
  size_t buckets_size;
  size_t size;
};

static size_t primes[] = {17, 31, 67, 127, 257, 509, 1021, 2053, 4099, 8191, 16381};
static int num_primes  = 11;

ioopm_hash_table_t *ioopm_hash_table_create()
{
  ioopm_hash_table_t *new_hash_table = calloc(1, sizeof(ioopm_hash_table_t));
  new_hash_table->buckets            = calloc(primes[0], sizeof(entry_t));
  new_hash_table->buckets_size       = primes[0];
  new_hash_table->size               = 0;
  return new_hash_table;
}

static entry_t *find_previous_entry_for_key(entry_t *address, int key)
{
  entry_t *first_entry    = address; 
  entry_t *next_entry     = first_entry->next;
  entry_t *previous_entry = first_entry;
  
  while (next_entry != NULL)
    {
      if (next_entry->key == key)
        {
          return previous_entry;
        }
      previous_entry = next_entry;
      next_entry = next_entry->next;
    }
  return first_entry;
}


static entry_t *entry_create(int key, elem_t value, entry_t *next)
{
  entry_t *new_entry = calloc(1, sizeof(entry_t));

  new_entry->key = key;
  new_entry->value = value;
  new_entry->next = next;
  
  return new_entry;                      
}


static void modulo_(int *a, int b) // DEMO ACHIEVEMENT M38: värdeöverföring via pekare
{
  if (*a < 0)
    {
      while (*a < 0)
        {
          *a = b + *a;
        }
    }
  else
    {
      *a = *a % b;
    }
}


static int modulo(int a, int b)
{
  if (a < 0)
    {
      while (a < 0)
        {
          a = b + a;
        }
      return a;
    }
  else
    {
      return a % b;
    }
}

static int get_next_bucket_prime(int current_size)
{
  int i = 0;
  while(i < num_primes && current_size >= primes[i])
    {
      i++;
    }
  return primes[i];
}

static bool ioopm_hash_table_rehash(int key, elem_t value, void *new_ht)
{
  ioopm_hash_table_insert(new_ht, key, value);
  return true;
}

static void ioopm_hash_table_resize(ioopm_hash_table_t *ht)
{
  int load_factor = ht->size / ht->buckets_size;
  if (load_factor > MAX_LOAD_FACTOR)
    { 
      ///create new temp hash_table
      ioopm_hash_table_t new_ht;
      new_ht.buckets_size = get_next_bucket_prime(ht->buckets_size);
      new_ht.size = 0;
      new_ht.buckets = calloc(new_ht.buckets_size, sizeof(entry_t));

      //ioopm_hash_table_t *new_ht = calloc(1, sizeof(ioopm_hash_table_t));
      //new_ht->buckets_size = get_next_bucket_prime(ht->buckets_size);
      //new_ht->buckets = calloc(new_ht->buckets_size, sizeof(entry_t));
      //new_ht->size = 0; 
      
      //fill new temp hash_table with old entries.
      ioopm_hash_table_apply_to_all(ht, ioopm_hash_table_rehash, &new_ht);
      
      //free the memory of the old hash_table
      ioopm_hash_table_clear(ht);
      free(ht->buckets);
      *ht = new_ht;
      return;
    }
  else
    {
      return;
    }
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, elem_t value)
{
  ioopm_hash_table_resize(ht);
  int bucket = key;
  modulo_(&bucket, ht->buckets_size);
  entry_t *entry = find_previous_entry_for_key(&ht->buckets[bucket], key);
  entry_t *next = entry->next;

  if (next != NULL && next->key == key)
    {
      next->value = value;
    }
  else
    {
      entry->next = entry_create(key, value, next);
      ht->size += 1;
    }
}


elem_t *ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key)
{
  int bucket = modulo(key, ht->buckets_size);
  entry_t *entry = find_previous_entry_for_key(&ht->buckets[bucket], key);
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


//TODO: Define behavior for failure to find key
elem_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, int key)
{
  int bucket = modulo(key, ht->buckets_size);
  entry_t *entry = find_previous_entry_for_key(&ht->buckets[bucket], key);
  entry_t *next = entry->next;
  
  if (next != NULL && next->key == key)
    {
      elem_t removed_value = next->value;
      entry->next = entry->next->next;
      entry_destroy(next);
      entry->next = NULL;
      ht->size -= 1;
      return removed_value;
    }
  else
    {
      elem_t elem = {.void_ptr = NULL};
      return elem;
    }
}


void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{
  ioopm_hash_table_clear(ht);
  entry_t *first_entry = &ht->buckets[0];
  entry_destroy(first_entry);
  free(ht);
}


size_t ioopm_hash_table_size(ioopm_hash_table_t *ht)
{
  return ht->size;
}


bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht)
{
  for (int i = 0; i < ht->buckets_size; ++i)
    {
      entry_t *temp = &ht->buckets[i];
      if (temp->next != NULL)
        {
          return false;
        }
    }
  return true;
}


void ioopm_hash_table_clear(ioopm_hash_table_t *ht)
{
  for (int bucket = ht->buckets_size - 1; bucket >= 0; --bucket)
    {
      entry_t *first_entry = &ht->buckets[bucket];
      entry_t *entry, *next;
      
      if (first_entry->next != NULL)
        {
          entry = first_entry->next;
          next = entry->next;
          
          while (next != NULL)
            {
              entry_destroy(entry);
              entry = next;
              next = entry->next;
            }
          entry_destroy(entry);
          first_entry->next = NULL;
        }
    }
} 


ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht)
{
  ioopm_list_t *keys = ioopm_linked_list_create();

  for (int i = 0; i < ht->buckets_size; ++i)
    {
      entry_t *temp = &ht->buckets[i];
      entry_t *next = temp->next;
      elem_t elem;
      while (next != NULL)
        {
          elem.integer = next->key;
          ioopm_linked_list_append(keys, elem);
          next = next->next;
        }
    }
  return keys;
}


ioopm_list_t *ioopm_hash_table_values(ioopm_hash_table_t *ht)
{
  ioopm_list_t *values = ioopm_linked_list_create();

  for (int i = 0; i < ht->buckets_size; ++i)
    {
      entry_t *temp = &ht->buckets[i];
      entry_t *next = temp->next;
      while (next != NULL) // Kan optimeras, se 5.2.1
        {
          ioopm_linked_list_append(values, next->value);
          next = next->next;
        }
    }
  return values;
}


static bool key_equiv(int key, elem_t value_ignored, void *x)
{
  return key == *((int *) x);
}


bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, int key)
{
  return ioopm_hash_table_any(ht, key_equiv, &key);
}


bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, elem_t value, ioopm_apply_function compare_func)
{
  return ioopm_hash_table_any(ht, compare_func, &value);
}

bool ioopm_hash_table_all(ioopm_hash_table_t *h, ioopm_apply_function pred, void *arg)
{
  int size = ioopm_hash_table_size(h);
  ioopm_list_t *keys = ioopm_hash_table_keys(h);
  ioopm_list_t *values = ioopm_hash_table_values(h);
  bool result = true;
  
  for (int i = 0; i < size && result; i++)
    {
      result = result && pred(ioopm_linked_list_remove(keys, 0).integer, ioopm_linked_list_remove(values, 0) , arg);
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
      if (pred(ioopm_linked_list_remove(keys, 0).integer, ioopm_linked_list_remove(values, 0), arg))
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
  for (int i = 0; i < h->buckets_size; ++i)
    {
      entry_t *temp = &h->buckets[i];
      entry_t *next = temp->next;
      while (next != NULL) // Kan optimeras, se 5.2.1
        {
          apply_fun(next->key, next->value, arg);
          next = next->next;
        }
    }
  return;
}

/// ONLY usED FOR TESTSING
size_t ioopm_hash_table_buckets_size(ioopm_hash_table_t *ht)
{
  return ht->buckets_size;
}
