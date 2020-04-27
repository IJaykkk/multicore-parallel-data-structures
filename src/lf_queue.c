#include "lf_queue.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <errno.h>

int queue_new(queue *q) {
    // sentinel
    node *new_node = calloc(1, sizeof(node));
    if (!new_node)  {
        return -errno;
    }

    memset(q, 0, sizeof(queue));
    q->head = q->tail = new_node;

    return 0;
}


int queue_delete(queue *q){
    if (q->tail && q->head) {
        node *curr = q->head;
        node *tmp;

        // iterate through nodes
        while (curr != q->tail) {
            tmp = curr->next;
            free(curr);
            curr = tmp;
        }

        free(q->head);
        memset(q, 0, sizeof(queue));
    }

    return 0;
}


int queue_push(queue *q, void *val) {
    node *tail;
    node *new_node = calloc(1, sizeof(node));
    if (!new_node) {
        return -errno;
    }

    new_node->val = val;
    do {
        tail = q->tail;
        if ( CAS(&q->tail, tail, new_node)) {
            tail->next = new_node;
            break;  
        }
    } while (1);
    ANF(&q->count);

    return 0;
}


void* queue_pop(queue *q) {
    void *val = 0;
    node *head;

    /* A little spinlock.
     * Try to contend for q->head.
     * After getting it, assign it to zero,
     * thid thread prevents other threads from getting it */
    do {
        head = q->head;
    } while (head == 0 || !CAS(&q->head, head, 0));

    // queue is empty
    if (head->next == 0) {
        q->head = head;
        return 0;
    }
    val = head->next->val;
    q->head = head->next;

    SNF(&q->count);
    free(head);

    return val;
}

/* debuggin API */
void queue_print(queue *q, int num_ops) {
    char *msg = (char*) calloc(num_ops * 5, sizeof(char));
    sprintf(msg, "[");
    node *curr = q->head->next;
    while (curr != NULL) {
        char buffer[5];
        sprintf(buffer, "%ld,", (long) curr->val);
        strcat(msg, buffer);
        curr = curr->next;
    }
    printf("-> %s]\n", msg);
}
