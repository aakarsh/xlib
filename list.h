#ifndef LIST_H
#define LIST_H

struct list {
  void* data;
  ssize_t size;
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

/**
 * Creates new list node.
 */
struct list*
list_node(void* data,
          size_t sz)
{
  struct list* new_head =
    calloc(1,sizeof(struct list));
  
  new_head->data =  malloc(sz);
  new_head->size = sz;
  
  memcpy(new_head->data,data,sz);
  
  new_head->next = NULL;
  new_head->prev = NULL;
  return new_head;
}

/**
 * Push new head to head of list.
 */
struct list*
list_prepend(struct list* new_head,
             struct list* head)
{
  if(head != NULL) {
    new_head->next = head;
    head->prev     = new_head;
  }
  return new_head;
}

/**
 * Reverse the list in-place.
 */
struct list*
list_reverse(struct list* head)
{  
  struct  list* prev = NULL;
  struct  list* cur = head;

  while ( cur != NULL ) {
    
    struct list* saved_next = cur->next;
    struct list* new_next   = cur->prev;

    cur->next = new_next;
    cur->prev = saved_next;
    
    prev = cur;
    cur = saved_next;    
  }  
  return prev;
}


struct list*
list_unlink(struct list** head,
            struct list* node)
{
  struct list* prev = node->prev;
  struct list* next = node->next;

  if(prev != NULL) {
    prev->next = next;
  }
  
  if(next !=NULL) {
    next->prev  = prev;
  }
  
  node->next = NULL;
  node->prev = NULL;
  
  if(*head == node) {
    *head = NULL;
  }
  
  return node;
}

void
list_delete(struct list** head,
                 struct list* node)
{
  struct list* unlinked  = list_unlink(head,node);
  if(unlinked) {
    free(unlinked->data);
    free(node);
  }
}

void
list_free(struct list** head_ptr)
{
  struct list* cur =  *head_ptr ;
  while(cur != NULL) {
    struct list* next = cur->next;
    list_delete(head_ptr,cur);
    cur = next;
  }
  *head_ptr = NULL;
}


void
print_list(struct list* tokens,
           FILE* stream)
{
  bool first = true;
  for(struct list* token = tokens;
      token != NULL; token = token->next)
    {
    if(!first)
      printf(",");
    fprintf(stream,"%s",token->data);

    first = false;
    }
  printf("\n");
}

#endif
