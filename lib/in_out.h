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

void destroyVertexList(vertex_t** Vertices, unsigned int nVertices);
OutType createOutType (unsigned int serverId, unsigned int clientId, double inflRTT);

vertex_t** readFile(char* fileName, unsigned int *sCount, unsigned int *cCount, unsigned int *mCount, unsigned int *total, unsigned int **sArray, unsigned int **cArray, unsigned int **mArray);
void writeFile(char* fileName, OutType* outTArray, unsigned int Nlines);

#endif // !IN_OUT_H_
