#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

typedef struct node node_t;

struct list
{
  node_t *first;
  node_t *last;
  int size;
};

struct node
{
  int *data; // Vi börjar med int och kan generalisera senare till void
  node_t *next;
};


ioopm_list_t *ioopm_linked_list_create()
{
  ioopm_list_t *new_list = calloc(1, sizeof(ioopm_list_t));
  if (new_list)
    {
      // Use of calloc will ensure result->first->next == NULL
      new_list->first = new_list->last = calloc(1, sizeof(node_t));
      new_list->size = 0;
    }
  return new_list;
}


// PRE: list != NULL 
void ioopm_linked_list_destroy(ioopm_list_t *list)
{
  ioopm_linked_list_clear(list);
  free(list->first); // Free the sentinel
  free(list);
  
  /* node_t *node = list->first;
  if (node != NULL)
    {
      node_t *next = node->next; 
      while (next != NULL)
        {
          free(node);
          node = next;
          next = next->next;
        }
    }
    free(list); */
}


// PRE: next != NULL
static node_t *link_new(int value, node_t *next)
{
  node_t *new_node = calloc(1, sizeof(node_t));

  if (new_node)
    {
      new_node->data = &value;
      new_node->next = next;
    }

  return new_node;
}


// PRE: list != NULL
void ioopm_linked_list_append(ioopm_list_t *list, int value)
{
  ioopm_linked_list_insert(list, ioopm_linked_list_size(list), value);
  /* // Alternativ lösning (mindre abstraktion):
  list->last->next = link_new(value, NULL);
  list->size++; */
}


// PRE: list != NULL
void ioopm_linked_list_prepend(ioopm_list_t *list, int value)
{
  ioopm_linked_list_insert(list, 0, value);
}


// PRE: first_node != NULL
static node_t *list_inner_find_previous(node_t *first_node, int index)
{
  node_t *previous_node = first_node;

  for (int i = 0; i < index; ++i)
    {
      previous_node = previous_node->next;
    }

  return previous_node;
}


static int list_inner_adjust_index(int index, int upper_bound)
{
  if (abs(index) > upper_bound)
    {
      index = upper_bound;
      return index;
    }
  return abs(index);
}


// PRE: list != NULL
void ioopm_linked_list_insert(ioopm_list_t *list, int index, int value)
{
  int list_size = ioopm_linked_list_size(list);
  int valid_index = list_inner_adjust_index(index, list_size + 1);

  node_t *previous_node;
  if (valid_index < list_size) {
    previous_node = list_inner_find_previous(list->first, valid_index);  
  }
  else
    {
      previous_node = list_inner_find_previous(list->last, valid_index);
    }
  
  previous_node->next = link_new(value, previous_node->next);

  list->size += 1;
}


// PRE: list != NULL
int ioopm_linked_list_remove(ioopm_list_t *list, int index)
{
  int list_size = ioopm_linked_list_size(list);
  int valid_index = list_inner_adjust_index(index, list_size);
  
  node_t *previous_node = list_inner_find_previous(list->first, valid_index);

  node_t *to_remove = previous_node->next;
  int removed_value = *to_remove->data;
  previous_node->next = to_remove->next;

  free(to_remove);                   
  
  list->size -= 1;
  
  return removed_value;
}


// PRE: list != NULL
int ioopm_linked_list_get(ioopm_list_t *list, int index)
{
  int list_size = ioopm_linked_list_size(list);
  int valid_index = list_inner_adjust_index(index, list_size);

  node_t *previous_node = list_inner_find_previous(list->first, valid_index);

  if (previous_node->next != NULL)
    {
      return *previous_node->next->data;
    }
  else
    {
      return *previous_node->data;
    }
}


static int compare_int_elements(int a, int b)
{
  return b - a;
}


// PRE: list != NULL
bool ioopm_linked_list_contains(ioopm_list_t *list, int value)
{
  for (node_t *cursor = list->first->next; cursor; cursor = cursor->next)
    {
      if (compare_int_elements(*cursor->data, value) == 0) return true; // compare_int_elements förbereder generalisering
    }
  return false;
}


// PRE: list != NULL
int ioopm_linked_list_size(ioopm_list_t *list)
{
  return list->size;
}


// PRE: list != NULL
bool ioopm_linked_list_is_empty(ioopm_list_t *list)
{
  return list->size == 0;
}


void ioopm_linked_list_clear(ioopm_list_t *list)
{
  int list_size = ioopm_linked_list_size(list);
  while (list_size > 0)
    {
      ioopm_linked_list_remove(list, 0);
    }
}


// PRE: list != NULL
bool ioopm_linked_list_all(ioopm_list_t *list, bool (*prop)(int, int), void *x) // TODO
{
  return false;
}


// PRE: list != NULL
bool ioopm_linked_list_any(ioopm_list_t *list, bool (*prop)(int, int), void *x) // TODO
{
  return false;
}


// PRE: list != NULL
void ioopm_linked_apply_to_all(ioopm_list_t *list, void (*fun)(int, int), void *x)
{
  for (node_t *cursor = list->first->next; cursor; cursor = cursor->next)
    {
      fun(*cursor->data, (int) x);
    }
}


