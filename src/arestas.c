#include "../lib/edges.h"

edge_t* createEmptyEdges(int e) {
  edge_t* novo = malloc(sizeof * novo * e );
  for (int i = 0; i < e; i++) {
    novo[i].idA = 0;
    novo[i].idB = 0;
    novo[i].weight = 0;
  }
  return novo;
}
