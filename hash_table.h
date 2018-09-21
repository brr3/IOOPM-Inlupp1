#pragma once
#include <stdbool.h>


typedef struct entry entry_t;
typedef struct hash_table ioopm_hash_table_t;


#define No_Buckets 17


struct entry
{
  int key;       // holds the key
  char *value;   // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  entry_t buckets[No_Buckets];
};


/// @brief Create a new hash table
/// @return A new empty hash table
ioopm_hash_table_t *ioopm_hash_table_create();

/// @brief add key => value entry in hash table ht
/// @param ht hash table operated upon
/// @param key key to insert
/// @param value value to insert
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value);

/// @brief lookup value for key in hash table ht
/// @param ht hash table operated upon
/// @param key key to lookup
/// @return the value mapped to by key (temporary: return the pointer to the value mapped to by key)
char **ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key);

/// @brief remove any mapping from key to a value
/// @param ht hash table operated upon
/// @param key key to remove
/// @return the value mapped to by key (FIXME: incomplete)
char *ioopm_hash_table_remove(ioopm_hash_table_t *ht, int key);

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);

void ioopm_hash_table_destroy_r(ioopm_hash_table_t *ht, entry_t *entry, int bucket);
