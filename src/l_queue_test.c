#include "l_queue.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>
#include <getopt.h>


int main(int argc, char** argv) {
    if ((argc - optind) < 3) {
        printf("I need three fixed arguments!");
        exit(1);
    }

    int num_threads = strtol(argv[1], NULL, 10);
    int num_ops = strtol(argv[2], NULL, 10);
    float push_ratio = strtof(argv[3], NULL);

    time_t t;
    srand((unsigned) time(&t));

    queue *q = queue_new();

    # pragma omp parallel for num_threads(num_threads)
    for (int i = 0; i < num_ops; i++) {
        #ifdef DEBUG
        printf("current idx: %d\n", i);
        #endif

        int num  = rand();
        float r = (float) rand() / (float) RAND_MAX;
        if (r < push_ratio)  {
            queue_push(q, num);

            #ifdef DEBUG
            printf("num: %d inserting by %d\n", num, omp_get_thread_num());
            #endif
        } else {
            int val = queue_pop(q);

            #ifdef DEBUG
            printf("num: %d poped by %d\n", val, omp_get_thread_num());
            #endif
        }
    }

    #ifdef DEBUG
    queue_print(q, num_ops);
    queue_delete(q);
    #endif

    return 0;
}
