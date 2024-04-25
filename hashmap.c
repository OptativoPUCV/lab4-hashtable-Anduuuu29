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
  while(map->buckets[pos]!=NULL)
    {
      if(is_equal(map->buckets[pos]->key,key))
      {
        map->buckets[pos]->value=value;
      }
      pos = (pos+1)%map->capacity;
    }
  if(map->buckets[pos]==NULL)
  {
    map->buckets[pos]=createPair(key,value);
    map->size++;
    map->current++;
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
  Pair *dato = searchMap(map, key);
  if(dato != NULL)
  {
    dato->key = NULL;
    map->size--;
  }
}

Pair * searchMap(HashMap * map,  char * key) 
{
  int pos = hash(key,map->capacity);
  while(map->buckets[pos]!=NULL)
    {
      if(is_equal(map->buckets[pos]->key,key))
      {
        map->current = pos;
        return map->buckets[pos];
      }
      pos = (pos+1)%map->capacity;
    }
  return NULL;
}


Pair * firstMap(HashMap * map) {
  if(map == NULL)
    exit(EXIT_FAILURE);
  map->current = -1;
  return nextMap(map);
}

Pair * nextMap(HashMap * map) {
  if(map == NULL)
    exit(EXIT_FAILURE);
  for(int i = map->current + 1; i < map->capacity; i++)
    {
      if(map->buckets[i] != NULL)
      {
        map->current = i;
        return map->buckets[i];
      }
    }
  return map->buckets[map->current];
}
