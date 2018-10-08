All tests done without printing the words & frequency in freq_count.c

bigbigbig.txt (6 MB)

Max load factor = 10

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

Max load factor = 5

  %   cumulative   self              self     total           
 time   seconds   seconds    calls  ms/call  ms/call  name    
 30.02      0.06     0.06  1208437     0.00     0.00  find_previous_entry_for_key
 25.02      0.11     0.05  8439434     0.00     0.00  cmp_string
 25.02      0.16     0.05  1208437     0.00     0.00  hash_string
 15.01      0.19     0.03  1121673     0.00     0.00  process_word
  5.00      0.20     0.01  1121673     0.00     0.00  ioopm_hash_table_lookup
  0.00      0.20     0.00  1208437     0.00     0.00  modulo
  0.00      0.20     0.00    86764     0.00     0.00  entry_create
  0.00      0.20     0.00    86764     0.00     0.00  ioopm_hash_table_insert
  0.00      0.20     0.00    86764     0.00     0.00  ioopm_hash_table_resize
  0.00      0.20     0.00    44902     0.00     0.00  entry_destroy
  0.00      0.20     0.00    44902     0.00     0.00  ioopm_hash_table_rehash
  0.00      0.20     0.00        8     0.00     0.00  get_next_bucket_prime
  0.00      0.20     0.00        8     0.00     0.00  ioopm_hash_table_apply_to_all
  0.00      0.20     0.00        8     0.00     0.00  ioopm_hash_table_clear
  0.00      0.20     0.00        1     0.00     0.00  ioopm_hash_table_create
  0.00      0.20     0.00        1     0.00   200.12  process_file
  
  Max load factor = 100
  
    %   cumulative   self              self     total           
 time   seconds   seconds    calls  ms/call  ms/call  name    
 52.66      0.10     0.10 14931437     0.00     0.00  cmp_string
 21.07      0.14     0.04  1206144     0.00     0.00  find_previous_entry_for_key
 10.53      0.16     0.02  1121673     0.00     0.00  ioopm_hash_table_lookup
 10.53      0.18     0.02  1121673     0.00     0.00  process_word
  5.27      0.19     0.01  1206144     0.00     0.00  modulo
  0.00      0.19     0.00  1206144     0.00     0.00  hash_string
  0.00      0.19     0.00    84471     0.00     0.00  entry_create
  0.00      0.19     0.00    84471     0.00     0.00  ioopm_hash_table_insert
  0.00      0.19     0.00    84471     0.00     0.00  ioopm_hash_table_resize
  0.00      0.19     0.00    42609     0.00     0.00  entry_destroy
  0.00      0.19     0.00    42609     0.00     0.00  ioopm_hash_table_rehash
  0.00      0.19     0.00        7     0.00     0.00  get_next_bucket_prime
  0.00      0.19     0.00        7     0.00     0.00  ioopm_hash_table_apply_to_all
  0.00      0.19     0.00        7     0.00     0.00  ioopm_hash_table_clear
  0.00      0.19     0.00        1     0.00     0.00  ioopm_hash_table_create
  0.00      0.19     0.00        1     0.00   190.12  process_file

Top 3 functions (max load factor 10):            
cmp_string
ioopm_hash_table_lookup
hash_string

Top 3 functions (max load factor 5):    
find_previous_entry_for_key
cmp_string
hash_string

Top 3 functions (max load factor 100):  
cmp_string
find_previous_entry_for_key
ioopm_hash_table_lookup



16k-words.txt

Max load factor = 10

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

Max load factor = 5

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

Max load factor = 100

  %   cumulative   self              self     total           
 time   seconds   seconds    calls  Ts/call  Ts/call  name    
  0.00      0.00     0.00   286177     0.00     0.00  cmp_string
  0.00      0.00     0.00    26444     0.00     0.00  find_previous_entry_for_key
  0.00      0.00     0.00    26444     0.00     0.00  hash_string
  0.00      0.00     0.00    26444     0.00     0.00  modulo
  0.00      0.00     0.00    16992     0.00     0.00  ioopm_hash_table_lookup
  0.00      0.00     0.00    16992     0.00     0.00  process_word
  0.00      0.00     0.00     9452     0.00     0.00  entry_create
  0.00      0.00     0.00     9452     0.00     0.00  ioopm_hash_table_insert
  0.00      0.00     0.00     9452     0.00     0.00  ioopm_hash_table_resize
  0.00      0.00     0.00     5082     0.00     0.00  entry_destroy
  0.00      0.00     0.00     5082     0.00     0.00  ioopm_hash_table_rehash
  0.00      0.00     0.00        4     0.00     0.00  get_next_bucket_prime
  0.00      0.00     0.00        4     0.00     0.00  ioopm_hash_table_apply_to_all
  0.00      0.00     0.00        4     0.00     0.00  ioopm_hash_table_clear
  0.00      0.00     0.00        1     0.00     0.00  ioopm_hash_table_create
  0.00      0.00     0.00        1     0.00     0.00  process_file

Top 3 functions (max load factor 10):
cmp_string
find_previous_entry_for_key
hash_string

Top 3 functions (max load factor 5):
cmp_string
find_previous_entry_for_key
hash_string

Top 3 functions (max load factor 100):
cmp_string
find_previous_entry_for_key
hash_string



10k-words.txt
Max load factor = 10

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
Max load factor = 10

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
Max load factor = 10

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
