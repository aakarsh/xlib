#include "heap.h"

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <math.h>

#define min(X,Y) (((X) < (Y)) ? (X) : (Y))


static int inline
left(int index)
{
  return index << 1;
}

static int inline
right(int index)
{
  return (index << 1) + 1;
}

void
swap(struct heap* heap,
     size_t u, size_t v);

struct heap*
heap_init(int capacity,
          int (*cmp)(void* k1, void* k2, size_t n))
{
  struct heap* heap =
    malloc(sizeof(struct heap));

  struct heap_element* elements =
    calloc(capacity, sizeof(struct heap_element));

  heap->elements = &elements;
  heap->capacity = capacity;
  heap->size = 0;
  heap->type = HEAP_MIN;
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
  if(heap->size > heap->capacity) {
    perror("heap_insert");
    exit(1);
  }

  int cur = heap->size;

  struct heap_element* element =
    *(heap->elements + cur);

  element->data = (struct heap_ptr) { .mem = data, .size = data_size};
  element->key  = (struct heap_ptr) { .mem = key , .size = key_size };

  // increment size
  heap->size++;
}

int
heap_pick_larger(struct heap* heap,
                 int i,
                 int j)
{
  if(i > heap->size)
    return j;

  if(j > heap->size)
    return i;

  struct heap_element* x = *(heap->elements + i);
  struct heap_element* y = *(heap->elements + j);

  struct heap_ptr x_key = x->key;
  struct heap_ptr y_key = y->key;

  if(heap->cmp( x_key.mem,
                y_key.mem,
                min(x_key.size,y_key.size)) > 0) {
    return i;
  } else {
    return j;
  }
}

/**
 * struct heap_element*
 * heap_larger(element );
 */
void
heap_heapify(struct heap* heap, size_t i)
{
  int larger = i;
  
  larger = heap_pick_larger(heap,larger,left(i));
  larger = heap_pick_larger(heap,larger,right(i));
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

void
swap(struct heap* heap,
     size_t u, size_t v)
{
  struct heap_element* tmp   = *(heap->elements + u);
  *(heap->elements+u) = *(heap->elements + v); 
  *(heap->elements+v) = tmp; 
}
