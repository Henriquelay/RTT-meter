#ifndef INPUT_H_
#define INPUT_H_


#include <stdio.h>
#include <stdlib.h>
#include "edges.h"

void leServidores(FILE* file,int* S,int s);
void leClientes(FILE* file,int* C,int c);
void leMonitores(FILE* file,int* M, int m);
void leArestas(FILE* file,edge_t* arestas, int e);

#endif // !INPUT_H_
