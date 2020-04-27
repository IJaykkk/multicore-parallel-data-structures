//#include "lqueue.h" 
//#include "lqueue.h" 
//#include "llist.h"
#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>


int main(int argc, char** argv) {
    /* blocking queue
     *
    queue *q = queue_new();
    time_t t;
    srand((unsigned) time(&t));

    # pragma omp parallel for num_threads(8)
    for (int i = 0; i < 300; i++) {
        int num  = rand() % 100;
        if (num % 3 >= 1)  {
            printf("num: %d inserting by %d\n", num, omp_get_thread_num());
            queue_push(q, num);
        } else {
            int val = queue_pop(q);
            printf("num: %d poped by %d\n", val, omp_get_thread_num());
        }
    }

    queue_print(q);
    queue_delete(q);
    */

    printf("hello world\n");
    
    /* non-blocking queue
     *
    time_t t;
    srand((unsigned) time(&t));

    queue q;
    queue_new(&q);

    # pragma omp parallel for num_threads(8)
    for (int i = 0; i < 300; i++) {
        int num  = rand() % 100 + 1;
        if (num % 3 >= 1)  {
            printf("num: %d inserting by %d\n", num, omp_get_thread_num());
            queue_push(&q, (void *) num);
        } else {
            int val = (long) queue_pop(&q);
            if (val == 0) {
                printf("empty queue by %d\n", omp_get_thread_num());
            } else {
                printf("num: %d poped by %d\n", val, omp_get_thread_num());
            }
        }
    }
    queue_print(&q);
    */

    /* non-blocking linked list */
    /*
    time_t t;
    srand((unsigned) time(&t));

    list l;
    list_new(&l);
    # pragma omp parallel for num_threads(9)
    for (int i = 0; i < 800; i++) {
        int num  = rand() % 100 + 1;
        if (num % 3 >= 1)  {
            printf("num: %d inserting by %d\n", num, omp_get_thread_num());
            list_insert(&l, num);
        } else {
            int val = list_delete(&l, rand() % 100);
            printf("status: %d poped by %d\n", val, omp_get_thread_num());
        }
    }
    list_print(&l);
    */

    /* blocking linked list */
    time_t t;
    srand((unsigned) time(&t));

    list l;
    list_new(&l);
    int idx = 1;
    int *buffer = calloc(1000, sizeof(int));
    # pragma omp parallel for num_threads(21)
    for (int i = 0; i < 500; i++) {
        int num  = rand() % 100 + 1;
        if (num % 3 >= 1)  {
            printf("num: %d inserting by %d\n", num, omp_get_thread_num());
            list_insert(&l, num);
            buffer[idx++] = num;
        } else {
            int tmp_idx = rand() % idx;
            int val = list_delete(&l, buffer[tmp_idx]);
            printf("status: %d poped by %d\n", val, omp_get_thread_num());
        }
    }
    list_print(&l);
    return 0;
}
