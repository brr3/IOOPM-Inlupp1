#ifndef __COMMON__
#define __COMMON__
#include <stdbool.h>

typedef union elem elem_t;

union elem
{
  int integer;
  unsigned int unsigned_integer;
  bool boolean;
  float float_number;
  char *string;
  void *void_ptr;
};

//Compares 2 elements, returns 0 if they are equal.
//± has meaning depending on type.
typedef int(*cmp_fun_t)(elem_t a, elem_t b);
  
#endif
