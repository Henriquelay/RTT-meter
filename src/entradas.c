#include"../lib/entradas.h"

void leServidores(FILE* file,int* S, int s){
  for(int i=0;i<s;i++){
    fscanf(file,"%i",&S[i]);
  }
}

void leClientes(FILE* file,int* C,int c){
  for(int i=0;i<c;i++){
    fscanf(file,"%i",&C[i]);
  }
}

void leMonitores(FILE* file,int* M, int m){
  for(int i=0;i<m;i++){
    fscanf(file,"%i",&M[i]);
  } 
}

void leArestas(FILE* file,aresta* arestas, int e){
  for(int i=0;i<e;i++){
    int a,b;
    double w;
    fscanf(file,"%i %i %lf",&a,&b,&w);
    arestas[i].idA=a;
    arestas[i].idB=b;
    arestas[i].weight=w;
  } 
}