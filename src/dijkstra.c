#include "../lib/dijkstra.h"

void dijkstra(vertex_t* startingVertex[], unsigned int nVert, unsigned int starting) {
    // If starting node has no edges
    // Will be useful quitting early to not allocate anything
    if (!startingVertex[starting]) {
        return;
    }
    startingVertex[starting]->dist = 0;

    // printf("Starts at: %u\n", starting);

    // Ditance array to keep track of distances from graph[starting] to graph[n]
    // To mark visited nodes
    // Internal Dijkstra's control
    PQ* dijVertex = PQ_init(nVert);

    // Inserting all vertices
    unsigned int i;
    for (i = 0; i < nVert; i++) {
        PQ_insert(dijVertex, startingVertex[i]);
    }

    puts("\nAfter starting everything, before dijkstra:");
    PQ_print(dijVertex);

    while (!PQ_empty(dijVertex)) {
        // puts("Current state:");
        // PQ_print(dijVertex);
        vertex_t* vertex = PQ_delmin(dijVertex);
        // puts("After delmin:");
        // PQ_print(dijVertex);
        printf("Current:");
        print_vertex(vertex);
        // printf("\nDistances:[");
        // for (unsigned int k = 0; k < nVert; k++) {
        //     printf("%u ", value(startingVertex[k]));
        // }
        // puts("]");
        for (linked_node_t* edgeNode = vertex->edgeList->head; edgeNode != NULL; edgeNode = edgeNode->next) {
            edge_t *edge = edgeNode->value;
            double distance = value(vertex) + edge->weight;
            printf("\ndistancia porra: %lf",distance);
            printf("\n value porra: %lf de: %d\n",value(dijVertex->vertex[dijVertex->map[edge->idTo]]),dijVertex->vertex[dijVertex->map[edge->idTo]]->id);
            // printf("Distance from %u to %u (%u) + (%u) = %u\n", id(vertex), to(vertex)[i], value(vertex), vertex->weight[i], distance);
            if (distance < value(dijVertex->vertex[dijVertex->map[edge->idTo]])) {
                puts("Updating distance");
                printf("From %lf ", value(vertex));
                PQ_decrease_key(dijVertex, edge->idTo, distance);
                printf("to %lf\n", value(vertex));
            }
        }
        printf("NewDistances:[");
        for (unsigned int k = 0; k < nVert; k++) {
            printf("%lf ", value(startingVertex[k]));
        }
        puts("]");

        // puts("");
    }


    free(dijVertex->vertex);
    free(dijVertex->map);
    free(dijVertex);
}
