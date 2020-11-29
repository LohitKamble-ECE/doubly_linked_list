/**
 * Doubley Linked-List Implementation
 *
 * Author: Lohit Kamble
 * Date  : Nov 30 2020
 * Time  : 03:26
 * System: Ubuntu 20.10
 */

#include "list.h"  // user list interface

#include <stdbool.h>  // bool data type
#include <stddef.h>   // size_t data type
#include <stdio.h>    // basic input and output functions
#include <stdlib.h>   // malloc() and free()
#include <string.h>   // stderr()

#include "error_handler.h"  // error handler macros

/**
 * Construct the list so that it is avialable to perform operation on it.
 * a. If list pointer is pointing to previously allocated list then it prompts
 *    the appropriate error message and will not allocate the new memory for
 *    the list again causing it memroy leak.
 * b. Return the address of memory of newly allocated list on success or the
 *    same as passed list pointer otherwise.
 */
list *construct(list *this_list, int (*compare)(const void *, const void *),
                void (*print)(const void *)) {
  if (!this_list) {
    if ((this_list = (list *)malloc(sizeof(list)))) {
      this_list->beg = NULL;
      this_list->end = NULL;
      this_list->size = 0;
      this_list->compare = compare;
      this_list->print = print;
    } else {
      print_fatal_error("memory is not allocated for list...");
    }
  } else {
    print_only_error("list is already constructed...");
    print_error_continue(
        "constructing it once again does not make any sense...");
  }
  return this_list;
}

/**
 * Print the list in desired direction.
 * Use 'f' or 'F' to print in forward direction.
 * Use 'r' or 'R' to print in reverse direction.
 */
void print(list *this_list, const char flag) {
  if (this_list) {
    if (this_list->beg) {
      node *trav = NULL;
      switch (flag) {
        case 'f':
        case 'F':
          trav = this_list->beg;
          while (trav) {
            this_list->print(trav->data);
            trav = trav->succ;
          }
          break;
        case 'r':
        case 'R':
          trav = this_list->end;
          while (trav) {
            this_list->print(trav->data);
            trav = trav->prev;
          }
          break;
        default:
          print_fatal_error("unacceptable flag...");
          print_error_continue(
              "try passing 'f' to print list in forward direction...");
          print_error_continue(
              "try passing 'r' to print list in reverse direction...");
          print_error_continue(
              "the correspoinding uppercase equivalent is also acceptable for "
              "the above character..");
          break;
      }
      printf("\n");
    } else {
      printf("list is empty...\n");
    }
  } else {
    construct_list_error(
        "tring to print the content of it does not make any sense...");
  }
}

/**
 * Allocated and initialize the new node.
 * Return its address if memory is allocated successfully or NULL otherwise.
 */
static node *allocate_node(void *data, size_t size, node *succ, node *prev) {
  node *new_node = NULL;
  if ((new_node = (node *)malloc(sizeof(node)))) {
    if ((new_node->data = (void *)malloc(size))) {
      memmove(new_node->data, data, size);
      new_node->succ = succ;
      new_node->prev = prev;
    } else {
      print_fatal_error(
          "memory is not allocated for the data part of the node...");
      // Avoiding possible memory leak.
      free(new_node);
      new_node = NULL;
    }
  } else {
    print_fatal_error("memory is not allocated for the new node...");
  }
  return new_node;
}

/**
 * Check wether the node present in the list or not.
 * If it present then return true or false otherwise.
 */
static bool is_node_present_in_list(list *this_list, node *this_node) {
  if (this_list) {
    node *trav = this_list->beg;
    while (trav) {
      if (trav == this_node) {
        return true;
      }
      trav = trav->succ;
    }
  } else {
    construct_list_error(
        "tring to insert new node into it does not make any sense...");
  }
  return false;
}

/**
 * Insert the new node before the specified node in the list assuming list is
 * previously constructed. If the specified node is not in the list then no
 * operation will perform on it and will return the error code -1. If the
 * specified node is NULL or the list does not contain any node at all then new
 * node is inserted at the beginning of the list.
 */
int insert_before(list *this_list, node *this_node, void *data, size_t size) {
  if (this_list) {
    if (!this_list->beg) {
      // List does not content a single node.
      // Inserting its first node.
      node *new_node = NULL;
      if ((new_node = allocate_node(data, size, NULL, NULL))) {
        this_list->beg = new_node;
        this_list->end = new_node;
        ++this_list->size;
        return 0;
      }
    } else {
      if (this_node && this_node != this_list->beg) {
        // Inserting new node before the specified node.
        if (is_node_present_in_list(this_list, this_node)) {
          node *new_node = NULL;
          if ((new_node =
                   allocate_node(data, size, this_node, this_node->prev))) {
            this_node->prev->succ = new_node;
            this_node->prev = new_node;
            if (this_node == this_list->beg) {
              this_list->beg = new_node;
            }
            ++this_list->size;
            return 0;
          }
        } else {
          print_logical_error(
              "the passed node before which new node is to be inserted is not "
              "present in the list...");
        }
      } else {
        // Inserting new node at the beginning of the list.
        node *new_node = NULL;
        if ((new_node = allocate_node(data, size, this_list->beg, NULL))) {
          this_list->beg->prev = new_node;
          this_list->beg = new_node;
          ++this_list->size;
          return 0;
        }
      }
    }
  } else {
    construct_list_error(
        "tring to insert node into it does not make any sense...");
  }
  return -1;
}

/**
 * Return the address of the node at particular index.
 * If there no node present at particular index prompts the appropriate message
 * and return NULL indicating error.
 */
node *node_at_index(list *this_list, size_t index) {
  if (this_list) {
    if (this_list->beg) {
      node *trav = this_list->beg;
      for (size_t i = 0; i < index; ++i) {
        if (!trav) {
          print_logical_error("there is no node present at given index...");
          return NULL;
        }
        trav = trav->succ;
      }
      return trav;
    } else {
      print_logical_error("list is empty...");
    }
  } else {
    construct_list_error(
        "tring to access node at particular index does not make any "
        "sense...");
  }
  return NULL;
}

/**
 * Return the pointer to previous node pointed by the specified node.
 * Well doing so in this way is actually an overhead but it is safe as there is
 * checking of whether the node is present in the list or not and act
 * accordingly. I recommended it.
 */
node *get_prev(list *this_list, node *this_node) {
  if (this_list) {
    if (this_list->beg) {
      if (is_node_present_in_list(this_list, this_node)) {
        return this_node->prev;
      }
    } else {
      print_logical_error("list is empty...");
    }

  } else {
    construct_list_error(
        "trying to get prev member of particular node does not make any "
        "sense...");
  }
  return NULL;
}

/**
 * Return the pointer to successor node pointed by the specified node.
 * Well doing so in this way is actually an overhead but it is safe as there is
 * checking of whether the node is present in the list or not and act
 * accordingly. I recommended it.
 */
node *get_succ(list *this_list, node *this_node) {
  if (this_list) {
    if (this_list->beg) {
      if (is_node_present_in_list(this_list, this_node)) {
        return this_node->succ;
      }
    } else {
      print_logical_error("list is empty...");
    }
  } else {
    construct_list_error(
        "trying to get succ member of particular node does not make any "
        "sense...");
  }
  return NULL;
}

/**
 * Return the pointer to the data part of the node.
 */
void *get_data(node *this_node) {
  if (this_node) {
    return this_node->data;
  } else {
    print_fatal_error(
        "accessing data part of node which is not allocated previously...");
  }
  return NULL;
}

/**
 * Return the pointer to the first node of the list.
 */
node *get_begin(list *this_list) {
  if (this_list) {
    return this_list->beg;
  } else {
    construct_list_error(
        "trying to get iterator begin does not make any sense...");
  }
  return NULL;
}

/**
 * Return the pointer to the last node of the list.
 */
node *get_end(list *this_list) {
  if (this_list) {
    return this_list->end;
  } else {
    construct_list_error(
        "trying to get iterator end does not make any sense...");
  }
  return NULL;
}

/**
 * Return the address of the node whose data member is equal to the specified
 * data.
 */
node *find_key(list *this_list, void *data) {
  if (this_list) {
    if (this_list->beg) {
      node *trav = this_list->beg;
      while (trav) {
        if (!this_list->compare(trav->data, data)) {
          return trav;
        }
        trav = trav->succ;
      }
    } else {
      print_logical_error("list is empty...");
    }
  } else {
    construct_list_error("trying to find the key does not make any sense...");
  }
  return NULL;
}

/**
 * Insert the new node after the specified node in the list assuming list is
 * previously constructed. If the specified node is not in the list then no
 * operation will perform on it and will return the error code -1. If the
 * specified node is NULL then new node is inserted at the end of the list. And
 * if the list does not contain any node at all then new node is inserted at the
 * beginning of the list.
 */
int insert_after(list *this_list, node *this_node, void *data, size_t size) {
  if (this_list) {
    if (!this_list->beg) {
      // List is emtpy.
      // Inserting its first element.
      node *new_node = NULL;
      if ((new_node = allocate_node(data, size, NULL, NULL))) {
        this_list->beg = new_node;
        this_list->end = new_node;
        ++this_list->size;
        return 0;
      }
    } else if (this_node && this_node != this_list->end) {
      // Inserting after the specified node present in the list.
      if (is_node_present_in_list(this_list, this_node)) {
        node *new_node = NULL;
        if ((new_node =
                 allocate_node(data, size, this_node->succ, this_node))) {
          this_node->succ->prev = new_node;
          this_node->succ = new_node;
          ++this_list->size;
          return 0;
        }
      } else {
        print_fatal_error(
            "the passed node after which new node has to insert is not present "
            "in the list...");
      }
    } else {
      // Inserting at end of the list.
      node *new_node = NULL;
      if ((new_node = allocate_node(data, size, NULL, this_list->end))) {
        this_list->end->succ = new_node;
        this_list->end = new_node;
        ++this_list->size;
        return 0;
      }
    }
  } else {
    construct_list_error(
        "trying to insert node into it does not make any sense...");
  }
  return 0;
}

/**
 * Remove (or deallocated) current specified node from the list if it preset.
 * If the specified node is NULL remove the last node of the list.
 */
int delete_current(list *this_list, node *this_node) {
  if (this_list) {
    if (this_list->beg) {
      if (this_list->beg == this_list->end) {
        // Node to be deleted is the first and last node of the list.
        node *to_be_deleted = this_list->beg;
        this_list->beg = NULL;
        this_list->end = NULL;
        free(to_be_deleted->data);
        free(to_be_deleted);
        to_be_deleted = NULL;
        --this_list->size;
        return 0;
      } else if (this_node == this_list->beg) {
        // Node to be deleted is the first node of the list.
        this_list->beg = this_node->succ;
        this_list->beg->prev = NULL;
        free(this_node->data);
        free(this_node);
        this_node = NULL;
        --this_list->size;
        return 0;
      } else if (this_node == NULL || this_node == this_list->end) {
        // Node to be deleted is the last node of the list.
        node *to_be_deleted = this_list->end;
        this_list->end = to_be_deleted->prev;
        this_list->end->succ = NULL;
        free(to_be_deleted->data);
        free(to_be_deleted);
        to_be_deleted = NULL;
        --this_list->size;
        return 0;
      } else {
        // Node to be deleted is present in between begin and end of the list.
        if (is_node_present_in_list(this_list, this_node)) {
          this_node->prev->succ = this_node->succ;
          this_node->succ->prev = this_node->prev;
          free(this_node->data);
          free(this_node);
          --this_list->size;
          return 0;
        } else {
          print_logical_error(
              "node to be deleted is not present in the list...");
        }
      }
    } else {
      print_logical_error("list is empty...");
    }
  } else {
    construct_list_error(
        "trying to delete node from it does not make any sense...");
  }
  return -1;
}

/**
 * Delete all the node present in the list.
 */
int delete_all(list *this_list) {
  if (this_list) {
    if (this_list->beg) {
      while (this_list->beg) {
        delete_current(this_list, NULL);
      }
      return 0;
    } else {
      print_logical_error("list is empty...");
    }
  } else {
    construct_list_error(
        "trying to delete all node form the list does not make any sense...");
  }
  return -1;
}

/**
 * Deallocate the memory for all the node present in the list and also the list
 * itself.
 * No any operation can perform on the list pointer unless construted again.
 */
list *destruct(list *this_list) {
  if (this_list) {
    if (delete_all(this_list)) {
      free(this_list);
      this_list = NULL;
    }
  } else {
    construct_list_error("trying to destruct it does not make any sense...");
  }
  return this_list;
}

/**
 * Return the size of the list.
 */
size_t get_size(list *this_list) {
  if (this_list) {
    return this_list->size;
  } else {
    construct_list_error(
        "trying to find the size of the list does not make any sense...");
  }
  return 0;
}
