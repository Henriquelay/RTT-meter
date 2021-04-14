#ifndef ENTRADAS_H_
#define ENTRADAS_H_
#include<stdio.h>
#include<stdlib.h>
#include"arestas.h"
#include"../aux/item.h"
#include"../aux/PQ.h"
#include"../lib/arestas.h"

void leServidores(FILE* file,int* S,int s);
void leClientes(FILE* file,int* C,int c);
void leMonitores(FILE* file,int* M, int m);
void leArestas(FILE* file,aresta* Arestas, int e);

#endif // !ENTRADAS_H_