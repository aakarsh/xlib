#ifndef HTABLE_H
#define HTABLE_H
#include "list.h"

struct htable*  htable_create(size_t min_size);

void* htable_find(struct htable* htable,
                  void* key,
                  size_t key_size);

void htable_remove(void* key, struct htable* t);

struct htable_entry {
  void* key;
  size_t key_size;
  void* data;
};

struct htable_elem {
  struct list* chain;
};

struct htable {
  struct htable_elem** elems;
  size_t size;
  unsigned long (*hash_function)(void* key, size_t nbytes);
};

unsigned long
sdmb_str_hash(void* key,
              size_t nbytes)
{
  unsigned char* str = (unsigned char*) key;
  unsigned long hash = 0;

  int c;
  while (nbytes > 0) {
    c = *str++;
    hash = c + (hash << 6) + (hash << 16) - hash;
    nbytes--;
  }
  return hash;
}

void
htable_add(struct htable* htable,
                void* key,
                size_t key_size,
                void* data)
{
  unsigned long hash = htable->hash_function(key,key_size);
  size_t index =  (hash % htable->size);
  struct htable_entry* entry =  malloc(sizeof(struct htable_entry));
  entry->key = key;
  entry->key_size = key_size;
  entry->data = data;
  
  if(!htable->elems[index]) {
    htable->elems[index] = malloc(sizeof (struct htable_elem));
    htable->elems[index]->chain = list_node(entry,sizeof(entry));
  }
}

void*
htable_find(struct htable* htable,
                  void* key,
                  size_t key_size)
{
  unsigned long hash = htable->hash_function(key,strlen(key)+1);
  size_t index =  (hash % htable->size);
  
  if(htable->elems[index] != NULL) {
    struct list* chain = htable->elems[index]->chain;
    struct htable_entry* entry = NULL;
    while(chain!=NULL) {
      entry =  (struct htable_entry*)  chain->data;
      if((entry->key ,key)) {
        return entry->data;
      }
      chain = chain->next;
    }
  }
  return NULL;
}

struct htable*
htable_create(size_t min_size)
{
  struct htable* t =  malloc(sizeof(struct htable));
  t->size  = min_size;
  t->elems = calloc(sizeof(struct htable_elem),min_size);
  t->hash_function = sdmb_str_hash;
  return t;
}

#endif
