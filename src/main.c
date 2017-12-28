#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#include "list.h"
#include "htable.h"
#include "rb_tree.h" 
#include "parse.h"
#include "str.h"
#include "heap.h"

#define LINE_SIZE 1024

int
main(int argc, char* argv[])
{
  char* fname = "/etc/passwd";
  FILE* file  = fopen(fname, "r");
  
  if(!file) {
    fprintf(stderr, "failed fopen: %s\n",fname);
    perror(NULL);
    return -1;      
  }
  
  size_t size = LINE_SIZE;
  char* line = malloc(size);
  int num = 0;

  struct htable* table = htable_create(1<<10);

  struct heap* h = heap_create(100,heap_str_cmp);
  
  while((getline(&line,&size,file))!= -1) {
    
    char* trim_line = trim_char(line,'\n');
    heap_insert(h, trim_line, size, line, size);
    
    struct list* tokens = parse_line(trim_line,":");
    
    htable_add(table,        // allow new table
               tokens->data, // key
               tokens->size, // size
               tokens,       // pointer-to-tokens
               sizeof(struct list*));
    

    
    print_list(tokens,stdout);
    num++;
  }

  printf("---------------------------------------------------\n");
  char* key = "sshd";
  struct list* tokens = htable_find(table,key,strlen(key)+1);
  print_list(tokens,stdout);
  printf("---------------------------------------------------\n");
  
  int i;
  struct heap_element** elements = heap_sort(h,&i);
  while( i > 0) {
    struct heap_element* e = *(elements+i);
    printf("%3d: %s\n", i,(char*) e->data.mem);
    i--; 
  }
  
  return 0;
}
