#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

volatile unsigned long counter = 0;

static pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

int randomNumber(){
    return((1 + (int)( 20.0 * rand() / ( RAND_MAX + 1.0 ) )));
}

/*Sequential List*/
typedef struct Elem {
        int data;
        struct Elem *next;
}elem;

void insert(elem *pointer, int data) {
    /* Iterate through the list till we encounter the last elem.*/
    while(pointer->next != NULL && (pointer->next)->data < data) {
        pointer = pointer -> next;
    }
    /* Allocate memory for the new elem and put data in it.*/
    // pointer->next = (elem *)malloc(sizeof(elem));
    // pointer = pointer->next;
    // pointer->data = data;
    // pointer->next = NULL;
}


int finding(elem *pointer, int key) {
    pointer = pointer -> next;
    /* Iterate through the entire linked list and search for the key. */
    pointer = pointer -> next;

    while(pointer != NULL) {
        if(pointer->data == key) {
            return 1;
        }
        pointer = pointer -> next;
    }
    /*Key is not found */
    return 0;
}

void delete(elem *pointer, int data) {
    printf("Delete da data = %d\n", data);
    /* Go to the elem for which the elem next to it has to be deleted */
    while(pointer->next != NULL && (pointer->next)->data != data) {
            pointer = pointer -> next;
    }
    if(pointer->next==NULL) {
            printf("Element %d is not present in the list\n",data);
            return;
    }
    /* Now pointer points to a elem and the elem next to it has to be removed */
    elem *temp;
    temp = pointer -> next;
    /*temp points to the elem which has to be removed*/
    pointer->next = temp->next;
    /*We removed the elem which is next to the pointer (which is also temp) */
    free(temp);
    /* Beacuse we deleted the elem, we no longer require the memory used for it . 
        free() will deallocate the memory.
        */
    return;
}

void print(elem *pointer) {
    pointer = pointer->next;
    printf("Print Sequential\n");
    while(pointer != NULL){
        printf("%d ",pointer->data);
        pointer = pointer->next;
    }
    printf("\n\n");
    return;
}

void create(elem **head) {
    (*head) = malloc(sizeof(elem));
    (*head)->next = NULL;
}

bool nextBool() {
    int val;
    val = (1 + (int)( 20.0 * rand() / ( RAND_MAX + 1.0 )));

    if(val % 2 == 0)
        return true;
    else
        return false;
}

static elem *start;

void *worker(void *arg) {
    int i = 0;
    int aux = 0;
    for (i = 0; i < *((int *)arg); ++i) {

        /*If true generates insert, otherwise generates remove*/
        if(nextBool()){
            aux = randomNumber();
            insert(start, aux);

            printf("Insert = %d\n",aux);
            printf("The ID of this thread is: %u\n", (unsigned int)pthread_self());
        } else {
            // aux = randomNumber();
            // delete(start, aux);

            // printf("Deleted = %d\n",aux);
            // printf("The ID of this thread is: %u\n", (unsigned int)pthread_self());
        }
        pthread_mutex_lock(&mutex1);
        print(start);
        pthread_mutex_unlock(&mutex1);
    }
    return NULL;
}

int main(int argc, char **argv) {
    int i, count;
    pthread_t *t;

    srand(time(NULL));

    create(&start);

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

    /* print counter value */
    printf("all thread done -> counter=%lu\n", counter);

    print(start);


    return 0;
}