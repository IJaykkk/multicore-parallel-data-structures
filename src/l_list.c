#include "l_list.h"

#include <string.h>
#include <omp.h>

node* node_new(int val) {
    node *new_node = (node*) malloc(sizeof(node));
    if (new_node == NULL) {
#ifdef DEBUG
        printf("node_new(%d)\n", val);
#endif
        return NULL;
    }
    new_node->next = NULL;
    new_node->val = val;
    return new_node;
}


list* list_new(list *l) {
    l->head = node_new(-1);
    l->size = 0;
    omp_init(l->lock);
    return l;
}


void list_insert(list *l, int val) {
    omp_on(l->lock);

    node *new_node = node_new(val);
    node *pred = l->head;
    node *curr = l->head->next;
    while (curr != NULL && curr->val < val) {
        pred = curr;
        curr = curr->next;
    }
    if (curr == NULL || curr->val != val) {
        pred->next = new_node;
        new_node->next = curr;
        l->size += 1;
    }

    omp_off(l->lock);
    return;
}

int list_delete(list *l, int val) {
    omp_on(l->lock);

    int res = -1;
    node *pred = l->head;
    node *curr = l->head->next;
    while (curr != NULL && curr->val < val) {
        pred = curr;
        curr = curr->next;
    }
    if (curr != NULL && curr->val == val) {
        pred->next = curr->next;
        res = curr->val;
        free(curr);
        l->size -= 1;
    }

    omp_off(l->lock);
    return res;
}


int list_find(list *l, int val) {
    omp_on(l->lock);

    int res = 0;
    node *curr = l->head->next;
    while (curr != NULL && curr->val < val) {
        curr = curr->next;
    }
    if (curr != NULL && curr->val == val) {
        res = 1;
    }

    omp_off(l->lock);
    return res;
}


/* debuggin API */
void list_print(list *l, int num_ops) {
    char *msg = (char*) calloc(num_ops * 5, sizeof(char));
    sprintf(msg, "[");
    node *curr = l->head->next;
    while (curr != NULL) {
        char buffer[5];
        sprintf(buffer, "%d,", curr->val);
        strcat(msg, buffer);
        curr = curr->next;
    }
    printf("-> %s]\n", msg);
}
