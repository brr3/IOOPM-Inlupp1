#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include "common.h"
#include "linked_list.h"

typedef struct entry entry_t;
typedef struct hash_table ioopm_hash_table_t;

#define No_Buckets 17 // ONLY USED IN TEST FILE
#define MAX_LOAD_FACTOR 10

/// @brief Create a new hash table
/// @param hash_function          | hash function to convert keys to a hash code
/// @param compare_key_function   | function to compare the keys
/// @param compare_value_function | function to compare the elements
/// @return A new empty hash table
ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function hash_function, ioopm_apply_function compare_key_func, ioopm_apply_function compare_value_func);

/// @brief add key => value entry in hash table ht
/// @param ht      | hash table operated upon
/// @param key     | key to insert
/// @param element | element to insert
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t element);

/// @brief lookup value for key in hash table ht
/// @param ht  | hash table operated upon
/// @param key | key to lookup
/// @return a pointer to the element mapped to by key, or NULL if the key doesn't exist
elem_t *ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key);

/// @brief remove any mapping from key to a value
/// @param ht  | hash table operated upon
/// @param key | key to remove
/// @return the element mapped to by key, or NULL if the key doesn't exist
elem_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key);

/// @brief destroy the entire hash table and its entries
/// @param ht | hash table operated upon
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);

/// @brief returns the number of key => value entries in the hash table
/// @param ht | hash table operated upon
/// @return the number of key => value entries in the hash table
size_t ioopm_hash_table_size(ioopm_hash_table_t *ht);

/// @brief checks if the hash table is empty
/// @param ht | hash table operated upon
/// @return true if size == 0, else false
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht);

/// @brief clear all the entries in a hash table
/// @param ht | hash table operated upon
void ioopm_hash_table_clear(ioopm_hash_table_t *ht);

/// @brief return the keys for all entries in a hash map (in no particular order, but same as ioopm_hash_table_values)
/// @param ht | hash table operated upon
/// @return a linked list of keys for hash table ht
ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht);

/// @brief return the values for all entries in a hash map (in no particular order, but same as ioopm_hash_table_keys)
/// @param ht | hash table operated upon
/// @return a linked list of values for hash table ht
ioopm_list_t *ioopm_hash_table_values(ioopm_hash_table_t *ht);

/// @brief check if a hash table has an entry with a given key
/// @param ht  | hash table operated upon
/// @param key | the key sought
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key);

/// @brief check if a hash table has an entry with a given value
/// @param ht    | hash table operated upon
/// @param value | the value sought
bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, elem_t value);

/// @brief check if a predicate is satisfied by all entries in a hash table
/// @param ht   | hash table operated upon
/// @param pred | the predicate 
/// @param arg  | extra argument to pred
bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_apply_function pred, void *arg);

/// @brief check if a predicate is satisfied by any entry in a hash table
/// @param ht   | hash table operated upon
/// @param pred | the predicate 
/// @param arg  | extra argument to pred
bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_apply_function pred, void *arg);

/// @brief apply a function to all entries in a hash table
/// @param ht        | hash table operated upon
/// @param apply_fun | the function to be applied to all elements
/// @param arg       | extra argument to apply_fun
void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function apply_fun, void *arg);

/// @brief get the size of the buckets array (ONLY INTENDED FOR TESTING)
/// @param ht | hash table operated upon
size_t ioopm_hash_table_buckets_size(ioopm_hash_table_t *ht);
