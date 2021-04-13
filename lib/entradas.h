#ifndef ENTRADAS_H_
#define ENTRADAS_H_
#include<stdio.h>
#include<stdlib.h>
#include"vertices.h"
#include"../aux/item.h"
#include"../aux/PQ.h"

void leServidores(FILE* file,int* S,int s);
void leClientes(FILE* file,int* C,int c);
void leMonitores(FILE* file,int* M, int m);
void leVertices(FILE* file,Item** A, int e, int*map, int* tamanho);

#endif // !ENTRADAS_H_