#!/bin/bash

writeRatio1=0.30
writeRatio2=0.50
writeRatio3=0.75
writeRatio4=1.00

removeRatio1=0.20
removeRatio2=0.50
removeRatio3=0.25
removeRatio4=0.00

for numThreads in 1 2 4 8 16 32
do
    for numOP in 5000 10000 20000 40000 80000
    do
        echo "./bin/l_list_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio1 removeRatio $removeRatio1"
        echo "./bin/l_list_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio1 removeRatio $removeRatio1"    >> res/l_list_result_w30_d20.txt
        { time ./bin/l_list_test $numThreads $numOP $writeRatio1 $removeRatio1;}                                          2>> res/l_list_result_w30_d20.txt
        echo "------------------------------------------------------------------"                                          >> res/l_list_result_w30_d20.txt

        echo "./bin/l_list_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio2 removeRatio $removeRatio2"
        echo "./bin/l_list_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio2 removeRatio $removeRatio2"    >> res/l_list_result_w50_d50.txt
        { time ./bin/l_list_test $numThreads $numOP $writeRatio2 $removeRatio2;}                                          2>> res/l_list_result_w50_d50.txt
        echo "-----------------------------------------------------------------"                                           >> res/l_list_result_w50_d50.txt

        echo "./bin/l_list_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio3 removeRatio $removeRatio3"
        echo "./bin/l_list_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio3 removeRatio $removeRatio3"    >> res/l_list_result_w75_d25.txt
        { time ./bin/l_list_test $numThreads $numOP $writeRatio3 $removeRatio3;}                                          2>> res/l_list_result_w75_d25.txt
        echo "-----------------------------------------------------------------"                                           >> res/l_list_result_w75_d25.txt

        echo "./bin/l_list_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio4 removeRatio $removeRatio4"
        echo "./bin/l_list_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio4 removeRatio $removeRatio4"    >> res/l_list_result_w100.txt
        { time ./bin/l_list_test $numThreads $numOP $writeRatio4 $removeRatio4;}                                          2>> res/l_list_result_w100.txt
        echo "-----------------------------------------------------------------"                                           >> res/l_list_result_w100.txt
    done
done

for numThreads in 1 2 4 8 16 32
do
    for numOP in 5000 10000 20000 40000 80000
    do
        echo "./bin/lf_list_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio1 removeRatio $removeRatio1"
        echo "./bin/lf_list_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio1 removeRatio $removeRatio1"    >> res/lf_list_result_w30_d20.txt
        { time ./bin/lf_list_test $numThreads $numOP $writeRatio1 $removeRatio1;}                                          2>> res/lf_list_result_w30_d20.txt
        echo "------------------------------------------------------------------"                                           >> res/lf_list_result_w30_d20.txt

        echo "./bin/lf_list_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio2 removeRatio $removeRatio2"
        echo "./bin/lf_list_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio2 removeRatio $removeRatio2"    >> res/lf_list_result_w50_d50.txt
        { time ./bin/lf_list_test $numThreads $numOP $writeRatio2 $removeRatio2;}                                          2>> res/lf_list_result_w50_d50.txt
        echo "-----------------------------------------------------------------"                                            >> res/lf_list_result_w50_d50.txt

        echo "./bin/lf_list_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio3 removeRatio $removeRatio3"
        echo "./bin/lf_list_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio3 removeRatio $removeRatio3"    >> res/lf_list_result_w75_d25.txt
        { time ./bin/lf_list_test $numThreads $numOP $writeRatio3 $removeRatio3;}                                          2>> res/lf_list_result_w75_d25.txt
        echo "-----------------------------------------------------------------"                                            >> res/lf_list_result_w75_d25.txt

        echo "./bin/lf_list_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio4 removeRatio $removeRatio4"
        echo "./bin/lf_list_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio4 removeRatio $removeRatio4"    >> res/lf_list_result_w100.txt
        { time ./bin/lf_list_test $numThreads $numOP $writeRatio4 $removeRatio4;}                                          2>> res/lf_list_result_w100.txt
        echo "-----------------------------------------------------------------"                                            >> res/lf_list_result_w100.txt
    done
done
