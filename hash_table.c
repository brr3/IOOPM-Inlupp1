#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash_table.h"


struct entry
{
  int key;       // holds the key                                                                                                                         
  char *value;   // holds the value                                                                                                                       
  entry_t *next; // points to the next entry (possibly NULL)                                                                                              
};

struct hash_table
{
  entry_t buckets[No_Buckets];
};


ioopm_hash_table_t *ioopm_hash_table_create()
{
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
          return previous_entry;
        }
      previous_entry = next_entry;
      next_entry = next_entry->next;
    }
  return first_entry;
}


static entry_t *entry_create(int key, char *value, entry_t *next)
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


void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value)
{
  int bucket = key;
  modulo_(&bucket, No_Buckets);
  entry_t *entry = find_previous_entry_for_key(&ht->buckets[bucket], key);
  entry_t *next = entry->next;

  if (next != NULL && next->key == key)
    {
      next->value = value;
    }
  else
    {
      entry->next = entry_create(key, value, next);
    }
}


char **ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key)
{
  int bucket = modulo(key, No_Buckets);
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


char *ioopm_hash_table_remove(ioopm_hash_table_t *ht, int key)
{
  int bucket = modulo(key, No_Buckets);
  entry_t *entry = find_previous_entry_for_key(&ht->buckets[bucket], key);
  entry_t *next = entry->next;
  
  if (next != NULL && next->key == key)                                                                       
    {
      char *removed_value = next->value;
      
      entry->next = entry->next->next;
      entry_destroy(next);
      entry->next = NULL;
      
      return removed_value;                                                                                    
    }                                                                                                         
  else                                                                                                        
    {                                                                                                         
      return NULL;                                                                                            
    }                                                                                                        
}


void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{
  ioopm_hash_table_clear(ht);
  entry_t *first_entry = &ht->buckets[0];
  entry_destroy(first_entry);
}


static size_t ioopm_hash_table_size_sr(ioopm_hash_table_t *ht, entry_t *temp, int counter, int i)
{
  if (i >= No_Buckets)
    {
      return (size_t) counter;
    } else if (temp->next != NULL)
    {
      return ioopm_hash_table_size_sr(ht, temp->next, counter + 1, i);
    } else
    {
      return ioopm_hash_table_size_sr(ht, &ht->buckets[i + 1], counter, i + 1);
    }
}



size_t ioopm_hash_table_size(ioopm_hash_table_t *ht) // ACHIEVEMENT F14 DEMO
{
  return ioopm_hash_table_size_sr(ht, &ht->buckets[0], 0, 0);
}

 
size_t ioopm_hash_table_size_i(ioopm_hash_table_t *ht)
{
  int counter = 0;
  for (int i = 0; i < No_Buckets; i++)
    {
      entry_t *temp = &ht->buckets[i];
      while(temp->next != NULL)
        {
          temp = temp->next;
          counter = counter + 1;
        }        
    }
  return (size_t) counter;
}


bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht)
{
  for (int i = 0; i < No_Buckets; ++i)
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
  for (int bucket = No_Buckets - 1; bucket >= 0; --bucket)
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


int *ioopm_hash_table_keys(ioopm_hash_table_t *ht)
{
  size_t ht_size = ioopm_hash_table_size(ht);
  int *keys = calloc(ht_size, sizeof(int));
  int n = 0;

  for (int i = 0; i < No_Buckets; ++i)
    {
      entry_t *temp = &ht->buckets[i];
      entry_t *next = temp->next;
      while (next != NULL)
        {
          keys[n] = next->key;
          next = next->next;
          ++n;
        }
    }
  return keys;
}


char **ioopm_hash_table_values(ioopm_hash_table_t *ht)
{
  size_t ht_size = ioopm_hash_table_size(ht);
  char **values = calloc(ht_size + 1, sizeof(char*)); // +1 for string terminator NULL
  int n = 0;

  for (int i = 0; i < No_Buckets; ++i)
    {
      entry_t *temp = &ht->buckets[i];
      entry_t *next = temp->next;
      while (next != NULL) // Kan optimeras, se 5.2.1
        {
          values[n] = next->value;
          next = next->next;
          ++n;
        }
    }
  values[n] = NULL;
  return values;
}


//kan implementeras m.h.a hash_table_apply_to_all
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, int key)
{
  char **value_ptr = ioopm_hash_table_lookup(ht, key);
  if (value_ptr == NULL)
    {
      return false;
    } else
    {
      return true;
    }
}

//kan implementeras m.h.a hash_table_apply_to_all
bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, char *value)
{
  entry_t *entry, *next;

  for (int i = 0; i < No_Buckets; ++i)
    {
      entry = &ht->buckets[i];
      next = entry->next;
      while (next != NULL)
        {
          if (strcmp(next->value, value) == 0)
            {
              return true;
            }
          next = next->next;
        }
    }
  return false;
}

//kan implementeras m.h.a hash_table_apply_to_all
bool ioopm_hash_table_all(ioopm_hash_table_t *h, ioopm_apply_function pred, void *arg)
{
  //Behöver optimiseras
  int size = ioopm_hash_table_size(h);
  int *keys = ioopm_hash_table_keys(h);
  char **values = ioopm_hash_table_values(h);
  bool result = true;
  
  for (int i = 0; i < size && result; i++)
    {
      result = result && pred(keys[i], values[i], arg);
    }
  free(keys);
  free(values);
  return result;  
}

//kan implementeras m.h.a hash_table_apply_to_all
bool ioopm_hash_table_any(ioopm_hash_table_t *h, ioopm_apply_function pred, void *arg)
{
  //Behöver optimiseras
  int size = ioopm_hash_table_size(h);
  int *keys = ioopm_hash_table_keys(h);
  char **values = ioopm_hash_table_values(h);
  for (int i = 0; i < size; i++)
    {
      if (pred(keys[i], values[i], arg))
        {
          free(keys);
          free(values);
          return true;
        }
    }
  free(keys);
  free(values);
  return false;
}

void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *h, ioopm_apply_function apply_fun, void *arg)
{
  //Behöver optimiseras
  int size = ioopm_hash_table_size(h);
  int *keys = ioopm_hash_table_keys(h);
  char **values = ioopm_hash_table_values(h);
  
  for (int i = 0; i < size; i++)
    {
      apply_fun(keys[i], values[i], arg);
    }
  free(keys);
  free(values);
  return;
}
