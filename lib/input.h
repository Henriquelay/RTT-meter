#ifndef INPUT_H_
#define INPUT_H_

#include <stdio.h>
#include <stdlib.h>
// #include "edges.h"
#include "../lib/PQ.h"

vertex_t** readFile(char* fileName, unsigned int *sCount, unsigned int *cCount, unsigned int *mCount, unsigned int *total, unsigned int **sArray, unsigned int **cArray, unsigned int **mArray);

#endif // !INPUT_H_
