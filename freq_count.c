#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hash_table.h"


#define Delimiters "+-#@()[]{}.,:;!? \t\n\r"


int cmpstringp(const void *p1, const void *p2)
{
  return strcmp(* (char * const *) p1, * (char * const *) p2);
}


int hash_string(elem_t key)
{
  char *str = key.string;
  int result = 0;
  do
    {
      result = result * 31 + *str;
    }
  while (*++str != '\0'); 
  return result;
}


bool cmp_string(elem_t key_ignored, elem_t value, void *x)
{
  return !strcmp(key_ignored.string, ((elem_t *)x)->string);
}


bool cmp_int(elem_t key_ignored, elem_t value, void *x)
{
  return value.integer - *(int*)x == 0;
}

void sort_keys(char *keys[], size_t no_keys)
{  
  qsort(keys, no_keys, sizeof(char *), cmpstringp);
}


void process_word(char *word, ioopm_hash_table_t *ht)
{
  elem_t key = {.string = strdup(word)}; //TODO: Minnesläcka
  elem_t *elem_count = ioopm_hash_table_lookup(ht, key);
  if (elem_count != NULL)
    {
      elem_count->integer += 1;
    }
  else
    {
      elem_t value = {.integer = 1};
      ioopm_hash_table_insert(ht, key, value);
    }
}


void process_file(char *filename, ioopm_hash_table_t *ht)
{
  FILE *f = fopen(filename, "r");

  while (true) 
    {
      char *buf = NULL;
      size_t len = 0;
      getline(&buf, &len, f);

      if (feof(f))
        {
          free(buf);
          break;
        }
      
      for (char *word = strtok(buf, Delimiters);
           word && *word;
           word = strtok(NULL, Delimiters)
           )
        {
          process_word(word, ht);
        }

      free(buf);
    }  
  fclose(f);
}


bool word_print(elem_t key, elem_t value, void *arg)
{
  printf("Word: %s\nCount: %d\n", key.string, value.integer);
  return true;
}


int main(int argc, char *argv[])
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_string, cmp_string, cmp_int);
  
  if (argc > 1)
    {
      for (int i = 1; i < argc; ++i)
        {
          process_file(argv[i], ht);
        }
      /*
      ioopm_list_t *keys = ioopm_hash_table_keys(ht);
      int arr_size = ioopm_linked_list_size(keys);
      char *arr[arr_size];
      
      for (int i = 0; i < arr_size; i++)
        {
          arr[i] = ioopm_linked_list_remove(keys, 0).string; 
        }
      sort_keys(arr, (size_t)arr_size);
      for (int i = 0; i < arr_size; i++)
        {
          puts(arr[i]);
        }
      ioopm_hash_table_destroy(ht);*/
    }
  else
    {
      puts("Usage: freq-count file1 ... filen");
    }
}








typedef struct q_elem q_elem_t;
struct q_elem {
  char *key;
  int count;
};

typedef struct help_struct help_struct_t;
struct help_struct{
  q_elem_t *array;
  int cursor;
  int size;
};


bool entries_to_array(elem_t key, elem_t value, void *arg)
{
  q_elem_t temp;
  temp.key = key.string;
  temp.count = value.integer;
  ((help_struct_t *)arg)->array[((help_struct_t *)arg)->cursor] = temp; 
  return true;
}

