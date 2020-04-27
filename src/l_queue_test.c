#include "l_queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>


int main(int argc, char** argv) {
    /* blocking queue */
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

    return 0;
}
