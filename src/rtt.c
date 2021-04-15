#include "../lib/rtt.h"

// It will update the dist value on the vertices
double* dijkstra(vertex_t* startingVertex[], unsigned int nVert, unsigned int starting) {
    // If starting node has no edges
    // Will be useful quitting early to not allocate anything
    // Removed because documentation assumes a well-behabed input where there's no unreacheable vertex
    // if (!startingVertex[starting]) {
    //     return;
    // }

    // printf("Starts at: %u\n", starting);

    // Ditance array to keep track of distances from graph[starting] to graph[n]
    // To mark visited nodes
    // Internal Dijkstra's control
    PQ* dijVertex = PQ_init(nVert);

    // Inserting all vertices
    for (unsigned int i = 0; i < nVert; i++) {
        value(startingVertex[i]) = INFINITY;
        PQ_insert(dijVertex, startingVertex[i]);
    }
    // Setting starting distance to 0
    PQ_decrease_key(dijVertex, starting, 0);

    while (!PQ_empty(dijVertex)) {
        vertex_t* vertex = PQ_delmin(dijVertex);
        for (linked_node_t* edgeNode = vertex->edgeList->head; edgeNode != NULL; edgeNode = edgeNode->next) {
            edge_t* edge = edgeNode->value;
            double distance = value(vertex) + edge->weight;
            if (distance < value(dijVertex->vertex[dijVertex->map[edge->idTo]])) {
                PQ_decrease_key(dijVertex, edge->idTo, distance);
            }
        }
    }

    free(dijVertex->vertex);
    free(dijVertex->map);
    free(dijVertex);

    // Exporting distances because next dijkstra wourld overwrite it
    double* distances = malloc(sizeof * distances * nVert);
    if (distances == NULL) {
        perror("Failed to alloc distances array after dijkstra");
        exit(EXIT_FAILURE);
    }
    for (unsigned int i = 0; i < nVert; i++) {
        distances[i] = startingVertex[i]->dist;
    }
    return distances;
}

/*
 * dists are a allocated array of double, of nVertsize.
*/
double RTTstarOverRTT(vertex_t* vertices[], unsigned int nVert, unsigned int server, unsigned int client, unsigned int monitor[], unsigned int serverCount, unsigned int clientCount, unsigned int monitorCount, double** serverDists, double** clientDists, double* monitorDists[monitorCount]) {
    double minRTTstar = INFINITY;
    // Checks if dijkstra has been run on this server. If not, run it. Same for others
    // printf("serverDists=%p\n", (void*)serverDists);
    // printf("*serverDists=%p\n",(void*) *serverDists);
    if (*serverDists == NULL) {
        printf("Fazendo novo serverDist em s=%u e c=%u\n", server, client);
        *serverDists = dijkstra(vertices, nVert, server);
    }
    if (*clientDists == NULL) {
        printf("Fazendo novo clientDist em s=%u e c=%u\n", server, client);
        *clientDists = dijkstra(vertices, nVert, client);
    }

    double rttTrue = (*serverDists)[client] + (*clientDists)[server];

    for (unsigned int m = 0; m < monitorCount; m++) {
        if (monitorDists[m] == NULL) {
        printf("Fazendo novo monitorDist em s=%u e c=%u m=%u\n", server, client, monitor[m]);
            monitorDists[m] = dijkstra(vertices, nVert, monitor[m]);
        }
        double rttStar = (*serverDists)[monitor[m]] + monitorDists[m][server] +
                        monitorDists[m][client] + (*clientDists)[monitor[m]];
        if (rttStar < minRTTstar && rttStar != 0) {
            minRTTstar = rttStar;
        }
    }
    return minRTTstar / rttTrue;
}
