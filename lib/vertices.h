#ifndef VERTICES_H_
#define VERTICES_H_


#include<stdlib.h>
#include<stdio.h>

typedef struct vertice {
  unsigned int idA;  
  unsigned int idB;                // identificador do nó
  double weight;     // valor associado ao nó;
}vertice;

vertice* criaArestasVazias(int e);

#endif // !VERTICES_H_