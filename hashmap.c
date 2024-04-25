#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
    int pos = hash(key,map->capacity);
    int i = 0;
    while(map->buckets[pos + i]!=NULL && map->buckets[pos+ i]->key!=NULL)
    {
        if(map->buckets[pos + i] == NULL || map->buckets[pos + i]->key == NULL)
        {
            map->buckets[pos + i] = createPair(key, value);
            map->size++;
            break;
        }

    }

}
void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)
    Pair ** old_array = map->buckets;
    map->capacity *= 2;
    map->buckets = (Pair**)calloc(map->capacity,sizeof(Pair*));
    map->size = 0;
    for(int i  = 0; i < map->capacity / 2; i++)
      if(old_array[i] != NULL)
      {
        insertMap(map,old_array[i]->key,old_array[i]->value);
        free(old_array[i]);
      }
  
  
}


HashMap * createMap(long capacity) {
  
  HashMap * map = (HashMap *) malloc (sizeof(HashMap));
  map->buckets = (Pair **) calloc (capacity, sizeof(Pair *));
  map->size = 0;
  map->capacity = capacity;
  map->current = -1;
  return map;
}

void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) 
{

  
  int pos = hash(key,map->capacity);
  if(map->buckets[pos]!=NULL)
  {
    if(is_equal(map->buckets[pos]->key,key))
    {
      return map->buckets[pos];
    }
  }
  map->current = pos;
  return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
