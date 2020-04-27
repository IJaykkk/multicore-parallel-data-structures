#include "l_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>


int main(int argc, char** argv) {
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
