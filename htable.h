#ifndef HTABLE_H
#define HTABLE_H

#include <string.h>
#include <assert.h>
#include "list.h"

static bool htable_debug = false;

struct htable*  htable_create(size_t min_size);

void*
htable_find(struct htable* htable,
            void* key,
            size_t key_size);

void
htable_remove(struct htable* t,
              void* key,
              size_t key_size);

void
htable_resize(struct htable* prev_table,
              size_t new_size);

void
htable_free_entries(struct htable* htable);

struct htable_entry {
  void* key;
  size_t key_size;
  void* data;
  size_t data_size;
};

struct htable_elem {
  struct list* chain;
};

struct htable {
  struct htable_elem** elems;
  size_t size;
  size_t nelems;
  double load_factor;  
  unsigned long (*hash_function)(void* key, size_t nbytes);
};


unsigned long
sdmb_str_hash(void* key,
              size_t nbytes)
{
  unsigned char* str = (unsigned char*) key;
  unsigned long hash = 0;

  int c;
  int nb = nbytes;
  while (nb > 0) {
    c = *str++;
    hash = c + (hash << 6) + (hash << 16) - hash;
    nb--;
  }
  return hash;
}
           
void
htable_add(struct htable* htable,
           void* key,
           size_t key_size,
           void* data,
           size_t data_size)
{
  unsigned long hash =
    htable->hash_function(key,key_size);

  size_t index =  (hash % htable->size);

  struct htable_entry entry =
    {
     .key = key,
     .key_size = key_size,
     .data = data,
     .data_size = data_size
    };

  struct list *entry_node =
    list_node(&entry, sizeof(struct htable_entry));

  htable->elems[index]->chain =
    list_prepend(entry_node,htable->elems[index]->chain);
  
  htable->nelems++;
  
  if(htable->load_factor < (htable->nelems/(1.0 * htable->size))) {
      htable_resize(htable,htable->size*2);
  }
}

struct list*
htable_find_node(struct htable* htable,
                 size_t index,
                 void* key,
                 size_t key_size)
{
  struct list* chain = htable->elems[index]->chain;
  struct htable_entry* entry = NULL;

  while(chain != NULL) {
    entry = (struct htable_entry*) chain->data;
    
    if(memcmp(entry->key, key,key_size) == 0) {
      return chain;
    }
    chain = chain->next;
  }
  return NULL;
}

struct htable_entry*
htable_del(struct htable* htable,
           void* key,
           size_t key_size)
{
  unsigned long hash =
    htable->hash_function(key,key_size);
  
  size_t index =  (hash % htable->size);
  
  struct list* elem =
    htable_find_node(htable,index, key,key_size);

  if(elem != NULL ) {
    list_delete(&(htable->elems[index]->chain), elem);    
    return (struct htable_entry*) elem->data;    
  }
  return NULL;  
}

struct htable_entry*
htable_find_entry(struct htable* htable,
                  void* key,
                  size_t key_size)
{
  unsigned long hash =
    htable->hash_function(key,key_size);
  
  size_t index =  (hash % htable->size);

  struct list* chain =
    htable_find_node(htable,index, key,key_size);
  
  if(chain != NULL ) {
    return (struct htable_entry*) chain->data;
  }
  return NULL;
}

void*
htable_find(struct htable* htable,
            void* key,
            size_t key_size)
{
  struct htable_entry* entry =
    htable_find_entry(htable,key,key_size);
  if(entry == NULL)
    return NULL;  
  return entry;
}

void
htable_resize(struct htable* prev_table,
              size_t new_size)
{
  struct htable* t = htable_create(new_size);  
  for(size_t i = 0 ; i < prev_table->size; i++) {
    struct list* chain = prev_table->elems[i]->chain;
    while(chain != NULL) {
      struct htable_entry* e = (struct htable_entry*) chain->data;
      htable_add(t,e->key,e->key_size, e->data,e->data_size);      
      chain = chain->next;      
    }    
  }  
  
  htable_free_entries(prev_table);
  
  prev_table->elems  = t->elems;
  prev_table->size   = t->size;
  prev_table->nelems = t->nelems;
}

void
htable_free_entries(struct htable* htable)
{
  // free old table entries
  for(size_t  i = 0 ; i < htable->size; i++) {
    list_free(&htable->elems[i]->chain);
    free(htable->elems[i]);
  }
}

void
htable_free(struct htable* htable)
{
  htable_free_entries(htable);
  free(htable);
}

struct htable*
htable_create(size_t min_size)
{
  struct htable* t =  malloc(sizeof(struct htable));
  t->size  = min_size;
  t->elems = calloc(min_size,sizeof(struct htable_elem));
  
  long n = min_size-1;
  while(n >= 0) {
    t->elems[n] = malloc(sizeof(struct htable_elem));
    t->elems[n]->chain = NULL;
    n--;
  }
  
  t->hash_function = sdmb_str_hash;
  t->load_factor = .75;  
  return t;
}

#endif
