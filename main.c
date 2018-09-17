#include <stdlib.h>
#include "hash_table.h"

int main(int argc, char *argv[])
{
  ioopm_hash_table_t *h = ioopm_hash_table_create();
  free(h);
  return 0;
}
