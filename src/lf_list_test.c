#include "lf_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>


int main(int argc, char** argv) {
    /* non-blocking linked list */
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

    return 0;
}
