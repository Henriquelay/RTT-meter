#include"../lib/arestas.h"

aresta* criaArestasVazias(int e){
  aresta* novo = malloc(e*sizeof(aresta));
  for(int i=0;i<e;i++){
    novo[i].idA=0;
    novo[i].idB=0;
    novo[i].weight=0;
  }
  return novo;
}