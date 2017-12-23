#ifndef PARSERS_H
#define PARSERS_H

#include "list.h"


struct list* parse_line(char* line,
                        char* delim);

struct list*
parse_line(char* line,  char* delim)
{  
  struct list* head = NULL;

  char* part = strtok(line, ":");
  do {
    size_t sz = strlen(part)+1;
    head = list_prepend(list_node(part, sz),head);    
  } while((part = strtok(NULL, ":" )) != NULL);

  return list_reverse(head); // correct order
}

#endif
