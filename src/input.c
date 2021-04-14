#include "../lib/input.h"

void readVertexList(FILE* file, vertex_t** V, int s) {
    for (unsigned int i = 0; i < s; i++) {
        unsigned int id;
        if (fscanf(file, "%u", &id) == -1) {
            perror("Error reading from file");
            exit(EXIT_FAILURE);
        };
        V[i] = init_vertex(id);
    }
}

void leArestas(FILE* file, vertex_t ** Vertices, unsigned int edgesCount) {
    for (unsigned int i = 0; i < edgesCount; i++) {
        unsigned int from, to;
        double weight;
        if (fscanf(file, "%i %i %lf", &from, &to, &weight) == -1) {
            perror("Error reading from file");
            exit(EXIT_FAILURE);
        };
        list_t* edgeList = Vertices[from]->edgeList;
        if (edgeList == NULL) {
            edgeList = list_init();
        }
        list_push(edgeList, init_edge(to, weight));
    }
}

vertex_t** readFile(char* fileName, unsigned int *s, unsigned int *c, unsigned int *m, unsigned int *total) {
    FILE* file = fopen(fileName, "r");
    if (!file) {
        perror("Falha ao abrir o arquivo");
        return -1;
    }
    unsigned int e;
    if (fscanf(file, "%u %u", total, &e) == -1) {
        perror("Error reading from file");
        exit(EXIT_FAILURE);
    };
    if (fscanf(file, "%u %u %u", s, c, &m) == -1) {
        perror("Error reading from file");
        exit(EXIT_FAILURE);
    };

    vertex_t ** Vertices = malloc(sizeof * Vertices * (*total));
    // This will create vertices
    readVertexList(file, Vertices, *total);
    leArestas(file, Vertices, e);

    fclose(file);

    return Vertices;
}

