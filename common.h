#pragma once
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

// Compares 2 elements, returns 0 if they are equal.
// ± has meaning depending on implementation.
typedef int(*cmp_fun_t)(elem_t a, elem_t b);

typedef bool(*ioopm_apply_function)(elem_t key, elem_t value, void *extra);

// Convert key to a hash code
typedef int(*ioopm_hash_function)(elem_t key);
