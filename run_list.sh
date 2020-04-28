#!/bin/bash

writeRatio1=0.50
writeRatio2=0.75

numThreads=1
for numThreads in 1 2 4 8 16
do
    for numOP in 1000000 2000000 4000000 10000000
    do
        echo "./bin/l_list_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio1, $t times"
        echo "./bin/l_list_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio1, $t times"    >> res/l_list_result_50.txt
        { time ./bin/l_list_test $numThreads $numOP $writeRatio1 ;}                                       2>> res/l_list_result_50.txt
        echo "-----------------------------------------------------"                                       >> res/l_list_result_50.txt

        echo "./bin/l_list_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio2, $t times"
        echo "./bin/l_list_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio2, $t times"    >> res/l_list_result_75.txt
        { time ./bin/l_list_test $numThreads $numOP $writeRatio2 ;}                                       2>> res/l_list_result_75.txt
        echo "-----------------------------------------------------"                                       >> res/l_list_result_75.txt
    done
done


numThreads=1
for numThreads in 1 2 4 8 16
do
    for numOP in 1000000 2000000 4000000 10000000
    do
        echo "./bin/lf_list_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio1, $t times"
        echo "./bin/lf_list_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio1, $t times"   >> res/lf_list_result_50.txt
        { time ./bin/lf_list_test $numThreads $numOP $writeRatio1 ; }                                     2>> res/lf_list_result_50.txt
        echo "-----------------------------------------------------"                                       >> res/lf_list_result_50.txt

        echo "./bin/lf_list_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio2, $t times"
        echo "./bin/lf_list_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio2, $t times"    >> res/lf_list_result_75.txt
        { time ./bin/lf_list_test $numThreads $numOP $writeRatio2 ;}                                       2>> res/lf_list_result_75.txt
        echo "-----------------------------------------------------"                                        >> res/lf_list_result_75.txt
    done
done