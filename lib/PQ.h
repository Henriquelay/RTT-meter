#ifndef PQ_H
#define PQ_H

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

// TODO Make into a list
#define EDGESIZE (500)

typedef struct Item_Vertex {
    unsigned int id;
    // TODO - make it a dynamic list
    float weight[EDGESIZE];
    unsigned int to[EDGESIZE];
    unsigned int size;
    float dist;
} Item_Vertex;

typedef struct PQ {
    unsigned int size;
    Item_Vertex** vertex;
    unsigned int* map;
} PQ;

#define id(A)           (A->id)                         // retorna identificador do nó */
#define value(A)        (A->dist)                       // retorna valor do nó */
#define to(A)           (A->to)                         // retorna id do nó destino */
#define more(A, B)      (value(A) > value(B))           // compara nós, por valor */

Item_Vertex make_item(unsigned int id);
void print_item(Item_Vertex* item);
Item_Vertex* init_item(unsigned int id);
void swap(PQ* pq, unsigned int i, unsigned int j);
void fix_up(PQ* pq, unsigned int k);
void fix_down(PQ* pq, unsigned int parent);
PQ* PQ_init(unsigned int maxSize);
void PQ_print(PQ* pq);
void PQ_insert(PQ* pq, Item_Vertex* v);
Item_Vertex* PQ_min(PQ* pq);
Item_Vertex* PQ_delmin(PQ* pq);
void PQ_decrease_key(PQ* pq, unsigned int id, unsigned int value);
char PQ_empty(PQ* pq);
char PQ_exists(PQ* pq, unsigned int key);
char PQ_existsAddr(PQ* pq, void* keyAddr);
unsigned int PQ_size(PQ* pq);
// Frees the Items inside too
void PQ_finish(PQ* pq);


#endif
