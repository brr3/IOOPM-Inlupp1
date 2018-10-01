#include "linked_list.h"
#include "iterator.h"

typedef struct node node_t;

struct iter 
{
  node_t *current;
};

ioopm_list_iterator_t *list_iterator(ioopm_list_t *list)
{
  ioopm_list_iterator_t *result = calloc(1, sizeof(ioopm_list_iterator_t));
  result->current = list->first;
}
