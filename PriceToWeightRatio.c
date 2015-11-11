#include <stdlib.h>
#include "Knapsack.h"

typedef struct {
    int index;
    float ratio;
} ThingRatio;

Thing *extractThingWithBestRatio(Instance *instance, int *index) {
    int i;
    float testedRatio;
    ThingRatio bestRatio;
    Thing *result;
    
    bestRatio.index = -1;
    for (i = 0; i < instance->thingCount; i++) {
        if (instance->thingsTakenVector[i]) continue;
        testedRatio = ((float) instance->things[i]->cost) / instance->things[i]->weight;
        if (bestRatio.index == -1 || testedRatio > bestRatio.ratio) {
            bestRatio.index = i;
            bestRatio.ratio = testedRatio;
        }
    }
    
    if (bestRatio.index >= 0) {
        result = instance->things[bestRatio.index];
        instance->thingsTakenVector[bestRatio.index] = 1;
        *index = bestRatio.index;
        return result;
    } else {
        return NULL;
    }
}

void evaluateState(Result *result, Instance *instance) {
    Thing *bestRatioThing;
    int bestRatioThingIndex;
    
    bestRatioThing = extractThingWithBestRatio(instance, &bestRatioThingIndex);
    if (!bestRatioThing) return;
    if (result->weight + bestRatioThing->weight > instance->capacity) return;
    
    result->thingPresenceVector[bestRatioThingIndex] = 1;
    result->weight += bestRatioThing->weight;
    result->cost += bestRatioThing->cost;
    evaluateState(result, instance);
}

Result* solveInstance(Instance *instance) {
    Result* result = createResult(instance);
    evaluateState(result, instance);
    return result;
}
