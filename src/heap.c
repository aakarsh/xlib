#include "heap.h"

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#define min(X,Y) (((X) < (Y)) ? (X) : (Y))
#define left(index) (index << 1)
#define right(index) ((index<<1) +1)

static inline
void
swap(struct heap* heap,
     size_t u, size_t v);

int
heap_int_cmp(void* k1,
             void* k2,
             size_t n)
{
  const int* s1 = (const int*) k1;
  const int* s2 = (const int*) k2;  
  return ( *s1 - *s2);
}

int
heap_str_cmp(void* k1,
             void* k2,
             size_t n)
{
  const char* s1 = (const char*) k1;
  const char* s2 = (const char*) k2;  
  return strncmp(s1, s2, n); 
}

struct heap*
heap_create(int capacity,
          int (*cmp)(void* k1, void* k2, size_t n))
{
  struct heap* heap =
    malloc(sizeof(struct heap));

  capacity +=1; // skip using element 0 for index computations

  struct heap_element** elements =
    calloc(capacity, sizeof(struct heap_element*));

  heap->elements = elements;
  heap->capacity = capacity;
  heap->size = 1;
  heap->type = HEAP_MAX;
  heap->cmp = cmp;

  return heap;
}

void
heap_insert(struct heap* heap,
            void* key,
            size_t key_size,
            void* data,
            size_t data_size)
{
  if( heap->size > heap->capacity ) {
    perror("heap_insert");
    exit(1);
  }

  int cur = heap->size;

  struct heap_element* element =
    malloc(sizeof(struct heap_element));

  *(heap->elements + cur) = element;

  element->data.mem = malloc(data_size);
  memcpy(element->data.mem, data,data_size);
  element->data.size  = data_size;

  element->key.mem = malloc(key_size);
  memcpy(element->key.mem, key,key_size);
  element->key.size  = key_size;
  
  // increment size
  heap->size++;
}

int
heap_pick_larger(struct heap* heap,
                 int i, int j)
{
  if(i >= heap->size)
    return j;

  if(j >= heap->size)
    return i;

  
  struct heap_element* x = heap_elem(heap, i);
  struct heap_element* y = heap_elem(heap, j);

  struct heap_ptr x_key = x->key;
  struct heap_ptr y_key = y->key;
  
  return (heap->type * heap->cmp(x_key.mem, y_key.mem,
                                 min(x_key.size,y_key.size))) >= 0 ? i : j;
}

/**
 * struct heap_element*
 * heap_larger(element );
 */
void
heap_heapify(struct heap* heap, size_t i)
{
  if(i > heap->size)
    return;
  
  int larger = i;

  larger = heap_pick_larger(heap, larger, left(i));
  larger = heap_pick_larger(heap, larger, right(i));

  // if i has has children smaller promote the largest
  // element and swap.
  if(larger != i && larger < heap->size) {
    swap(heap,larger,i);
    heap_heapify(heap, larger);
  }
}

void
heap_build(struct heap* heap)
{
  int i = round(heap->size/2);
  while(i > 0)
    heap_heapify(heap,i--);
}

static inline
void
swap(struct heap* heap,
     size_t u, size_t v)
{
  struct heap_element* tmp   = *(heap->elements + u);
  *(heap->elements+u) = *(heap->elements + v);
  *(heap->elements+v) = tmp;
}

/**
 * Returns elements of heap in sorted order
 * heap is emptied.
 */
struct heap_element**
heap_sort(struct heap* heap, int *n)
{
  *n = (heap->size-1);
  heap_build(heap);

  for (int i = heap->size - 1; i >= 1; i-- ) {
    swap(heap, 1, --heap->size);  
    heap_heapify(heap,1);
  }
  
  return (heap->elements+1); // first element is ignored
}
