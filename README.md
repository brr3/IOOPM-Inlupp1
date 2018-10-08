# IOOPM-Inlupp1

Authors: Bruno Rees, Alicia Nilsson, Henrik Johansson

Build (seperate files):
make test_hash
make test_list
make test_iterator
make freq_count 

Memory tests:
make memtest_hash
make memtest_list
make memtest_iterator

Run:
./test_hash
./test_list
./test_iterator
make fulltest (compile and run all of the above immediately)
./freq_count <file_1> <file_2> ... <file_n>

How failure is handled: 
All public functions found in the header files that may fail, for example when trying to remove an element from the hash table that does not exist, will return an "empty" (newly initiated) element of type elem_t (see common.h).

