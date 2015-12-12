#!/bin/bash

output=../doc/3/ratio

numThings=9
numInsts=50
ratio=0.5           # capacity to total weight
exp=1               # 1/w^exp for small things or 1/(wmax-w)^exp for big things
balance=0           # -1 for small things or 1 for big things
maxCost=100
maxWeight=100

mkdir -p $output
for method in BruteForce BranchNBound PriceDecomposition PriceToWeightRatio
do
    file=${output}/${method}
    echo -n "" > $file
    for i in $(seq 0.01 0.01 1.0)
    do
        echo -n "$i " >> $file
        /home/dominik/.CLion12/system/cmake/generated/8fe85d49/8fe85d49/Debug/knapgen -n $numThings -N $numInsts -m $i -k $exp -d $balance -C $maxCost -W $maxWeight -I 1000 1> myinst.dat 2> knapgenerrs
        /home/dominik/.CLion12/system/cmake/generated/8fe85d49/8fe85d49/Debug/$method < myinst.dat 1> myinst.mysol.dat 2>> $file
    done
done

method=PriceToWeightRatio
file=${output}/${method}.relerrs
echo -n "" > $file
for i in $(seq 0.01 0.01 1.0)
do
    echo -n "$i " >> $file
    /home/dominik/.CLion12/system/cmake/generated/8fe85d49/8fe85d49/Debug/knapgen -n $numThings -N $numInsts -m $i -k $exp -d $balance -C $maxCost -W $maxWeight -I 1000 1> myinst.dat 2> knapgenerrs
    /home/dominik/.CLion12/system/cmake/generated/8fe85d49/8fe85d49/Debug/$method -r < myinst.dat 1> myinst.mysol.dat 2>> $file
done