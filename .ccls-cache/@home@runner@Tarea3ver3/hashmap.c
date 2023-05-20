#include "hashmap.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HashMap HashMap;
int enlarge_called = 0;

struct HashMap {
  HPair **buckets;
  long size;     // cantidad de datos/pairs en la tabla
  long capacity; // capacidad de la tabla
  long current;  // indice del ultimo dato accedido
};

HPair *createPair(char *key, void *value) {
  HPair *new = (HPair *)malloc(sizeof(HPair));
  new->key = key;
  new->value = value;
  return new;
}

long hash(char *key, long capacity) {
  unsigned long hash = 0;
  char *ptr;
  for (ptr = key; *ptr != '\0'; ptr++) {
    hash += hash * 32 + tolower(*ptr);
  }
  return hash % capacity;
}

int is_equal(void *key1, void *key2) {
  if (key1 == NULL || key2 == NULL)
    return 0;
  if (strcmp((char *)key1, (char *)key2) == 0)
    return 1;
  return 0;
}

void insertMap(HashMap *map, char *key, void *value) {
  HPair *dato = createPair(key, value);    // crear par nuevo
  map->current = hash(key, map->capacity); // f.hash para posc de incs

  HPair **aux = map->buckets;
  long posicion = map->current; // pos actual

  // loop encontrar dispo
  while (aux[posicion] != NULL) {
    posicion++;
    if (posicion == (map->capacity))
      posicion = 0;
  }

  map->buckets[posicion] = dato; // se pone en dispo
  map->current = posicion;       // update pos actual
  map->size++;                   // ++
}

// done

void enlarge(HashMap *map) {
  enlarge_called = 1;                // no borrar (testing purposes)
  HPair **OldBuckets = map->buckets; // referencia oldb
  map->capacity *= 2;                // *2 capacidad
  HPair **newA =
      calloc(sizeof(HPair *), map->capacity); // nuevo arreglo de b con ++*2
  map->buckets = newA;
  // recorrer e insertar
  for (int i = 0; i < map->capacity / 2; i++) {
    if (OldBuckets[i] != NULL && OldBuckets[i]->key != NULL) {
      insertMap(map, OldBuckets[i]->key, OldBuckets[i]->value);
      // insertar again en mapa
    }
  }
}
// done

HashMap *createMap(long capacity) {
  // se explica solo ncfjfjf
  HashMap *map = (HashMap *)malloc(sizeof(HashMap));
  map->buckets = (HPair **)calloc(capacity, sizeof(HPair *));
  map->capacity = capacity;
  map->size = 0;
  map->current = -1;
  return map;
}
// done
void eraseMap(HashMap *map, char *key) {
  HPair *remove = searchMap(map, key);
  if (remove != NULL) {
    remove->key = NULL;
    (map->size)--;
  }
}
//: D

HPair *searchMap(HashMap *map, char *key) {
  int posicion = hash(key, map->capacity);
  while (map->buckets[posicion] != NULL) {
    if (is_equal(map->buckets[posicion]->key, key)) { // verific key
      map->current = posicion;       // pos act = pos encontrada
      return map->buckets[posicion]; // return par encontrado
    }
    posicion = (posicion + 1) % map->capacity; // avanzar
    if (posicion == hash(key, map->capacity))  // se llego al final
      break;
  }
  return NULL;
}
// done
HPair *firstMap(HashMap *map) {
  // itera
  for (int i = 0; i < map->capacity; i++) {
    // si current no esta vacio tiene key
    if (map->buckets[i] != NULL && map->buckets[i]->key != NULL) {
      // maps current a current
      map->current = i;

      return map->buckets[i];
    }
  }

  return NULL;
}
// done
HPair *nextMap(HashMap *map) {
  // itera desde current
  for (int i = map->current + 1; i < map->capacity; i++) {
    // si current no esta vacio tiene key
    if (map->buckets[i] != NULL && map->buckets[i]->key != NULL) {
      // maps current a current
      map->current = i;

      return map->buckets[i];
    }
  }
  return NULL;
}