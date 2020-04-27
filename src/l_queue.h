#ifndef MULTICORE_L_QUEUE_H
#define MULTICORE_L_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define omp_on(lock) (omp_set_lock(&lock))
#define omp_off(lock) (omp_unset_lock(&lock))
#define omp_init(lock) (omp_init_lock(&lock))
#define omp_destroy(lock) (omp_destroy_lock(&lock))

typedef struct node node;

struct node {
    int val;
    node *next;
};


typedef struct queue {
    node *head;        /* sentinel */
    node *tail;        /* latest data */
    size_t size;       /* current size */
    omp_lock_t lock;   /* lock */
} queue;


node* node_new(int val);
queue* queue_new();
void queue_delete(queue *q);
size_t queue_size(queue *q);
void queue_push(queue *q, int val);
int queue_peek(queue *q);
int queue_pop(queue *q);
void queue_print(queue *q, int num_threads);

#endif //MULTICORE_L_QUEUE_H

