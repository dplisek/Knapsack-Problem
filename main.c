#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "main.h"
#include "Knapsack.h"
#include "BruteForceAlwaysPresent.h"

/*#define CALC_REL_ERR*/
/*#define FILE_INPUT "/users/dominik/desktop/knapsack/data/myinst.dat"*/

#ifdef FILE_INPUT
#define INPUT_STREAM            fopen(FILE_INPUT, "r")
#define CLOSE_INPUT_STREAM      fclose(inputFile)
#else
#define INPUT_STREAM            stdin
#define CLOSE_INPUT_STREAM
#endif

FILE *inputFile;

int readNumber() {
    int i;
    char c, buffer[10];

    i = 0;
    memset(buffer, 0, sizeof(buffer));
    c = fgetc(inputFile);
    while (c >= '0' && c <= '9') {
        buffer[i++] = c;
        c = fgetc(inputFile);
    }

    return atoi(buffer);
}

void readThingsIntoInstance(Instance *instance) {
    int i;

    instance->things = malloc(sizeof(Thing *) * instance->thingCount);
    for (i = 0; i < instance->thingCount; i++) {
        instance->things[i] = (Thing *)malloc(sizeof(Thing));
        instance->things[i]->weight = readNumber();
        instance->things[i]->cost = readNumber();
    }
}

Instance *readInstance() {
    Instance *instance;

    instance = malloc(sizeof(Instance));
    instance->id = readNumber();
    if (instance->id == 0) {
        free(instance);
        return NULL;
    }
    instance->thingCount = readNumber();
    instance->capacity = readNumber();
    readThingsIntoInstance(instance);
    instance->thingsTakenVector = malloc(sizeof(int) * instance->thingCount);
    memset(instance->thingsTakenVector, 0, sizeof(int) * instance->thingCount);

    return instance;
}

Result *createResult(Instance *instance) {
    Result *result = malloc(sizeof(Result));
    result->weight = 0;
    result->cost = 0;
    result->thingPresenceVector = malloc(sizeof(int) * instance->thingCount);
    memset(result->thingPresenceVector, 0, sizeof(int) * instance->thingCount);
    return result;
}

void copyResult(Result *target, Result *src, Instance *instance) {
    target->weight = src->weight;
    target->cost = src->cost;
    memcpy(target->thingPresenceVector, src->thingPresenceVector, sizeof(int) * instance->thingCount);
}

void printResult(Result *result, Instance *instance) {
    int i;

    printf("%d", instance->id);
    printf(" %d", instance->thingCount);
    if (result) {
        printf(" %d ", result->cost);
        for (i = 0; i < instance->thingCount; i++) {
            printf(" %d", result->thingPresenceVector[i]);
        }
    } else {
        printf(" NO RESULT");
    }
    printf("\n");
}

void freeResult(Result *result) {
    free(result->thingPresenceVector);
    free(result);
}

void freeInstance(Instance *instance) {
    int i;

    for (i = 0; i < instance->thingCount; i++) {
        free(instance->things[i]);
    }
    free(instance->thingsTakenVector);
    free(instance->things);
    free(instance);
}

int main(int argc, const char * argv[]) {
    Instance *instance;
    Result *result;
    clock_t tt1, tt2;
    double elapsedTime;
#ifdef CALC_REL_ERR
    Result *bfResult;
    float relErr = 0.0;
    int totalInstances = 0;
#endif

    inputFile = INPUT_STREAM;
    if (!inputFile) {
        fprintf(stderr, "Missing input file.");
        return EXIT_FAILURE;
    }

    tt1 = clock();
    while ((instance = readInstance())) {
        result = solveInstance(instance);
#ifdef CALC_REL_ERR
            bfResult = solveInstanceBruteForce(instance);
            relErr += (float) (bfResult->cost - result->cost) / bfResult->cost;
            totalInstances++;
            freeResult(bfResult);
#endif
        printResult(result, instance);
        if (result) freeResult(result);
        freeInstance(instance);
    }
    tt2 = clock();

#ifdef CALC_REL_ERR
        relErr /= totalInstances;
        fprintf(stderr, "%.4f\n", relErr);
#else
        elapsedTime = ((double) tt2 - tt1) / (CLOCKS_PER_SEC / 1000);
        fprintf(stderr, "%.3f\n", elapsedTime);
#endif

    CLOSE_INPUT_STREAM;

    return EXIT_SUCCESS;
}
