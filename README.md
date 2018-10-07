# IOOPM-Inlupp1

LOAD_FACTOR = 10
bigbigbig.txt

Each sample counts as 0.01 seconds.
  %   cumulative   self              self     total           
 time   seconds   seconds    calls  ms/call  ms/call  name    
 45.03      0.09     0.09 14232491     0.00     0.00  cmp_string
 15.01      0.12     0.03       11     2.73     3.64  ioopm_hash_table_apply_to_all
 15.01      0.15     0.03  1501583     0.00     0.00  find_previous_entry_for_key
  5.00      0.16     0.01  1501583     0.00     0.00  hash_string
  5.00      0.17     0.01  1121673     0.00     0.00  process_word
  5.00      0.18     0.01   379910     0.00     0.00  ioopm_hash_table_insert
  5.00      0.19     0.01    51633     0.00     0.00  word_print
  5.00      0.20     0.01        1    10.01   200.13  process_file
  0.00      0.20     0.00  1501583     0.00     0.00  modulo
  0.00      0.20     0.00  1121673     0.00     0.00  ioopm_hash_table_lookup
  0.00      0.20     0.00   379910     0.00     0.00  ioopm_hash_table_resize
  0.00      0.20     0.00   231725     0.00     0.00  entry_create
  0.00      0.20     0.00   180092     0.00     0.00  entry_destroy
  0.00      0.20     0.00   180092     0.00     0.00  ioopm_hash_table_rehash
  0.00      0.20     0.00       10     0.00     0.00  get_next_bucket_prime
  0.00      0.20     0.00       10     0.00     0.00  ioopm_hash_table_clear
  0.00      0.20     0.00        1     0.00     0.00  ioopm_hash_table_create

