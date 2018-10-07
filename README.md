# IOOPM-Inlupp1

Authors: Bruno Rees, Alicia Nilsson, Henrik Johansson

Build (seperate files):
make test_hash
make test_list
make test_iterator

Run:
./test_hash
./test_list
./test_iterator

Performance tests:
All tests done without printing the words & frequency in freq_count.c
Max load factor = 10

bigbigbig.txt (bigger than all provided files)

  %   cumulative   self              self     total           
 time   seconds   seconds    calls  ms/call  ms/call  name    
 50.03      0.08     0.08  8439434     0.00     0.00  cmp_string
 18.76      0.11     0.03  1121673     0.00     0.00  ioopm_hash_table_lookup
 12.51      0.13     0.02  1208437     0.00     0.00  hash_string
  6.25      0.14     0.01  1121673     0.00     0.00  process_word
  6.25      0.15     0.01        1    10.01    10.01  ioopm_hash_table_create
  6.25      0.16     0.01        1    10.01   150.09  process_file
  0.00      0.16     0.00  1208437     0.00     0.00  find_previous_entry_for_key
  0.00      0.16     0.00  1208437     0.00     0.00  modulo
  0.00      0.16     0.00    86764     0.00     0.00  entry_create
  0.00      0.16     0.00    86764     0.00     0.00  ioopm_hash_table_insert
  0.00      0.16     0.00    86764     0.00     0.00  ioopm_hash_table_resize
  0.00      0.16     0.00    44902     0.00     0.00  entry_destroy
  0.00      0.16     0.00    44902     0.00     0.00  ioopm_hash_table_rehash
  0.00      0.16     0.00        8     0.00     0.00  get_next_bucket_prime
  0.00      0.16     0.00        8     0.00     0.00  ioopm_hash_table_apply_to_all
  0.00      0.16     0.00        8     0.00     0.00  ioopm_hash_table_clear

Top 3 functions:
cmp_string
ioopm_hash_table_lookup
hash_string



16k-words.txt

  %   cumulative   self              self     total           
 time   seconds   seconds    calls  Ts/call  Ts/call  name    
  0.00      0.00     0.00   173670     0.00     0.00  cmp_string
  0.00      0.00     0.00    26851     0.00     0.00  find_previous_entry_for_key
  0.00      0.00     0.00    26851     0.00     0.00  hash_string
  0.00      0.00     0.00    26851     0.00     0.00  modulo
  0.00      0.00     0.00    16992     0.00     0.00  ioopm_hash_table_lookup
  0.00      0.00     0.00    16992     0.00     0.00  process_word
  0.00      0.00     0.00     9859     0.00     0.00  entry_create
  0.00      0.00     0.00     9859     0.00     0.00  ioopm_hash_table_insert
  0.00      0.00     0.00     9859     0.00     0.00  ioopm_hash_table_resize
  0.00      0.00     0.00     5489     0.00     0.00  entry_destroy
  0.00      0.00     0.00     5489     0.00     0.00  ioopm_hash_table_rehash
  0.00      0.00     0.00        5     0.00     0.00  get_next_bucket_prime
  0.00      0.00     0.00        5     0.00     0.00  ioopm_hash_table_apply_to_all
  0.00      0.00     0.00        5     0.00     0.00  ioopm_hash_table_clear
  0.00      0.00     0.00        1     0.00     0.00  ioopm_hash_table_create
  0.00      0.00     0.00        1     0.00     0.00  process_file

Top 3 functions:
cmp_string
find_previous_entry_for_key
hash_string



10k-words.txt

  %   cumulative   self              self     total           
 time   seconds   seconds    calls  Ts/call  Ts/call  name    
  0.00      0.00     0.00    69893     0.00     0.00  cmp_string
  0.00      0.00     0.00    10386     0.00     0.00  find_previous_entry_for_key
  0.00      0.00     0.00    10386     0.00     0.00  hash_string
  0.00      0.00     0.00    10386     0.00     0.00  modulo
  0.00      0.00     0.00    10000     0.00     0.00  ioopm_hash_table_lookup
  0.00      0.00     0.00    10000     0.00     0.00  process_word
  0.00      0.00     0.00      386     0.00     0.00  entry_create
  0.00      0.00     0.00      386     0.00     0.00  ioopm_hash_table_insert
  0.00      0.00     0.00      386     0.00     0.00  ioopm_hash_table_resize
  0.00      0.00     0.00      187     0.00     0.00  entry_destroy
  0.00      0.00     0.00      187     0.00     0.00  ioopm_hash_table_rehash
  0.00      0.00     0.00        1     0.00     0.00  get_next_bucket_prime
  0.00      0.00     0.00        1     0.00     0.00  ioopm_hash_table_apply_to_all
  0.00      0.00     0.00        1     0.00     0.00  ioopm_hash_table_clear
  0.00      0.00     0.00        1     0.00     0.00  ioopm_hash_table_create
  0.00      0.00     0.00        1     0.00     0.00  process_file

Top 3 functions:
cmp_string
find_previous_entry_for_key
hash_string



1k-long-words.txt

  %   cumulative   self              self     total           
 time   seconds   seconds    calls  Ts/call  Ts/call  name    
  0.00      0.00     0.00     2765     0.00     0.00  cmp_string
  0.00      0.00     0.00     1023     0.00     0.00  find_previous_entry_for_key
  0.00      0.00     0.00     1023     0.00     0.00  hash_string
  0.00      0.00     0.00     1023     0.00     0.00  modulo
  0.00      0.00     0.00     1000     0.00     0.00  ioopm_hash_table_lookup
  0.00      0.00     0.00     1000     0.00     0.00  process_word
  0.00      0.00     0.00       23     0.00     0.00  entry_create
  0.00      0.00     0.00       23     0.00     0.00  ioopm_hash_table_insert
  0.00      0.00     0.00       23     0.00     0.00  ioopm_hash_table_resize
  0.00      0.00     0.00        1     0.00     0.00  ioopm_hash_table_create
  0.00      0.00     0.00        1     0.00     0.00  process_file

Top 3 functions:
cmp_string
find_previous_entry_for_key
hash_string



small.txt

  %   cumulative   self              self     total           
 time   seconds   seconds    calls  Ts/call  Ts/call  name    
  0.00      0.00     0.00       54     0.00     0.00  find_previous_entry_for_key
  0.00      0.00     0.00       54     0.00     0.00  hash_string
  0.00      0.00     0.00       54     0.00     0.00  modulo
  0.00      0.00     0.00       50     0.00     0.00  cmp_string
  0.00      0.00     0.00       27     0.00     0.00  entry_create
  0.00      0.00     0.00       27     0.00     0.00  ioopm_hash_table_insert
  0.00      0.00     0.00       27     0.00     0.00  ioopm_hash_table_lookup
  0.00      0.00     0.00       27     0.00     0.00  ioopm_hash_table_resize
  0.00      0.00     0.00       27     0.00     0.00  process_word
  0.00      0.00     0.00        1     0.00     0.00  ioopm_hash_table_create
  0.00      0.00     0.00        1     0.00     0.00  process_file

Top 3 functions:
find_previous_entry_for_key
hash_string
modulo
