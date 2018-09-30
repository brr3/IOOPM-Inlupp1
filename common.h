#pragma once

typedef union elem elem_t;

union elem
{
  int integer;
  unsigned int unsigned_integer;
  bool boolean;
  float float_number;
  void *void_ptr;
};

//Compares 2 elements, returns 0 if they are equal.
//± has meaning depending on type.
typedef int(*cmp_fun_t)(elem_t a, elem_t b);


int cmp_int(elem_t a, elem_t b)
{
  return b.integer - a.integer;
}
  
