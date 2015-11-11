cmake_minimum_required(VERSION 3.3)
project(Knapsack)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic")

set(SOURCE_FILES main.c main.h BruteForceAlwaysPresent.c BruteForceAlwaysPresent.h Knapsack.h)
add_executable(BruteForce ${SOURCE_FILES} BruteForce.c)
add_executable(PriceToWeightRatio ${SOURCE_FILES} PriceToWeightRatio.c)
add_executable(BranchNBound ${SOURCE_FILES} BranchNBound.c)
add_executable(PriceDecomposition ${SOURCE_FILES} PriceDecomposition.c)