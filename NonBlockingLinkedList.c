#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>
#include <inttypes.h>
/*
bool __sync_bool_compare_and_swap (type *ptr, type oldval type newval, ...)
type __sync_val_compare_and_swap (type *ptr, type oldval type newval, ...)
These builtins perform an atomic compare and swap. That is, if the current value of *ptr is oldval, then write newval into *ptr.
The bool version returns true if the comparison is successful and newval was written. The val version returns the contents of *ptr before the operation
*/


volatile unsigned long counter = 0;

static pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
// static pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

int CAS( volatile unsigned long* value, unsigned long comp_val, unsigned long new_val ) {
    return __sync_bool_compare_and_swap( value, comp_val, new_val );
}

int cas( uintptr_t* value, uintptr_t comp_val, uintptr_t new_val ) {
    return __sync_bool_compare_and_swap( value, comp_val, new_val );
}


int randomNumber(){
    return((1 + (int)( 20.0 * rand() / ( RAND_MAX + 1.0 ) )));
}


/*Linked list types*/
struct node {
   int key;
   bool mark;
   struct node * next;
};

typedef struct node Node;

// static const bool is_marked_reference(Node * p) {
//     return p->mark;
// }

// static const bool get_unmarked_reference(Node * p) {
//     Node *new_node = malloc(sizeof(Node));
//     new_node->key = p->key;
//     new_node->mark = !p->mark;
//     new_node->next = p->next;

//     __sync_bool_compare_and_swap( *p, p, new_node );
//     return (uintptr_t)new_node;
// }

// static const bool get_marked_reference(Node * p) {
//     Node *new_node = malloc(sizeof(Node));
//     new_node->key = p->key;
//     new_node->mark = !p->mark;
//     new_node->next = p->next;

//     __sync_bool_compare_and_swap( *p, p, new_node );
//     return (uintptr_t)new_node;
// }

static const bool is_marked_reference(const uintptr_t p) {
    printf("is_marked_reference 0x%" PRIXPTR "\n", (uintptr_t)p);
    return p & 0x1;
}

static const uintptr_t get_unmarked_reference(const uintptr_t p) {
    printf("get_unmarked_reference 0x%" PRIXPTR "\n", (uintptr_t)p);
    return p & 0xFFFFFFFE;
}

static const uintptr_t get_marked_reference(const uintptr_t p) {
    printf("get_marked_reference 0x%" PRIXPTR "\n", (uintptr_t)p);
    return p | 0x1;
}


/* Create a linked list */

void Create_Linked_list(Node **head, Node **tail) {
    printf("Create Function\n");
    (*head) = malloc(sizeof(Node));
    (**head).key = 0;
    (*tail) = malloc(sizeof(Node));
    (**tail).key = 100000;
    (*head)->next = (*tail);
}


/* Search - it takes a search key and returns references to two nodes called left node and right node for that key */

static Node *search(Node *head, Node *tail, Node **left_node, int key){
    Node *left_node_next = NULL, *right_node = NULL;
    printf("Search Function\n");

    search_again:
    do{
        Node *t = head;
        Node *t_next = head->next;

        /* 1: Find left_node and right_node*/
        do{
            if(!is_marked_reference((uintptr_t) t_next)) {
            // if(!is_marked_reference(t_next)) {
                (*left_node) = t;
                left_node_next = t_next;
            }

            t = (Node*) get_unmarked_reference((uintptr_t) t->next);
            // t = (Node*) get_unmarked_reference(t->next);
            if(t == tail){
                break;
            }

            t_next = t->next;
        } while(is_marked_reference((uintptr_t) t_next) || (t->key < key));
        // } while(is_marked_reference(t_next) || (t->key < key));

        right_node = t;

        /* 2: Check nodes are adjacent */
        if(left_node_next == right_node) {
            if((right_node != tail) && is_marked_reference((uintptr_t) right_node->next)){
            // if((right_node != tail) && is_marked_reference(right_node->next)){
                goto search_again; /*G1*/
            } else {
                return right_node;
            }
        }

        /* 3: Remove one or more marked nodes */
        if(cas((uintptr_t*) (*left_node)->next, *(uintptr_t*) left_node_next, *(uintptr_t*) right_node)){
            if((right_node != tail) && is_marked_reference((uintptr_t) right_node->next))
            // if((right_node != tail) && is_marked_reference(right_node->next))
                goto search_again; /*G2*/
            else{
                return right_node;
            }
        }
    }while(true); /*B2*/

    return NULL;
}


bool Insert_Element_With_Index(Node *head, Node *tail, int new_key){
    Node *new_node = malloc(sizeof(Node));
    Node *left_node, *right_node;

    new_node->key = new_key;
    new_node->mark = false;

    printf("Insert Function\n");

    do{
        right_node = search(head, tail, &left_node, new_key);

        if((right_node != tail) && (right_node->key == new_key)){
            return false;
        }

        new_node->next = right_node;

        if(cas(((uintptr_t*) &left_node->next), (uintptr_t) right_node, (uintptr_t) new_node )){
            return true;
        }
    }while(true); /*B3*/

    return true;
}


bool Remove_Element_With_Index(Node *head, Node *tail, int search_key){
    Node *right_node, *right_node_next, *left_node;

    printf("Delete Function\n");

    do{
        right_node = search(head, tail, &left_node, search_key);

        if((right_node == tail) && (right_node->key != search_key))
            return false;

        right_node_next = right_node->next;

        if(!is_marked_reference((uintptr_t) right_node_next)){
        // if(!is_marked_reference(right_node_next)){
            if(cas((uintptr_t*) &right_node->next, (uintptr_t) right_node_next, get_marked_reference(*(uintptr_t*) right_node_next))){
            // if(cas((uintptr_t*) &right_node->next, (uintptr_t) right_node_next, get_marked_reference(right_node_next))){
                printf("**** %d*******************\n",search_key);
                break;
            }
        }
    }while(true); /*B4*/

    if(!(cas((uintptr_t*) &left_node->next, (uintptr_t) right_node, (uintptr_t) right_node_next))){ /*C4*/
        right_node = search(head, tail, &left_node, search_key); 
        printf("**** %d*******************\n",search_key);
    }
    return true;
}


bool find(Node *head, Node *tail, int search_key){
    printf("Find Function\n");

    Node *right_node, *left_node;

    right_node = search(head, tail, &left_node, search_key);

    if((right_node == tail) || right_node->key != search_key)
        return false;
    else
        return true;
}


void print_list(Node *head, Node *tail) {
    Node *current_node;

    printf("Print Function\n");
    printf("[");

    for (current_node = head->next; current_node != tail; current_node = current_node->next) {
        if(is_marked_reference((uintptr_t) current_node))
        // if(is_marked_reference(current_node))
            continue;
        printf(" %d ", current_node->key);
    }
    printf("]\n");
}

bool nextBool() {
    int val;
    val = (1 + (int)( 20.0 * rand() / ( RAND_MAX + 1.0 )));

    if(val % 2 == 0)
        return true;
    else
        return false;
}

static Node *list_head;
static Node *list_tail;

void *worker(void *arg) {
    int i = 0;
    int aux = 0;
    for (i = 0; i < *((int *)arg); ++i) {

        /*If true generates insert, otherwise generates remove*/
        if(nextBool()){
            aux = randomNumber();
            printf("Insert = %d\n", aux);
            printf("The ID of this thread is: %u\n", (unsigned int)pthread_self());

            Insert_Element_With_Index(list_head, list_tail, aux);
        } else {
            aux = randomNumber();
            if(find(list_head, list_tail, aux)) {
                printf("Deleted = %d\n", aux);
                printf("The ID of this thread is: %u\n", (unsigned int)pthread_self());

                Remove_Element_With_Index(list_head, list_tail, aux);
            }
        }
        pthread_mutex_lock(&mutex1);
        print_list(list_head, list_tail);
        pthread_mutex_unlock(&mutex1);
    }
    return NULL;
}

int main(int argc, char **argv) {
    int i, count;
    pthread_t *t;

    Create_Linked_list(&list_head, &list_tail);

    if (argc != 3) {
        fprintf(stderr, "%s <#-threads> <#-iterations>\n", argv[0]);
        return 1;
    }

    count = atoi(argv[2]);

    /* create # threads */
    t = (pthread_t *)calloc(atoi(argv[1]), sizeof(pthread_t));

    for (i = 0; i < atoi(argv[1]); ++i)
        assert(!pthread_create(&(t[i]), NULL, worker, (void *)&count));

    /* wait for the completion of all the threads */
    for (i = 0; i < atoi(argv[1]); ++i)
        assert(!pthread_join(t[i], NULL));

    printf("all thread done\n");
    print_list(list_head, list_tail);

    return 0;
}