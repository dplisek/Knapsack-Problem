#include "Knapsack.h"
#include <stdlib.h>
#include <string.h>

int bestCost = 0;
int* remainingMaxCosts = NULL;

int remainingMaxCost(Instance *instance, int index) {
    int i, cost;

    if (remainingMaxCosts[index] >= 0) return remainingMaxCosts[index];

    cost = 0;
    for (i = index; i < instance->thingCount; i++) {
        cost += instance->things[i]->cost;
    }
    remainingMaxCosts[index] = cost;

    return cost;
}

void evaluateState(Result *result, Instance *instance, int index) {
    Result *originalResult, *backedUpResult = NULL;

    if (index == instance->thingCount) return;
    if (result->cost + remainingMaxCost(instance, index) <= bestCost) return;
    if (result->weight + instance->things[index]->weight <= instance->capacity) {
        originalResult = createResult(instance);
        copyResult(originalResult, result, instance);

        result->thingPresenceVector[index] = 1;
        result->weight += instance->things[index]->weight;
        result->cost += instance->things[index]->cost;

        evaluateState(result, instance, index + 1);
        if (result->cost > bestCost) bestCost = result->cost;

        backedUpResult = createResult(instance);
        copyResult(backedUpResult, result, instance);
        copyResult(result, originalResult, instance);
        freeResult(originalResult);
    }

    evaluateState(result, instance, index + 1);
    if (result->cost > bestCost) bestCost = result->cost;

    if (backedUpResult && result->cost < backedUpResult->cost) {
        copyResult(result, backedUpResult, instance);
    }

    if (backedUpResult) freeResult(backedUpResult);
}

Result* solveInstance(Instance *instance) {
    Result *result;

    bestCost = 0;
    remainingMaxCosts = malloc(sizeof(int) * instance->thingCount);
    memset(remainingMaxCosts, -1, sizeof(int) * instance->thingCount);
    result = createResult(instance);
    evaluateState(result, instance, 0);
    free(remainingMaxCosts);

    return result;
}
