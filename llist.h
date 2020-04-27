// Created by Eric.
//

#ifndef MULTICORE_LLIST_H
#define MULTICORE_LLIST_H

#include <stdio.h>
#include <stdlib.h>

#define CAS(ptr,old_val,new_val) \
    (__sync_bool_compare_and_swap(ptr, old_val, new_val))

typedef struct node node;
typedef struct list list;

struct node {
    int val;
    node *next;
};

struct list {
    node *head;
    node *tail;
};

int is_marked(const long i);
long unset_mark(long i);
long set_mark(long i);
long get_unmarked(long w);
long get_marked(long w);

list* list_new(list *l);
int list_insert(list *l, int val);
int list_delete(list *l, int val);
int list_find(list *l, int val);
node* list_search(list *l, int val, node **left_node);
void list_print(list *l);

#endif //MULTICORE_LLIST_H
