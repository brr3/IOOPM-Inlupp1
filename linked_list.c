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
  void *data;
  node_t *next;
};
