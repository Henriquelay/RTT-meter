#include<stdio.h>
#include<stdlib.h>
#include"../lib/entradas.h"
#include"../lib/vertices.h"
#include"../aux/item.h"
#include"PQ.h"

int main(int argc, char** argv){
  //definição da maioria das variaveis
  char *fileName = argv[1];
  puts(fileName);
  FILE *file= fopen(fileName,"r");
  
  if (!file){
    fprintf(stderr, "Falha ao abrir o arquivo '%s'.\n", fileName);
    return -1;
  }
  vertice* vertices;
  int *S;
  int *C;
  int *M;
  int v,e,s,c,m;
  int *tamanhos= malloc(e*sizeof(int));

  // // leArquivo(file,S,C,M);
  fscanf(file,"%d %d",&v,&e);
  fscanf(file,"%d %d %d",&s,&c,&m);
  S= malloc(s*sizeof(int));
  C= malloc(c*sizeof(int));
  M= malloc(m*sizeof(int));
  vertices = criaVerticesVazios(e);
  leServidores(file,S,s);
  leClientes(file,C,c);
  leMonitores(file,M,m);

  //maloca uma matriz de pq
  Item **A = malloc(e*sizeof(Item)+1);
  for(int i=0; i<e;i++){
    A[i] = PQ_init(e);
    tamanhos[i]=0;
  }
  leVertices(file,A,e,tamanhos);
  //maloca uma matriz de distancia
  double **distancias = malloc(e*sizeof(float*));
  for(int i=0; i<e;i++){
    distancias[i] = calloc(e,sizeof(float));
  }

  for (i=0; i<e; i++) { // call dijkstra for N times
      vertice[i] = dijkstra(A, e, i);
      // maxDist[i] = V[i][N].dist;
      // if (diameter<maxDist[i]) {
      //     diameter = maxDist[i];
      // }
  }

}

// void leArquivo(FILE* file,int *S, int *C, int *M){
//   int v,e,s,c,m;
//   fscanf(file,"%i %i",v,e);
//   fscanf(file,"%i %i %i",s,c,m);
// }