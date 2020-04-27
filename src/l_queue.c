#include "l_queue.h"
#include <string.h>

node* node_new(int val) {
    node *new_node = (node*) malloc(sizeof(node));
    if (new_node == NULL) {
#ifdef DEBUG
        printf("node_new(%d) failed\n", val);
#endif
        return NULL;
    }
    new_node->next = NULL;
    new_node->val = val;
    return new_node;
}


queue* queue_new() {
    queue* q = (queue*) malloc(sizeof(queue));
    q->head = node_new(-1);
    q->tail = q->head;
    omp_init(q->lock);
    return q;
}

void queue_delete(queue* q) {
    omp_destroy(q->lock);
    free(q);
    return;
}

size_t queue_size(queue *q) {
    if (q == NULL) {
#ifdef DEBUG
        printf("queue is null.\n");
#endif
        exit(1);
    }

    omp_on(q->lock);
    size_t size = q->size;
    omp_off(q->lock);
    return size;
}


void queue_push(queue *q, int val) {
    omp_on(q->lock);

    node* new_node = node_new(val);
    q->tail->next = new_node;
    q->tail = new_node;
    q->size++;

    omp_off(q->lock);
    return;
}


int queue_peek(queue* q) {
    omp_on(q->lock);

    if (q->head->next == NULL) {
        omp_off(q->lock);
#ifdef DEBUG
        printf("queue size is 0.\n");
#endif
        return -1;
    }

    int res = q->head->next->val;
    omp_off(q->lock);
    return res;
}


int queue_pop(queue *q) {
    omp_on(q->lock);

    if (q->head->next == NULL) {
        omp_off(q->lock);
#ifdef DEBUG
        printf("queue size is 0.\n");
#endif
        return -1;
    }

    node *pred = q->head;
    node *curr = pred->next;
    if (curr == NULL) { /* queue is empty */
#ifdef DEBUG
        printf("queue is empty\n");
#endif
        return -1;
    }  else {
        pred->next = curr->next;
        curr->next = NULL;
        if (q->head->next == NULL) {
            q->tail = q->head;
        }
    }

    int res = curr->val;
    free(curr); /* free obsolete node */

    omp_off(q->lock);
    return res;
}

/* debuggin API */
void queue_print(queue *q, int num_ops) {
    char *msg = (char*) calloc(num_ops * 5, sizeof(char));
    sprintf(msg, "[");
    node *curr = q->head->next;
    while (curr != NULL) {
        char buffer[5];
        sprintf(buffer, "%d,", curr->val);
        strcat(msg, buffer);
        curr = curr->next;
    }
    printf("-> %s]\n", msg);
}




