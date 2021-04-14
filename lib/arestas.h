#ifndef ARESTAS_H_
#define ARESTAS_H_


#include<stdlib.h>
#include<stdio.h>

typedef struct aresta {
  unsigned int idA;  
  unsigned int idB;                // identificador do nó
  double weight;     // valor associado ao nó;
}aresta;

aresta* criaArestasVazias(int e);

#endif // !ARESTAS_H_