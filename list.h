struct list {
  void* data;
  ssize_t size;
  struct list* next;
  struct list* prev;
};

struct list* list_node(void* data, size_t sz);
struct list* list_prepend(struct list* new_head, struct list* head);
struct list* list_reverse(struct list* head);

struct list*
list_node(void* data, size_t sz)
{
  struct list* new_head =  malloc(sizeof(struct list));
  new_head->data =  malloc(sz);
  memcpy(new_head->data,data,sz);
  new_head->next = NULL;
  new_head->prev = NULL;
  return new_head;
}

/**
 * push new head to head of list.
 */
struct list*
list_prepend(struct list* new_head, struct list* head)
{
  if(head != NULL) {
    new_head->next = head;
    head->prev = new_head;
  }
  return new_head;
}

/**
 * Reverse the list in-place
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
