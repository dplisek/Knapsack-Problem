#!/bin/bash

for f in 4 10 15 20 22 25 27 30 32 35 37 40
do
  echo -n "$f "
  /Users/Dominik/Library/Developer/Xcode/DerivedData/Knapsack-ajlsyszrgjwydsagsitvsuekdqpo/Build/Products/Debug/Price\ to\ Weight\ Ratio --calc-rel-err < knap_${f}.inst.dat > knap_${f}.mysol.dat
done

