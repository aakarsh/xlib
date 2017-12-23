#ifndef HTABLE_H
#define HTABLE_H

#include <string.h>
#include <assert.h>
#include "list.h"

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
  
  unsigned long (*hash_function)(void* key,
                                 size_t nbytes);
  
};

struct htable*
htable_create(size_t min_size);

void
htable_add(struct htable* htable,
           void* key,
           size_t key_size,
           void* data,
           size_t data_size);

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

#endif
