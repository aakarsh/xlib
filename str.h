#ifndef STR_H
#define STR_H

char*
trim_char(char* line,
          char c);

char*
trim_char(char* line,
          char c)
{
  int len = strlen(line)-1;
  while(len >= 0 && line[len] == c)
    line[len--] = '\0';
  return line;
}

#endif
