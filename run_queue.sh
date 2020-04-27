#!/bin/bash

writeRatio1=0.50
writeRatio2=0.75
writeRatio3=1.00

numThreads=1
for((i=0;i<=5;i++))
do
    numOP=10

    for((j=1;j<=6;j++))
    do
        for((t=1;t<3;t++))
        do
            echo "./bin/l_queue_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio1, $t times"
            echo "./bin/l_queue_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio1, $t times"    >> res/l_queue_result_50.txt
            { time ./bin/l_queue_test $numThreads $numOP $writeRatio1 ;}                                       2>> res/l_queue_result_50.txt
            echo "-----------------------------------------------------"                                        >> res/l_queue_result_50.txt
        done

        for((t=1;t<3;t++))
        do
            echo "./bin/l_queue_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio2, $t times"
            echo "./bin/l_queue_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio2, $t times"    >> res/l_queue_result_75.txt
            { time ./bin/l_queue_test $numThreads $numOP $writeRatio2 ;}                                       2>> res/l_queue_result_75.txt
            echo "-----------------------------------------------------"                                        >> res/l_queue_result_75.txt
        done

        for((t=1;t<3;t++))
        do
            echo "./bin/l_queue_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio3, $t times"
            echo "./bin/l_queue_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio3, $t times"    >> res/l_queue_result_100.txt
            { time ./bin/l_queue_test $numThreads $numOP $writeRatio3 ;}                                       2>> res/l_queue_result_100.txt
            echo "-----------------------------------------------------"                                        >> res/l_queue_result_100.txt
        done

        ((numOP=$numOP*10))
    done

    ((numThreads=$numThreads*2))
done


numThreads=1
for((i=0;i<=5;i++))
do
    numOP=10

    for((j=1;j<=6;j++))
    do
        for((t=1;t<3;t++))
        do
            echo "./bin/lf_queue_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio1, $t times"
            echo "./bin/lf_queue_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio1, $t times"   >> res/lf_queue_result_50.txt
            { time ./bin/lf_queue_test $numThreads $numOP $writeRatio1 ; }                                     2>> res/lf_queue_result_50.txt
            echo "-----------------------------------------------------"                                        >> res/lf_queue_result_50.txt
        done

        for((t=1;t<3;t++))
        do
            echo "./bin/lf_queue_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio2, $t times"
            echo "./bin/lf_queue_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio2, $t times"    >> res/lf_queue_result_75.txt
            { time ./bin/lf_queue_test $numThreads $numOP $writeRatio2 ;}                                       2>> res/lf_queue_result_75.txt
            echo "-----------------------------------------------------"                                         >> res/lf_queue_result_75.txt
        done

        for((t=1;t<3;t++))
        do
            echo "./bin/lf_queue_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio3, $t times"
            echo "./bin/lf_queue_test threads: $numThreads, numOP: $numOP, writeRatio $writeRatio3, $t times"    >> res/lf_queue_result_100.txt
            { time ./bin/lf_queue_test $numThreads $numOP $writeRatio3 ;}                                       2>> res/lf_queue_result_100.txt
            echo "-----------------------------------------------------"                                         >> res/lf_queue_result_100.txt
        done

        ((numOP=$numOP*10))
    done

    ((numThreads=$numThreads*2))
done
