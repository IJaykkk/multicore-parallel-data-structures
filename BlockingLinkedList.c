#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <time.h>

volatile unsigned long counter = 0;
static pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER;

int randomNumber(){
    return((1 + (int)( 20.0 * rand() / ( RAND_MAX + 1.0 ) )));
}

/*Sequential List*/
typedef struct Elem {
        int data;
        struct Elem *next;
}elem;

static elem *start;

void create(elem **head) {
    (*head) = malloc(sizeof(elem)); // dummy head
    (*head)->next = NULL;
}

void insert(elem *pointer, int data) {
    /* Iterate through the list till we encounter the last elem.*/
    while(pointer->next != NULL) {
        pointer = pointer -> next;
    }
    /* Allocate memory for the new elem and put data in it.*/
    pointer->next = (elem *)malloc(sizeof(elem));
    pointer->next->data = data;
    pointer->next->next = NULL;
}

int finding(elem *pointer, int data) {
    while (pointer->next != NULL && (pointer->next)->data != data) {
            pointer = pointer -> next;
    }

    if (pointer->next != NULL) {
        // printf("Element %d is found in the list\n",data);
        return true;
    } else {
        return false;
    }
}

void delete(elem *pointer, int data) {
    /* Go to the elem for which the elem next to it has to be deleted */
    while(pointer->next != NULL && (pointer->next)->data != data) {
            pointer = pointer -> next;
    }

    if(pointer->next==NULL) {
            // printf("Element %d is not present in the list\n",data);
            return;
    }

    elem *temp;
    temp = pointer -> next;
    pointer->next = temp->next;
    free(temp);

    return;
}

void print(elem *pointer) {
    pointer = pointer->next;
    // printf("Print Sequential\n");
    while(pointer != NULL){
        printf("%d ",pointer->data);
        pointer = pointer->next;
    }
    printf("\n");
    return;
}

bool nextBool() {
    int val;
    val = (1 + (int)( 20.0 * rand() / ( RAND_MAX + 1.0 )));

    if(val % 2 == 0)
        return true;
    else
        return false;
}

void *worker(void *arg) {
    int i = 0;
    int aux = 0;
    for (i = 0; i < *((int *)arg); ++i) {

        /*If true generates insert, otherwise generates remove*/
        if(nextBool()){
            aux = randomNumber();

            pthread_mutex_lock(&mutex1);
            insert(start, aux);
            pthread_mutex_unlock(&mutex1);

            printf("Insert = %d\n",aux);
            printf("The ID of this thread is: %u\n", (unsigned int)pthread_self());
        } else {
            aux = randomNumber();

            pthread_mutex_unlock(&mutex2);
            delete(start, aux);
            pthread_mutex_unlock(&mutex2);

            printf("Deleted = %d\n",aux);
            printf("The ID of this thread is: %u\n", (unsigned int)pthread_self());
        }
        pthread_mutex_lock(&mutex3);
        print(start);
        pthread_mutex_unlock(&mutex3);
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

    printf("all thread done\n");

    return 0;
}