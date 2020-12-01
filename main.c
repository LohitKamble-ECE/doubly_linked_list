#include <stdio.h>

#include "list.h"

void print_char(const void *);
int compare_char(const void *, const void *);

int main(void) {
  list *p = NULL;
  p = construct(p, compare_char, print_char);
  char d = 'p';
  push_descending(p, &d, sizeof(char));
  d = 'q';
  push_descending(p, &d, sizeof(char));
  d = 'r';
  push_descending(p, &d, sizeof(char));
  d = 's';
  push_descending(p, &d, sizeof(char));
  d = 't';
  push_descending(p, &d, sizeof(char));
  d = 'z';
  push_descending(p, &d, sizeof(char));
  print(p, 'f');
  return 0;
}

void print_char(const void *p) { printf("%c ", *(char *)p); }

int compare_char(const void *a, const void *b) {
  return *(char *)a - *(char *)b;
}
