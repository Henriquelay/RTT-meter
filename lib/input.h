#ifndef INPUT_H_
#define INPUT_H_

#include <stdio.h>
#include <stdlib.h>
// #include "edges.h"
#include "../lib/PQ.h"

vertex_t** readFile(char* fileName, unsigned int *s, unsigned int *c, unsigned int *m, unsigned int *total);

#endif // !INPUT_H_
