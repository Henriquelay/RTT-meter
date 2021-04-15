#include "../lib/PQ.h"

void exch(vertex_t** a, vertex_t** b) {
    vertex_t* T = *a;
    *a = *b;
    *b = T;
}

edge_t* init_edge(unsigned int to, double weight) {
    edge_t* edge = malloc(sizeof * edge);
    if (edge == NULL) {
        perror("Error allocating for new edge");
        exit(EXIT_FAILURE);
    }
    edge->idTo = to;
    edge->weight = weight;
    return edge;
}

void print_vertex_callback(void* edge) {
    printf("\t-(%f)->%u\n", ((edge_t*)edge)->weight, ((edge_t*)edge)->idTo);
}

void print_vertex(vertex_t* vertex) {
    if (!vertex) { printf("NULL\n"); return; }
    printf("[Vertex %u] dist = (%f)\n", id(vertex), value(vertex));
    if (!vertex->edgeList) {
        printf("\tNo edges.\n");
    } else {
        list_runOnAll(vertex->edgeList, print_vertex_callback);
    }
}

void print_all_vertices(vertex_t** vertices, unsigned int Ntotal, unsigned int Nserver, unsigned int Nclient, unsigned int Nmonitor, unsigned int* serverIds, unsigned int* clientIds, unsigned int* monitorIds) {
    puts("Inserted vertices:");
    for (unsigned int i = 0; i < Ntotal; i++) {
        print_vertex(vertices[i]);
    }
    printf("Servers:\t[");
    for (unsigned int i = 0; i < Nserver; i++) {
        printf("%u ", serverIds[i]);
    }
    printf("]\nClients:\t[");
    for (unsigned int i = 0; i < Nclient; i++) {
        printf("%u ", clientIds[i]);
    }
    printf("]\nMonitors:\t[");
    for (unsigned int i = 0; i < Nmonitor; i++) {
        printf("%u ", monitorIds[i]);
    }
    printf("]\n");
}

vertex_t* init_vertex(unsigned int id) {
    vertex_t* newItem = malloc(sizeof * newItem);
    newItem->id = id;
    newItem->size = 0;
    newItem->edgeList = NULL;
    newItem->dist = INFINITY;
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
        // child < pq->size checks if there's a position after child, since PQ starts at 1;
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
    // This implementation skips index 0
    unsigned int i;
    for (i = 0; i <= pq->size; i++) {
        printf("[%u] ", i);
        print_vertex(pq->vertex[i]);
    }
}

void PQ_insert(PQ* pq, vertex_t* v) {
    pq->size++;
    pq->vertex[pq->size] = v;
    pq->map[id(v)] = pq->size;
    fix_up(pq, pq->size);
}

vertex_t* PQ_min(PQ* pq) {
    return pq->vertex[1];
}

vertex_t* PQ_delmin(PQ* pq) {
    vertex_t* min = PQ_min(pq);
    swap(pq, 1, pq->size);
    pq->size--;
    fix_down(pq, 1);
    return min;
}

void PQ_decrease_key(PQ* pq, unsigned int id, double value) {
    unsigned int i = pq->map[id];
    value(pq->vertex[i]) = value;
    // printf("Novo valor %u\n", value(pq->vertex[i]));
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

// Frees the Items inside too
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
