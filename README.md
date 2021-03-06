# IOOPM-Inlupp1

Authors: Bruno Rees, Alicia Nilsson, Henrik Johansson

=========BUILD==========
make test_hash
make test_list
make freq_count // word processing program

=========MEMORY TESTS==========
make memtest_hash
make memtest_list

=========RUN TESTS==========
./test_hash
./test_list
make fulltest // build and run all of the above tests immediately

=========RUN WORD PROCESSING PROGRAM==========
./freq_count <file_1> <file_2> ... <file_n>

=========FAILURE HANDLING==========
All public functions found in the header files that may fail, for example when trying to remove an element from the hash table that does not exist, will return an "empty" (newly initiated) element of type elem_t with void_ptr set to NULL, see common.h.
When creating a new hash table, you must provide the functions mentioned in the header file or the program will crash (i.e. you cannot provide a NULL pointer).
All public functions found in the header files that take a list or a hash table as an argument does NOT handle NULL pointers.

=========OTHER NOTES==========
iterator.h is necessary for linked_list.c and linked_list_tests.c to successfully compile.

=========COVERAGE TESTS==========
hash_table.c
Lines executed:100.00% of 166
Branches executed:100.00% of 49

linked_list.c
Lines executed:97.50% of 120
Branches executed:100.00% of 32

=========PERFORMANCE TESTS==========
See initial-profiling.md.
