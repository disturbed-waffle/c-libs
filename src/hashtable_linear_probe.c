#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "../hashtable.h"

#define MAX_KEY 256
#define TABLE_SIZE 10
#define DELETED_NODE (item *)(0xFFFFFFFFFFFFFFFF)
#define VALUE_TYPE int

typedef struct{
    char key[MAX_KEY];
    VALUE_TYPE value;
}item;

item *hash_table[TABLE_SIZE];

unsigned int hash(const char *key){
    int length = strlen(key);
    unsigned int hash_value = 0;
    for (int i=0; i< length; i++){
        hash_value += key[i];
        hash_value = (hash_value*key[i]) % TABLE_SIZE;
    }
    return hash_value;
}

void init_hash_table(){
    for (int i=0; i<TABLE_SIZE; i++){
        hash_table[i] = NULL;
    }
}

void print_table(){
    printf("Start");
    for (int i=0; i<TABLE_SIZE; i++){
        if (hash_table[i] == NULL || hash_table[i] == DELETED_NODE){
            printf("\t%d\t--\n",i);
        }else{
            printf("\t%d\t%s\n", i, hash_table[i]->key);
        }
    }
    printf("End");
}

bool hash_table_insert(item *p){
    if (p==NULL) return false;
    int index = hash(p->key);
    
    //looking for open space
    for (int i=0; i<TABLE_SIZE; i++){
        int try = (index+i) % TABLE_SIZE;
        if (hash_table[try] == NULL ||
            hash_table[try] == DELETED_NODE){
            hash_table[try] = p;
            return true;
        }
    }
    // table full
    return false;
}

// find item in table by key, with few collisions ~O(1) but will increase with more collsions
item *hash_table_lookup(const char *key){
    int index = hash(key);

    // if not at index keep going since insertion acccounts for collision
    for (int i=0; i < TABLE_SIZE; i++){
       int try = (index + i) % TABLE_SIZE;
        if (hash_table[try] == NULL) return NULL; // Empty so can't have existed
        if (hash_table[try] == DELETED_NODE) continue;

        if (strncmp(key, hash_table[try]->key, MAX_KEY)==0){
            return hash_table[try];
        }  
    }
    return NULL;
}

item *hash_table_delete(const char *key){
    int index = hash(key);

    for (int i=0; i < TABLE_SIZE; i++){
       int try = (index + i) % TABLE_SIZE;
       if (hash_table[try] == NULL) return NULL;
       if (hash_table[try] == DELETED_NODE) continue;

       if (strncmp(key, hash_table[try]->key, MAX_KEY)==0){       
            hash_table[try] = DELETED_NODE;
            return hash_table[try];
        }  
    }
    return NULL;
}

int main(){

    init_hash_table();
    item joseph = {"Joseph", 19};
    item gertrude = {"Gertrude", 23};
    item sammy = {"Sammy", 32};
    item john = {"John", 12};
    item billy = {"Billy", 23};
    item mark = {"Mark", 17};
    item scooby = {"Scooby", 9};
    item booty = {"Booty", 100};
    
    
    hash_table_insert(&joseph);
    hash_table_insert(&gertrude);
    hash_table_insert(&sammy);
    hash_table_insert(&john);
    hash_table_insert(&billy);
    hash_table_insert(&mark);
    hash_table_insert(&scooby);
    hash_table_insert(&booty);
    
    
    print_table();
    item *tmp = hash_table_lookup("Gertrude");
    if (tmp == NULL || tmp == DELETED_NODE){
        printf("\nnot found\n");
    }else{
        printf("\nFound %s, %d\n\n", tmp->key, tmp->value);
    }

    hash_table_delete("Gertrude");
    print_table();

    // hash testing
    //printf("Sammy -> %u\n", hash("Sammy"));
    // printf("Steven -> %u\n", hash("Steven"));
    // printf("Chris -> %u\n", hash("Chris")); 

    return 0;
}