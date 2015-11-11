#include "BruteForceAlwaysPresent.h"

void evaluateStateBruteForce(Result *result, Instance *instance, int index) {
    Result *originalResult, *backedUpResult = NULL;
    
    if (index == instance->thingCount) return;
    if (result->weight + instance->things[index]->weight <= instance->capacity) {
        originalResult = createResult(instance);
        copyResult(originalResult, result, instance);
        
        result->thingPresenceVector[index] = 1;
        result->weight += instance->things[index]->weight;
        result->cost += instance->things[index]->cost;
        
        evaluateStateBruteForce(result, instance, index + 1);
        
        backedUpResult = createResult(instance);
        copyResult(backedUpResult, result, instance);
        copyResult(result, originalResult, instance);
        freeResult(originalResult);
    }
    
    evaluateStateBruteForce(result, instance, index + 1);
    
    if (backedUpResult && result->cost < backedUpResult->cost) {
        copyResult(result, backedUpResult, instance);
    }
    
    if (backedUpResult) freeResult(backedUpResult);
}

Result* solveInstanceBruteForce(Instance *instance) {
    Result* result = createResult(instance);
    evaluateStateBruteForce(result, instance, 0);
    return result;
}
