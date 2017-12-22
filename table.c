#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "list.h"
#include "htable.h"

#define LINE_SIZE 1024

char* trim_char(char* line,char c);
void print_list(struct list* tokens, FILE* stream);
struct list* parse_line(char* line, char* delim);

int
main(int argc, char* argv[])
{
  char* fname = "/etc/passwd";
  FILE* fs = fopen(fname, "r");

  if(!fs) {
    fprintf(stderr, "failed fopen: %s\n",fname);
    perror(NULL);
    return -1;      
  }

  char* line = malloc(LINE_SIZE);
  size_t size = LINE_SIZE;
  int num = 0;

  struct list* lines = malloc(sizeof(struct list));
  struct htable* table = htable_create(1<<10);

  while((getline(&line,&size,fs))!= -1) {
    struct list* tokens =
      parse_line(trim_char(line,'\n'),":");
    htable_add(table,       // allow new table
               tokens->data, // key
               tokens->size, // size
               tokens,       // pointer-to-tokens
               sizeof(struct list*));
    print_list(tokens,stdout);
    num++;
  }

  printf("---------------------------------------------------\n");
  char* key = "sshd";
  struct list* tokens =  htable_find(table,key,strlen(key)+1);
  print_list(tokens,stdout);
  printf("---------------------------------------------------\n");
  return 0;
}

char*
trim_char(char* line,char c) {
  int len = strlen(line)-1;
  while(len > 0 && line[len] == c)  line[len--] = '\0';
  return line;
}

void
print_list(struct list* tokens, FILE* stream)
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

struct list*
parse_line(char* line,  char* delim)
{
  int first = true;
  struct list* head = NULL;

  char* part = strtok(line, ":");
  do {
    size_t sz = strlen(part)+1;
    head = list_prepend(list_node(part, sz),head);

  } while((part = strtok(NULL, ":" )) != NULL);

  return list_reverse(head); // correct order
}
