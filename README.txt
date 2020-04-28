# Instructions

The following code is run on crunchy3.

Run "module load gcc-9.2", and "make all" to create binaries at the project root directory.
There will be four binaries in "./bin" folder: l_list_test, lf_list_test, l_queue_test, lf_queue_test.

1. l_list_test: To test blocking linked list.
2. lf_list_test: To test lock-free linked list.
3. l_queue_test: To test blocking queue.
4. lf_queue_test: To test lock-free queue.

And, then run "bash run_queue.sh" and "bash run_list" at the project root
directory. The output will be stored in "./res" folder.
