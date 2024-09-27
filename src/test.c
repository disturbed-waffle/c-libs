#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hashtable.h"


int main(){
    hash_table_init();
    int ages[8];
    srand(time(NULL));
    for (int i=0; i<8;i++) {
        ages[i] = rand() % 100;
    }
    item joseph = {"Joseph", &ages[0]};
    item gertrude = {"Gertrude", &ages[1]};
    item sammy = {"Sammy", &ages[2]};
    item john = {"John", &ages[3]};
    item billy = {"Billy", &ages[4]};
    item mark = {"Mark", &ages[5]};
    item scooby = {"Scoob", &ages[6]};
    item booty = {"Poopy", &ages[7]};
    
    hash_table_insert(&joseph);
    hash_table_insert(&gertrude);
    hash_table_insert(&sammy);
    hash_table_insert(&john);
    hash_table_insert(&billy);
    hash_table_insert(&mark);
    hash_table_insert(&scooby);
    hash_table_insert(&booty);
    
    hash_table_print();
    char **keys = hash_table_keys();

    for (int i=0; i<hash_table_item_count(); i++){
        item *tmp = hash_table_lookup(keys[i]);
        printf("%s Age: %d\n", tmp->key, *(int *)tmp->value);
    }
    hash_table_delete(gertrude.key);
    keys = hash_table_keys();
    printf("%d",*(int *) hash_table_value("Billy"));



    return 0;
}