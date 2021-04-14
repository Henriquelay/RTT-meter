#include "dijkstra.h"

void dijkstra(Item_Vertex* startingVertex[], unsigned int nVert, unsigned int starting, unsigned int target) {
    /* If starting node has no edges */
    /* Will be useful quitting early to not allocate anything */
    if (!startingVertex[starting]) {
        return;
    }
    startingVertex[starting]->dist = 0;
    if(starting == target) {
        return;
    }

    /* printf("Starts at: %u\n", starting); */

    /* Ditance array to keep track of distances from graph[starting] to graph[n] */
    /* unsigned int* distances = malloc(sizeof * distances * nVert); */
    /* To mark visited nodes */
    /* char visited[nVert]; */
    /* Internal Dijkstra's control */
    PQ* dijVertex = PQ_init(EDGESIZE);

    /* Inserting all vertices */
    unsigned int i;
    for (i = 0; i < nVert; i++) {
        PQ_insert(dijVertex, startingVertex[i]);
    }
    /* Inserting only starting node */
    /* for (i = 0; i < nVert; i++) {
        /* Initializes with maximum distance, gets replaced on first iteration 

        distances[i] = UINT_MAX;
        visited[i] = 0;
    } */
    /* A vertice's distance to itself is 0. */
    /* distances[starting] = 0; */



    /* puts("\nAfter starting everything, before dijkstra:");
    PQ_print(dijEdges); */

    while (!PQ_empty(dijVertex)) {
        /* puts("Current state:");
        PQ_print(dijVertex); */
        Item_Vertex* vertex = PQ_delmin(dijVertex);
        /* puts("After delmin:");
        PQ_print(dijVertex);
        printf("Current:");
        print_item(vertex);
        printf("\nDistances:[");
        unsigned int k;
        for (k = 0; k < nVert; k++) {
            printf("%u ", value(startingVertex[k]));
        }
        puts("]"); */
        for (i = 0; i < vertex->size; i++) {
            unsigned int distance = value(vertex) + vertex->weight[i];
            /* printf("Distance from %u to %u (%u) + (%u) = %u\n", id(vertex), to(vertex)[i], value(vertex), vertex->weight[i], distance); */
            if (distance < value(dijVertex->vertex[dijVertex->map[to(vertex)[i]]])) {
                /* puts("Updating distance"); */
                PQ_decrease_key(dijVertex, to(vertex)[i], distance);
            }
        }
        /* unsigned int k; */
        /* printf("NewDistances:[");
        for (k = 0; k < nVert; k++) {
            printf("%u ", value(startingVertex[k]));
        }
        puts("]"); */

        /* visited[id(edge)] = 1; */
        /* puts(""); */
    }


    free(dijVertex->vertex);
    free(dijVertex->map);
    free(dijVertex);
}
