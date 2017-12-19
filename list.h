struct list {
  void* data;
  ssize_t size;
  struct list* next;
  struct list* prev;
};

struct list* list_node(void* data, size_t sz);
struct list* list_prepend(struct list* new_head, struct list* head);
struct list* list_reverse(struct list* head);

struct list* list_node(void* data, size_t sz)
{
  struct list* new_head =  malloc(sizeof(struct list));
  new_head->data =  malloc(sz);
  memcpy(new_head->data,data,sz);
  new_head->next = NULL;
  new_head->prev = NULL;
  return new_head;
}

struct list* list_prepend(struct list* new_head, struct list* head)
{
  if(head != NULL) {
    new_head->next = head;  
    head->prev = new_head;
  }
  return new_head;
}

struct list* list_reverse(struct list* head)
{
  struct  list* next = head->next;
  while(next != NULL) {
    
    struct list* save_next = next->next;
    next->next = next->prev;
    
    if(next->prev != NULL) {
      (next->prev)->prev = next;
    }
    
  }
}

