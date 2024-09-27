#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include "hashtable.h"

// global
static int table_size = 100;
static int item_count = 0;
static bool table_initialized = false;
static char **keys = NULL;
item **hash_table = NULL;

unsigned int hash(char *key){
    int length = strlen(key);
    unsigned int hash_value = 0;
    for (int i=0; i< length; i++){
        hash_value += key[i];
        hash_value = (hash_value*key[i]) % table_size;
    }
    return hash_value;
}

void hash_table_init(){
    if (table_initialized) return;

    hash_table = malloc(table_size * sizeof(item *));
    if (hash_table == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    for (int i=0; i<table_size; i++){
        hash_table[i] = NULL;
    }
    table_initialized = true;
}

void hash_table_init_size(int t_size){
    if (table_initialized) return;

    table_size = t_size;
    hash_table_init();
}

void hash_table_print(){
    printf("BEGIN\n");
    for (int i=0; i<table_size; i++){
        if (hash_table[i] == NULL){
            printf("\t%d\t--",i);
        }else{
            printf("\t%d\t", i);
            item *tmp = hash_table[i];
            while (tmp != NULL){
                printf("%s - ", tmp->key);
                tmp = tmp->_next;
            }
        }
        printf("\n");
    }
    printf("END\n");
}
int hash_table_insert(item *p){
    if (p==NULL) return STATUS_ERROR;
    int index = hash(p->key);
    item *tmp = hash_table[index];
    // Check if key already exists
    while(tmp != NULL){
        if (strcmp(tmp->key, p->key) == 0){
            tmp->value = p->value;
            return STATUS_REPLACED;
        }
        tmp = tmp->_next;
    }
    // Otherwise set as the head
    p->_next = hash_table[index];
    hash_table[index] = p;
    item_count++;
    return STATUS_SUCCESS;
}

item *hash_table_lookup(char *key){
    int index = hash(key);
    item *tmp = hash_table[index];
    while(tmp != NULL && strcmp(tmp->key, key) != 0){
        tmp = tmp->_next;
    }
    return tmp;
}

bool hash_table_contains(char *key){
    item *tmp = hash_table_lookup(key);
    if (tmp == NULL){
        return false;
    }else{
        return true;
    }
}
// Delete item
item *hash_table_delete(char *key){
    int index = hash(key);
    item *tmp = hash_table[index];
    item *prev = NULL;
    while(tmp != NULL && strcmp(tmp->key, key) != 0){
        prev = tmp;
        tmp = tmp->_next;
    }
    // Didn't find
    if (tmp == NULL ) return NULL;
    // found at head
    if (prev == NULL) {
        hash_table[index] = tmp->_next; //set _next to the head 
    }else{
        prev->_next = tmp->_next;
    }
    item_count--;
    return tmp;
}

void *hash_table_value(char *key){
    item *tmp = hash_table_lookup(key);
    void *value = tmp->value;
    return value;
}

char **hash_table_keys(){
    if (keys != NULL){
        for (int i=0; i < item_count; i++){
            free(keys[i]); // free each key string
        }
        free(keys); // free array of pointers
    }
    // Allocate memory for each key pointer
    keys = malloc(item_count * sizeof(char *));
    int key_index = 0;
    for (int i=0;i<table_size;i++){
        if (hash_table[i] == NULL){
            continue;
        }else{
            item *tmp = hash_table[i];
            while(tmp != NULL){
                keys[key_index] = strdup(tmp->key); // duplicates key string in memory and sets the pointer to this string 
                if (keys[key_index] == NULL) {
                    perror("strdup");
                    exit(EXIT_FAILURE);
                }
                key_index++;
                tmp = tmp->_next;
            }
        }
    }
    return keys;
}

void hash_table_deinit(){
    for (int i=0; i < table_size; i++){
        if (hash_table[i] == NULL){
            continue;
        }
        else{
            hash_table[i] = NULL;
        }
    }
    free(hash_table);
    hash_table = NULL;
    table_initialized = false;
}

// Attempts to free all items and their members from dynamic memmory
void hash_table_free(){
    
    if (!table_initialized) return;
    
    for (int i=0; i < table_size; i++){
        if (hash_table[i] == NULL){
            continue;
        }
        else{
            item *tmp = hash_table[i];
            while(tmp != NULL){
                item *next = tmp->_next;
                free(tmp->key);
                free(tmp->value);
                free(tmp);
                tmp = next;
            }
            hash_table[i] = NULL;
        }
    }
    free(hash_table);
    hash_table = NULL;
    table_initialized = false;
}

int hash_table_item_count(){
    return item_count;
}
