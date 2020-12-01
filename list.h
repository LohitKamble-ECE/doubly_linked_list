#ifndef LIST_H
#define LIST_H

#include <stddef.h>  // size_t

typedef struct node {
  void *data;
  struct node *prev;
  struct node *succ;
} node;

typedef struct list {
  node *beg;
  node *end;
  size_t size;
  int (*compare)(const void *, const void *);
  void (*print)(const void *);
} list;

extern list *construct(list *this_list,
                       int (*compare)(const void *, const void *b),
                       void (*print)(const void *));
extern list *destruct(list *this_list);
extern void print(list *this_list, const char flag);
extern int insert_before(list *this_list, node *this_node, void *data,
                         size_t size);
extern int insert_after(list *this_list, node *this_node, void *data,
                        size_t size);
extern int delete_current(list *this_list, node *this_node);
extern int delete_all(list *this_list);
extern int reverse(list *this_list);
extern node *node_at_index(list *this_list, size_t index);
extern node *find_key(list *this_list, void *data);
extern node *get_prev(list *this_list, node *this_node);
extern node *get_succ(list *this_list, node *this_node);
extern size_t get_size(list *this_list);
extern void *get_data(node *this_node);
extern node *get_begin(list *this_list);
extern node *get_end(list *this_list);
#endif
