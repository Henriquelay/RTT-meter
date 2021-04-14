#include<stdio.h>
#include<stdlib.h>
#include"../lib/input.h"
#include"../lib/arestas.h"

int main(int argc, char** argv) {
    //definição da maioria das variaveis
    char* fileName = argv[1];
    puts(fileName);
    FILE* file = fopen(fileName, "r");

    if (!file) {
        fprintf(stderr, "Falha ao abrir o arquivo '%s'.\n", fileName);
        return -1;
    }
    aresta* arestas;
    int* S;
    int* C;
    int* M;
    int v, e, s, c, m;

    // // leArquivo(file,S,C,M);
    fscanf(file, "%d %d", &v, &e);
    fscanf(file, "%d %d %d", &s, &c, &m);
    S = malloc(s * sizeof(int));
    C = malloc(c * sizeof(int));
    M = malloc(m * sizeof(int));
    arestas = createEmptyEdges(e);
    leServidores(file, S, s);
    leClientes(file, C, c);
    leMonitores(file, M, m);
    leArestas(file, arestas, e);

}

// void leArquivo(FILE* file,int *S, int *C, int *M){
//   int v,e,s,c,m;
//   fscanf(file,"%i %i",v,e);
//   fscanf(file,"%i %i %i",s,c,m);
// }
