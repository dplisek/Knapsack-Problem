#!/bin/bash

for f in 4 10 15 20 22 25 27 30 32 35 37 40
do
  echo -n "$f "
  /home/dominik/.CLion12/system/cmake/generated/8fe85d49/8fe85d49/Debug/PriceDecomposition < knap_${f}.inst.dat > knap_${f}.mysol.dat
done

