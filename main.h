#ifndef main_h
#define main_h

typedef struct {
    int weight;
    int cost;
} Thing;

typedef struct {
    int id;
    int thingCount;
    int capacity;
    Thing **things;
    int *thingsTakenVector;
} Instance;

typedef struct {
    int weight;
    int cost;
    int *thingPresenceVector;
} Result;

Result *createResult(Instance *instance);
void copyResult(Result *target, Result *src, Instance *instance);
void freeResult(Result *result);

#endif /* main_h */
