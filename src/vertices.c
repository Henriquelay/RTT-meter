#include"../lib/vertices.h"

vertice* criaVerticesVazios(int e){
  vertice* novo = malloc(e*sizeof(vertice));
  for(int i=0;i<e;i++){
    novo[i].idA=0;
    novo[i].idB=0;
    novo[i].weight=0;
  }
  return novo;
}