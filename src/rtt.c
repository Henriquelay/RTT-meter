#include "../lib/rtt.h"

// It will update the dist value on the vertices
void dijkstra(vertex_t* startingVertex[], unsigned int nVert, unsigned int starting) {
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
}


double RTT(vertex_t* vertices[], unsigned int nVert, unsigned int from, unsigned int to) {
    dijkstra(vertices, nVert, from);
    double aTOb = value(vertices[to]);
    dijkstra(vertices, nVert, to);
    return aTOb + value(vertices[from]);
}

double RTTblasted(vertex_t* vertices[], unsigned int nVert, unsigned int server, unsigned int client, unsigned int monitor) {
    return  RTT(vertices, nVert, server, monitor) +
            RTT(vertices, nVert, monitor, client);
}

double RTTmegaBlasted(vertex_t* vertices[], unsigned int nVert, unsigned int server, unsigned int client, unsigned int monitor[], unsigned int serverCount, unsigned int clientCount, unsigned int monitorCount) {
    double minRTT = INFINITY;
    for (unsigned int m = 0; m < monitorCount; m++) {
        double rtt = RTTblasted(vertices, nVert, server, client, monitor[m]);
        if (rtt < minRTT && rtt != 0) {
            minRTT = rtt;
        }
    }
    return minRTT;
}
