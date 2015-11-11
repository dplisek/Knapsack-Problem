#!/bin/bash

for f in 4 10 15 20 22 25 27 30 32 35 37 40
do
  echo -n "$f "
  /Users/Dominik/Library/Caches/CLion12/cmake/generated/290e7237/290e7237/Debug/PriceDecomposition < knap_${f}.inst.dat > knap_${f}.mysol.dat
done

