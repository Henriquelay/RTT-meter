#include<stdio.h>
#include<stdlib.h>
#include"../lib/entradas.h"
#include"../lib/vertices.h"
#include"../aux/item.h"
#include"PQ.h"
#include"../lib/djikistra.h"

int main(int argc, char** argv){
  //definição da maioria das variaveis
  char *fileName = argv[1];
  puts(fileName);
  FILE *file= fopen(fileName,"r");
  
  if (!file){
    fprintf(stderr, "Falha ao abrir o arquivo '%s'.\n", fileName);
    return -1;
  }
  aresta* arestas;
  int *S;
  int *C;
  int *M;
  int v,e,s,c,m;
  int *tamanhos= malloc(e*sizeof(int));
  int *map = m;

  // // leArquivo(file,S,C,M);
  fscanf(file,"%d %d",&v,&e);
  fscanf(file,"%d %d %d",&s,&c,&m);
  S= malloc(s*sizeof(int));
  C= malloc(c*sizeof(int));
  M= malloc(m*sizeof(int));
  arestas = malloc(e*sizeof(aresta));
  leServidores(file,S,s);
  leClientes(file,C,c);
  leMonitores(file,M,m);
  leArestas(file,arestas,e);
  double **distancias = malloc(e*sizeof(float*));
  for(int i=0; i<e;i++){
    distancias[i] = calloc(e,sizeof(float));
  }

  for (int i=0; i<s; i++) { // call dijkstra for N times
    distancias[S[i]] = dijkistra(); 
  }
  for (int i=0; i<c; i++) { // call dijkstra for N times
    distancias[C[i]] = dijkistra(); 
  }
  for (int i=0; i<m; i++) { // call dijkstra for N times
    distancias[M[i]] = dijkistra(); 
  }

}

// void leArquivo(FILE* file,int *S, int *C, int *M){
//   int v,e,s,c,m;
//   fscanf(file,"%i %i",v,e);
//   fscanf(file,"%i %i %i",s,c,m);
// }