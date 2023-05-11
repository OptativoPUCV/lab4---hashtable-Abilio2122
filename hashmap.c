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
  int pos= hash(key,map->capacity);
  // en el caso de que este vacia la pos
  if(map->buckets[pos]==NULL){ 
    Pair *p = createPair(key, value);
    map->buckets[pos] = p;
    map->size++;
    map->current=pos;
    return;
  }
  //en el caso que este ocupada
  int next_pos = (pos + 1) % map->capacity;
    while (next_pos != pos) {
        if (map->buckets[next_pos] == NULL) {
            Pair *p = createPair(key, value);
            map->buckets[next_pos] = p;
            map->size++;
            map->current = next_pos;
            return;
        }
        next_pos = (next_pos + 1) % map->capacity;
    }
  //si no hay espacio disponible en el mapa no se insertará
  printf("Error: la tabla de hash está llena.\n");
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
  HashMap *map= (HashMap *) malloc(sizeof(HashMap));
  map->capacity=capacity;
  map->current=-1;
  map->buckets= (Pair **) calloc(capacity,sizeof(Pair *));

  
  return map;
}

void eraseMap(HashMap * map,  char * key) {    
  int pos=hash(key,map->capacity);
  int inicio = pos;
  
  while(map->buckets[pos]!=NULL){
    if(strcmp(map->buckets[pos]->key,key)==0){
      map->buckets[pos]->key=NULL;
      map->size--;
      return;
    }
    pos = ((pos + 1) % map -> capacity);
    if(pos==inicio){
    printf("no se encontro casilla a eliminar");
    break;
    }
  }
}

Pair * searchMap(HashMap * map,  char * key) {   
  int pos=hash(key,map->capacity);

  //en este while  recorre todo el arreglo desde la posicion del hash hasta un NULL
  while(map->buckets[pos]!=NULL){
    if(map->buckets[pos] != NULL && strcmp(map->buckets[pos]->key, key) == 0){
      map->current=pos;
      return map->buckets[pos];
    }
    //si no lo encuentra va para la proxima posicion como arreglo de colision
    pos = (pos + 1) % map->capacity;
  }
  //en el caso de que dentro de que salga del while quiere decir que no esta en el arreglo
  return NULL;
}

Pair * firstMap(HashMap * map) {
  int i=0;
  // recorro todo el arreglo hasta lelgar al fin
  while(i<map->capacity){
    if(map->buckets[i]!=NULL){
      map->current=i;
      return map->buckets[i];
    }
    i++;
  }
// si se salio de el while sin retornar quiere decir que esta vacio
  return NULL;
}

Pair * nextMap(HashMap * map) {
 // Si la posición actual es -1, no hay siguiente elemento
  if (map->current == -1) {
      return NULL;
  }
  
  for(int pos=map->current+1;pos<map->capacity;)
  
  // Si llegó al final del arreglo sin encontrar un par válido, establece la posición actual en -1 y devuelve NULL
  map->current = -1;

  return NULL;
}
