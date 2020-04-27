#ifndef MULTICORE_L_LIST_H
#define MULTICORE_L_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define omp_on(lock) (omp_set_lock(&lock))
#define omp_off(lock) (omp_unset_lock(&lock))
#define omp_init(lock) (omp_init_lock(&lock))
#define omp_destroy(lock) (omp_destroy_lock(&lock))

typedef struct node node;
typedef struct list list;

struct node {
    int val;
    node *next;
};


typedef struct list {
    node *head;        /* sentinel */
    size_t size;       /* current size */
    omp_lock_t lock;   /* lock */
} queue;


node* node_new(int val);
list* list_new(list *l);
void list_insert(list *l, int val);
int list_delete(list *l, int val);
int list_find(list *l, int val);
size_t list_size(list *l);
void list_print(list *l, int num_ops);

#endif //MULTICORE_L_LIST_H
