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
  int count = 0;
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


bool free_keys_from_hash_table(elem_t key, elem_t value_ignored, void *ignored)
{
  free(key.string);
  return true;
}

typedef struct word_count wc_t;

struct word_count {
  char *str;
  int count;
};

int main(int argc, char *argv[])
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(hash_string, cmp_string, cmp_int);
  
  if (argc > 1)
    {
      for (int i = 1; i < argc; ++i)
        {
          process_file(argv[i], ht);
        }
      
      ioopm_list_t *words = ioopm_hash_table_keys(ht);
      int arr_size = ioopm_linked_list_size(words);
      char *arr_words[arr_size];
      
      for (int i = 0; i < arr_size; i++)
        {
          arr_words[i] = ioopm_linked_list_remove(words, 0).string; 
        }
      sort_keys(arr_words, (size_t)arr_size);

      int arr_count[arr_size];
      for (int i = 0; i < arr_size; i++)
        {
          elem_t temp = {.string = arr_words[i]};
          arr_count[i] = ioopm_hash_table_lookup(ht, temp)->integer;
        }

      for (int i = 0; i < arr_size; i++)
	{
	  printf("[%d] %s\n", arr_count[i], arr_words[i]);
	}
      
      ioopm_hash_table_apply_to_all(ht, free_keys_from_hash_table, NULL);
      ioopm_hash_table_destroy(ht);
    }
  else
    {
      puts("Usage: freq-count file1 ... filen");
    }
}

