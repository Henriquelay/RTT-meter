#ifndef IN_OUT_H_
#define IN_OUT_H_

#include <stdio.h>
#include <stdlib.h>
// #include "edges.h"
#include "../lib/PQ.h"
#include "../lib/rtt.h"

typedef struct outType
{
    unsigned int serverId;
    unsigned int clientId;
    double inflRTT;
}OutType;

vertex_t** readFile(char* fileName, unsigned int *sCount, unsigned int *cCount, unsigned int *mCount, unsigned int *total, unsigned int **sArray, unsigned int **cArray, unsigned int **mArray);
OutType** createOutTypeArray (unsigned int size);
OutType* createOutType (unsigned int serverId, unsigned int clientId, double inflRTT);
void writeFile (char* outFileName, unsigned int Nserver, unsigned int Nclient, unsigned int Nmonitor, unsigned int Ntotal, unsigned int* serverIds, unsigned int* clientIds, unsigned int* monitorIds, vertex_t** vertices);
int comparator(const void* p, const void* q);

#endif // !IN_OUT_H_
