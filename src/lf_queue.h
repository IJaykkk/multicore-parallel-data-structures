#ifndef MULTICORE_LF_QUEUE_H
#define MULTICORE_LF_QUEUE_H

#define CAS(old_ptr,old_val,new_val) \
    (__sync_bool_compare_and_swap(old_ptr, old_val, new_val))
#define ANF(ptr) (__sync_add_and_fetch(ptr, 1))
#define SNF(ptr) (__sync_sub_and_fetch(ptr, 1))

typedef struct node node;
typedef struct queue queue;

struct node{
    void *val;
    node *next;
};

struct queue{
    node *head;
    node *tail;
    int count;
};

int queue_new(queue *q);
int queue_delete(queue *q);
int queue_push(queue *q, void *val);
void* queue_pop(queue *q);
void queue_print(queue *q, int num_ops);

#endif //MULTICORE_LF_QUEUE_H
