#ifndef PQ_H
#define PQ_H

#include <limits.h>
#include <stdlib.h>

// Make into a list
#define EDGESIZE (500)

#define id(A)           (A->id)                         /* retorna identificador do nó */
#define value(A)        (A->dist)                       /* retorna valor do nó */
#define to(A)           (A->to)                         /* retorna id do nó destino */
#define more(A, B)      (value(A) > value(B))           /* compara nós, por valor */
void exch(Item_Vertex** a, Item_Vertex** b) {
    Item_Vertex* T = *a;
    *a = *b;
    *b = T;
}

typedef struct Item_Vertex {
    unsigned int id;
    /* TODO - make it a dynamic list */
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


Item_Vertex make_item(unsigned int id) {
    Item_Vertex t;
    t.id = id;
    t.size = 0;
    unsigned int i;
    for (i = 0; i < EDGESIZE; i++) {
        t.to[i] = __DBL_MAX__;
        t.weight[i] = __DBL_MAX__;
    }
    t.dist = __DBL_MAX__;
    return t;
}

void print_item(Item_Vertex* item) {
    if (!item) { printf("NULL\n"); return; }
    printf("[Vertex %u] dist = (%u)\n", id(item), value(item));
    unsigned int i;
    for (i = 0; i < item->size; i++) {
        printf("%u--", id(item));
        printf("%u", item->weight[i]);
        printf("->%u\n", to(item)[i]);
    }
}

Item_Vertex* init_item(unsigned int id) {
    Item_Vertex* newItem = malloc(sizeof * newItem);
    *newItem = make_item(id);
    return newItem;
}

void swap(PQ* pq, unsigned int i, unsigned int j) {
    exch(&pq->vertex[i], &pq->vertex[j]);
    pq->map[id(pq->vertex[i])] = i;
    pq->map[id(pq->vertex[j])] = j;
}

void fix_up(PQ* pq, unsigned int k) {
    while (k > 1 && more(pq->vertex[k / 2], pq->vertex[k])) {
        swap(pq, k, k / 2);
        k = k / 2;
    }
}

void fix_down(PQ* pq, unsigned int parent) {
    while (2 * parent <= pq->size) {
        unsigned int child = 2 * parent;
        /* child < pq->size checks if there's a position after child, since PQ starts at 1; */
        if (child < pq->size && more(pq->vertex[child], pq->vertex[child + 1])) {
            child++;
        }
        if (!more(pq->vertex[parent], pq->vertex[child])) {
            break;
        }
        swap(pq, parent, child);
        parent = child;
    }
}

PQ* PQ_init(unsigned int maxSize) {
    PQ* pq = malloc(sizeof * pq);
    pq->vertex = malloc(sizeof * pq->vertex * (maxSize + 1));
    pq->vertex[0] = NULL;
    pq->map = malloc(sizeof * pq->map * (maxSize + 1));
    pq->size = 0;
    return pq;
}

void PQ_print(PQ* pq) {
    if (pq == NULL) {
        puts("It's NULL");
        return;
    }
    printf("PQ=%p map=%p size=%u\n", (void*)pq->vertex, (void*)pq->map, pq->size);
    /* This implementation skips index 0 */
    unsigned int i;
    for (i = 0; i <= pq->size; i++) {
        printf("[%u] ", i);
        print_item(pq->vertex[i]);
    }
}

void PQ_insert(PQ* pq, Item_Vertex* v) {
    pq->size++;
    pq->vertex[pq->size] = v;
    pq->map[id(v)] = pq->size;
    fix_up(pq, pq->size);
}

Item_Vertex* PQ_min(PQ* pq) {
    return pq->vertex[1];
}

Item_Vertex* PQ_delmin(PQ* pq) {
    Item_Vertex* min = PQ_min(pq);
    swap(pq, 1, pq->size);
    pq->size--;
    fix_down(pq, 1);
    return min;
}

void PQ_decrease_key(PQ* pq, unsigned int id, unsigned int value) {
    unsigned int i = pq->map[id];
    value(pq->vertex[i]) = value;
    /* printf("Novo valor %u\n", value(pq->vertex[i])); */
    fix_up(pq, i);
}

char PQ_empty(PQ* pq) {
    return pq->size == 0;
}

char PQ_exists(PQ* pq, unsigned int key) {
    unsigned int i;
    for (i = 1; i <= pq->size; i++) {
        if (id(pq->vertex[i]) == key) return 1;
    }
    return 0;
}

char PQ_existsAddr(PQ* pq, void* keyAddr) {
    unsigned int i;
    for (i = 0; i < pq->size; i++) {
        if (&(pq->vertex[i]) == keyAddr) return 1;
    }
    return 0;
}

unsigned int PQ_size(PQ* pq) {
    return pq->size;
}

/* Frees the Items inside too */
void PQ_finish(PQ* pq) {
    if (pq == NULL) return;
    unsigned int i;
    for (i = 1; i <= pq->size; i++) {
        free(pq->vertex[i]);
    }
    free(pq->vertex);
    free(pq->map);
    free(pq);
    pq = NULL;
}


#endif
