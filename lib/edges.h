#ifndef EDGES_H_
#define EDGES_H_


#include <stdlib.h>
#include <stdio.h>

typedef struct edge_t {
  unsigned int idA;
  unsigned int idB;                 // identificador do nó
  double weight;                    // valor associado ao nó;
}edge_t;

edge_t* createEmptyEdges(int e);

#endif // !EDGES_H_
