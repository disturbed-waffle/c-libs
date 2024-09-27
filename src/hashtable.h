
/*
Hash table with keys of type string 
and values stored as void pointers.
Only supports one active hash table at a time.
*/

//--------------
// DEFINES
// -------------

// Header gaurd
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>

/* 
    Items have a key and value pair and can be inserted into the hash_table
    linked list is used to avoid collisions at a given hash
    The latest item inseted will always be the head of the list 
    and last item's next pointer is NULL     
*/

// ITEM STRUCT
typedef struct item{
    char *key;
    void *value;
    struct item *_next;
}item;

enum {STATUS_ERROR, STATUS_SUCCESS, STATUS_REPLACED};

unsigned int hash(char *key);

// Initialize a new hash table
void hash_table_init(); 

void hash_table_init_size(int t_size);

// Prints out entire table with keys
void hash_table_print(); 

// Insert item into hashtable, replace equal keys, returns STATUS_CODE
int hash_table_insert(item *p); 

// returns item with given key, NULL if key is not found
item *hash_table_lookup(char *key); 

bool hash_table_contains(char *key);

// delete item with given key and return item, NULL if key not found
item *hash_table_delete(char *key); 

// return value of key
void *hash_table_value(char *key); 

// returns an array of all keys 
char **hash_table_keys(); 

// deinitialize current hash table;
void hash_table_deinit();

/* sussy among us
 Attempts to free all items and their members from dynamic memmory
 Do Not use if items or their members were not dynamically allocated
 Use hash_table_deinit */
void hash_table_free();

int hash_table_item_count();

#endif
