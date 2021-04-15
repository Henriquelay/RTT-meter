#include "../lib/in_out.h"

void destroyVertex(vertex_t* vertex) {
    list_destroy(vertex->edgeList);
    free(vertex);
}

void destroyVertexList(vertex_t** Vertices, unsigned int nVertices) {
    for (unsigned int i = 0; i < nVertices; i++) {
        destroyVertex(Vertices[i]);
    }
    free(Vertices);
}

unsigned int* readVertexList(FILE* file, vertex_t** V, unsigned int count) {
    unsigned int* idArray = malloc(sizeof * idArray * count);
    for (unsigned int i = 0; i < count; i++) {
        unsigned int Vid;
        if (fscanf(file, "%u", &Vid) == -1) {
            perror("Error reading from file");
            exit(EXIT_FAILURE);
        };
        idArray[i] = Vid;
    }
    return idArray;
}

void leArestas(FILE* file, vertex_t** Vertices, unsigned int edgesCount) {
    for (unsigned int i = 0; i < edgesCount; i++) {
        unsigned int from, to;
        double weight;
        if (fscanf(file, "%u %u %lf", &from, &to, &weight) == -1) {
            perror("Error reading from file");
            exit(EXIT_FAILURE);
        };
        if (Vertices[from]->edgeList == NULL) {
            Vertices[from]->edgeList = list_init();
        }
        // printf("Pushing -(%.15lf)->%u to %u's edgelist\n", weight, to, from);
        list_push(Vertices[from]->edgeList, init_edge(from, to, weight));
    }
}

vertex_t** readFile(char* fileName, unsigned int* sCount, unsigned int* cCount, unsigned int* mCount, unsigned int* total, unsigned int** sArray, unsigned int** cArray, unsigned int** mArray) {
    FILE* file = fopen(fileName, "r");
    if (!file) {
        perror("Falha ao abrir o arquivo de entrada");
        exit(EXIT_FAILURE);
    }
    unsigned int e;
    if (fscanf(file, "%u %u", total, &e) == -1) {
        perror("Error reading from file");
        exit(EXIT_FAILURE);
    };
    if (fscanf(file, "%u %u %u", sCount, cCount, mCount) == -1) {
        perror("Error reading from file");
        exit(EXIT_FAILURE);
    };

    vertex_t** Vertices = malloc(sizeof * Vertices * (*total));
    // This will create vertices

    for (unsigned int i = 0; i < *total; i++) {
        Vertices[i] = init_vertex(i);
    }
    *sArray = readVertexList(file, Vertices, *sCount);
    *cArray = readVertexList(file, Vertices, *cCount);
    *mArray = readVertexList(file, Vertices, *mCount);

    leArestas(file, Vertices, e);

    fclose(file);

    return Vertices;
}

OutType createOutType(unsigned int serverId, unsigned int clientId, double inflRTT) {
    // OutType* new = (OutType*)malloc(sizeof(OutType));
    OutType new;
    new.clientId = clientId;
    new.serverId = serverId;
    new.inflRTT = inflRTT;
    return new;
}

int comparator(const void* p, const void* q) {
    double x = ((OutType*)p)->inflRTT;
    double y = ((OutType*)q)->inflRTT;
    if (x > y)
        return 1;
    if (x < y)
        return -1;
    return 0;
}

void writeFile(char* fileName, OutType* outTArray, unsigned int Nlines) {
    FILE* file = fopen(fileName, "w");
    if (!file) {
        perror("Falha ao abrir o arquivo de saida");
        exit(EXIT_FAILURE);
    }
    qsort(outTArray, Nlines, sizeof * outTArray, comparator);
    for (int i = 0; i < Nlines; i++) {
        OutType outT = outTArray[i];
        fprintf(file, "%u %u %.15lf\n", outT.serverId, outT.clientId, outT.inflRTT);
    }
    fclose(file);
}
