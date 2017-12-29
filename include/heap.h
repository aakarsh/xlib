#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>
#include <assert.h>

enum heap_type { HEAP_MIN = -1,
                 HEAP_MAX = 1 };

struct heap_ptr {
  void* mem;
  size_t size;
};

struct heap_element {  
  struct heap_ptr key;
  struct heap_ptr data;
};

struct heap {
  struct heap_element** elements;
  long size;
  long capacity;
  enum heap_type type;
  int (*cmp) (void* k1, void* k2, size_t n); 
};


struct heap_element*
heap_elem(struct heap* heap,
          int i)
{
  assert(i < heap->size);
  return *(heap->elements + i);
}

int
heap_int_cmp(void* k1,
             void* k2,
             size_t n);
  
int
heap_str_cmp(void* k1,
             void* k2,
             size_t n);

struct heap*
heap_create(int capacity,
          int (*cmp)(void* k1,void* k2, size_t n));

void
heap_insert(struct heap* heap,
            void* key,
            size_t key_size,
            void* data,
            size_t data_size);

void
heap_build(struct heap* heap);

void*
heap_pop_max(struct heap* heap);

void*
heap_max(struct heap* heap);

/**
* Returns elements of the heap in
* sorted order.
*/
struct heap_element**
heap_sort(struct heap* heap,
          int *n);

#endif
