#include "lf_list.h"
#include "limits.h"
#include "string.h"

int is_marked(long i) {
    return (int) (i & 0x1L);
}

long get_unmarked(const long w) {
    return w & ~0x1L;
}

long get_marked(const long w) {
    return w | 0x1L;
}


list* list_new(list *l) {
    node* head = (node*) malloc(sizeof(node));
    head->next = NULL;
    head->val = INT_MIN;

    node* tail = (node*) malloc(sizeof(node));
    tail->next = NULL;
    tail->val = INT_MAX;

    l->head = head;
    l->head->next = tail;
    l->tail = tail;
    return l;
}


int list_insert(list *l, int val) {
    node *right_node, *left_node;
    right_node = left_node = NULL;
    node *new_node = (node*) malloc(sizeof(node));
    new_node->next = NULL;
    new_node->val = val;
    while(1) {
        right_node = list_search(l, val, &left_node);
        if ((right_node != l->tail) && (right_node->val == val)) {
            return 0;
        }
        new_node->next = right_node;
        if (CAS(&(left_node->next), right_node, new_node)) {
            return 1; }
    }
}


int list_delete(list *l, int val) {
    node *right_node, *right_node_next, *left_node;
    right_node = right_node_next = left_node = NULL;
    while (1) {
        right_node = list_search(l, val, &left_node);
        if ((right_node == l->tail) || (right_node->val != val)) {
            return -1;
        }
        right_node_next = right_node->next;
        if (!is_marked((long) right_node_next))
            if (CAS(&(right_node->next), right_node_next,
                get_marked((long) right_node_next)))
                break;
    }
    if (!CAS(&(left_node->next), right_node, right_node_next)) {
        right_node = list_search(l, right_node->val, &left_node);
    }
    return val;
}


int list_find(list *l, int val) {
    node *right_node, *left_node;
    right_node = list_search(l, val, &left_node);
    if ((right_node == l->tail) || (right_node->val != val)) {
        return 0;
    } else {
        return 1;
    }
}


node* list_search(list *l, int val, node **left_node) {
    node *left_node_next, *right_node;
    left_node_next = right_node = NULL;
    while(1) {
        node *t = l->head;
        node *t_next = l->head->next;
        /* Find left_node and right_node */
        while (is_marked((long) t_next) || (t->val < val)) {
            if (!is_marked((long) t_next)) { // valid
                (*left_node) = t;
                left_node_next = t_next;
            }
            t = (node*) get_unmarked((long) t_next);
            if (t == l->tail) break;
            t_next = t->next;
        }
        right_node = t;

        /* Check nodes are adjacent */
        if (left_node_next == right_node){
            if (!is_marked((long) right_node->next))
                return right_node;
        }

        /* Remove one or more marked nodes */
        if (CAS(&((*left_node)->next), left_node_next, right_node)) {
            if ((right_node == l->tail) && !is_marked((long) right_node->next))
                return right_node;
        }
    }
}


/* debuggin API */
void list_print(list *l, int num_ops) {
    char *msg = (char*) calloc(num_ops * 5, sizeof(char));
    sprintf(msg, "[");
    node *curr = l->head->next;
    while (curr != NULL && curr->val != INT_MAX) {
        char buffer[5];
        sprintf(buffer, "%d,", curr->val);
        strcat(msg, buffer);
        curr = curr->next;
    }
    printf("-> %s]\n", msg);
}
