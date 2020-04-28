#include "l_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>
#include <getopt.h>


int main(int argc, char** argv) {
    if ((argc - optind) < 4) {
        printf("I need four fixed arguments!");
        exit(1);
    }

    int num_threads = strtol(argv[1], NULL, 10);
    int num_ops = strtol(argv[2], NULL, 10);
    float insert_ratio = strtof(argv[3], NULL);
    float delete_ratio = strtof(argv[4], NULL);

    /* mapping from the ratio to range(0, 1) */
    float insert_ts = insert_ratio;
    float delete_ts = insert_ts + delete_ratio;

    time_t t;
    srand((unsigned) time(&t));

    list l;
    list_new(&l);

    # pragma omp parallel for num_threads(num_threads)
    for (int i = 0; i < num_ops; i++) {
        float r = (float) rand() / (float) RAND_MAX;
        int num  = rand();
        if (r < insert_ts)  {
            list_insert(&l, num);

            #ifdef DEBUG
            printf("inserting %d, index: %d, by %d\n", num, i, omp_get_thread_num());
            #endif
        } else if (insert_ts < r && r < delete_ts) {
            int val = list_delete(&l, num);

            #ifdef DEBUG
            printf("deleting %d, index: %d, status: %d, by %d\n", num, i, val, (int) omp_get_thread_num());
            #endif
        } else {
            int val = list_find(&l, num);

            #ifdef DEBUG
            printf("finding %d, index: %d, status: %d, by %d\n", num, i, val, (int) omp_get_thread_num());
            #endif
        }
    }

    #ifdef DEBUG
    list_print(&l, num_ops);
    #endif

    return 0;
}
