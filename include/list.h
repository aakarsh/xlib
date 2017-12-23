#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list {
  void* data;
  size_t size;
  struct list* next;
  struct list* prev;
};

struct list*
list_node(void* data,
          size_t sz);

struct list*
list_prepend(struct list* new_head,
             struct list* head);

struct list*
list_reverse(struct list* head);

struct list*
list_unlink(struct list** head,
            struct list* node);

void list_delete(struct list** head,
                 struct list* node);

void list_free(struct list** head_ptr);

void
print_list(struct list* tokens,
           FILE* stream);

#endif
