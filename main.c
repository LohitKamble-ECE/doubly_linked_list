#include <stdio.h>

#include "list.h"

void print_char(const void *);
int compare_char(const void *, const void *);

int main(void) {
  list *p = NULL;
  p = construct(p, compare_char, print_char);
  char d = 'a';
  insert_after(p, NULL, &d, sizeof(int));
  d++;
  insert_after(p, NULL, &d, sizeof(int));
  d++;
  insert_after(p, NULL, &d, sizeof(int));
  d++;
  insert_after(p, NULL, &d, sizeof(int));
  d++;
  insert_after(p, NULL, &d, sizeof(int));
  d++;
  insert_after(p, NULL, &d, sizeof(int));
  print(p, 'f');
  print(p, 'r');
  delete_all(p);
  print(p, 'f');
  destruct(p);
  return 0;
}

void print_char(const void *p) { printf("%c ", *(char *)p); }

int compare_char(const void *a, const void *b) {
  return *(char *)a - *(char *)b;
}
