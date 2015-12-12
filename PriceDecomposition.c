#include <stdlib.h>
#include <sys/param.h>
#include <string.h>
#include <math.h>
#include "Knapsack.h"
#include "main.h"

#define IGNORE_LOWEST_BITS 0

Instance *instance;
int maxCost;
int **weights;
Result *bestResult;

int calculateMaxCost() {
    int i, cost;

    cost = 0;
    for (i = 0; i < instance->thingCount; ++i) {
        cost += instance->things[i]->cost;
    }

    return cost >> IGNORE_LOWEST_BITS;
}

void initWeights() {
    int i;

    weights = malloc(sizeof(int *) * instance->thingCount);
    for (i = 0; i < instance->thingCount; ++i) {
        weights[i] = malloc(sizeof(int) * (maxCost + 1));
        memset(weights[i], -1, sizeof(int) * (maxCost + 1));
    }
}

void freeWeights() {
    int i;

    for (i = 0; i < instance->thingCount; ++i) {
        free(weights[i]);
    }
    free(weights);
}

int evaluateTableCell(int thing, int cost);

int getWeightOf(int thing, int cost) {
    if (thing < 0) {
        if (cost == 0) return 0;
        else return INT_MAX;
    }
    if (cost < 0) return INT_MAX;
    if (weights[thing][cost] >= 0) return weights[thing][cost];
    return evaluateTableCell(thing, cost);
}

int evaluateTableCell(int thing, int cost) {
    int weightWithout, weightWith;

    weightWithout = getWeightOf(thing - 1, cost);
    weightWith = getWeightOf(thing - 1, cost - (instance->things[thing]->cost >> IGNORE_LOWEST_BITS));
    if (weightWith < INT_MAX) weightWith += instance->things[thing]->weight;
    weights[thing][cost] = MIN(weightWithout, weightWith);
    return weights[thing][cost];
}

void evaluateLastThing() {
    int i;

    for (i = 0; i <= maxCost; ++i) {
        evaluateTableCell(instance->thingCount - 1, i);
    }
}

void reconstructBestResultVector(int thing, int cost) {
    if (thing == 0) {
        if (cost == 0) bestResult->thingPresenceVector[thing] = 0;
        else bestResult->thingPresenceVector[thing] = 1;
        return;
    }

    if (weights[thing - 1][cost] == weights[thing][cost]) {
        bestResult->thingPresenceVector[thing] = 0;
    } else {
        bestResult->thingPresenceVector[thing] = 1;
        cost -= instance->things[thing]->cost >> IGNORE_LOWEST_BITS;
    }
    thing--;
    reconstructBestResultVector(thing, cost);
}

void findBestResult() {
    int i, j;

    bestResult = createResult(instance);
    for (i = maxCost; i >= 0; --i) {
        if (weights[instance->thingCount - 1][i] <= instance->capacity) {
            bestResult->weight = weights[instance->thingCount - 1][i];
            reconstructBestResultVector(instance->thingCount - 1, i);
            bestResult->cost = 0;
            for (j = 0; j < instance->thingCount; j++) {
                if (bestResult->thingPresenceVector[j]) bestResult->cost += instance->things[j]->cost;
            }
            break;
        }
    }
}

Result *solveInstance(Instance *pInstance) {
    instance = pInstance;
    maxCost = calculateMaxCost();
    initWeights();
    evaluateLastThing();
    findBestResult();
    freeWeights();
    return bestResult;
}
