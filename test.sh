#!/bin/bash
numOP=1000

writeRatio1=1
writeRatio2=0.75
writeRatio3=0.5

for((i=0;i<=3;i++))
do
        numThreads=1

        for((j=0;j<=5;j++))
        do
                ((numThreads=$numThreads*2))
                # echo $numThreads
                # echo $numOP

                echo "numOP:" $numOP "  Threads:" $numThreads  "  writeRatio" $writeRatio1
                ./l_queue_test $numThreads $numOP $writeRatio

                echo "numOP:" $numOP "  Threads:" $numThreads  "  writeRatio" $writeRatio2
                ./l_queue_test $numThreads $numOP $writeRatio2

                echo "numOP:" $numOP "  Threads:" $numThreads  "  writeRatio" $writeRatio3
                ./l_queue_test $numThreads $numOP $writeRatio3
        done

        ((numOP=$numOP*10))
done
