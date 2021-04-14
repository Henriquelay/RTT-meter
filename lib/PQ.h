#ifndef PQ_H
#define PQ_H

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "list.h"

typedef struct struct_edge_t {
    // unsigned int idFrom;
    unsigned int idTo;                  // identificador do nó
    double weight;                      // valor associado ao nó;
} edge_t;

typedef struct struct_Item_Vertex {
    unsigned int id;
    unsigned int size;
    double dist;
    char type;
    list_t *edgeList;
} vertex_t;

typedef struct struct_PQ {
    unsigned int size;
    vertex_t** vertex;
    unsigned int* map;
} PQ;

#define id(A)           (A->id)                         // retorna identificador do nó
#define value(A)        (A->dist)                       // retorna distância do nó
#define to(A)           (A->to)                         // retorna id do nó destino
#define more(A, B)      (value(A) > value(B))           // compara nós, por valor */

edge_t* init_edge(unsigned int to, double weight);
vertex_t make_item(unsigned int id);
void print_vertex(vertex_t* item);
vertex_t* init_vertex(unsigned int id);
void swap(PQ* pq, unsigned int i, unsigned int j);
void fix_up(PQ* pq, unsigned int k);
void fix_down(PQ* pq, unsigned int parent);
PQ* PQ_init(unsigned int maxSize);
void PQ_print(PQ* pq);
void PQ_insert(PQ* pq, vertex_t* v);
vertex_t* PQ_min(PQ* pq);
vertex_t* PQ_delmin(PQ* pq);
void PQ_decrease_key(PQ* pq, unsigned int id, unsigned int value);
char PQ_empty(PQ* pq);
char PQ_exists(PQ* pq, unsigned int key);
char PQ_existsAddr(PQ* pq, void* keyAddr);
unsigned int PQ_size(PQ* pq);
// Frees the Items inside too
void PQ_finish(PQ* pq);


#endif
