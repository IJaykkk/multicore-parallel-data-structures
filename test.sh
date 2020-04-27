#!/bin/bash
numOP=1000

writeRatio1=1
writeRatio2=0.75
writeRatio3=0.5

for((i=0;i<=5;i++))
do
        numThreads=1

        for((j=0;j<=3;j++))
        do
                # echo $numThreads
                # echo $numOP

                echo "Threads:" $numThreads "  numOP:" $numOP  "  writeRatio" $writeRatio1
                ./l_queue_test $numThreads $numOP $writeRatio
		
		echo "Threads:" $numThreads "  numOP:" $numOP  "  writeRatio" $writeRatio2
                ./l_queue_test $numThreads $numOP $writeRatio2
		
		echo "Threads:" $numThreads "  numOP:" $numOP  "  writeRatio" $writeRatio3
                ./l_queue_test $numThreads $numOP $writeRatio3
		((numOP=$numOP*10))
        done

	((numThreads=$numThreads*2))
done
