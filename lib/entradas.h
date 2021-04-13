#ifndef ENTRADAS_H_
#define ENTRADAS_H_
#include<stdio.h>
#include<stdlib.h>
#include"arestas.h"

void leServidores(FILE* file,int* S,int s);
void leClientes(FILE* file,int* C,int c);
void leMonitores(FILE* file,int* M, int m);
void leArestas(FILE* file,aresta* arestas, int e);

#endif // !ENTRADAS_H_