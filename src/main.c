#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../lib/in_out.h"
#include "../lib/rtt.h"

#define DEBUG_PRINT     (0)

int main(int argc, char** argv) {
    //definição da maioria das variaveis
    char* inFileName = argv[1];
    char* outFileName = argv[2];
    unsigned int Nserver, Nclient, Nmonitor, Ntotal, *serverIds, *clientIds, *monitorIds;

    clock_t tallyRead = clock();
    vertex_t** vertices = readFile(inFileName, &Nserver, &Nclient, &Nmonitor, &Ntotal, &serverIds, &clientIds, &monitorIds);
    tallyRead = clock() - tallyRead;
    if (DEBUG_PRINT) printf("Reading took\t%.6lfs\n", (double) tallyRead / CLOCKS_PER_SEC);

    unsigned int Nlines = Nserver * Nclient;
    OutType outTArray[Nlines];

    double *serverDists[Nserver], *clientDists[Nclient], *monitorDists[Nmonitor];

    for (unsigned int m = 0; m < Nmonitor; m++) {
        monitorDists[m] = NULL;
    }
    for (unsigned int c = 0; c < Nclient; c++) {
        clientDists[c] = NULL;
    }

    clock_t tallyRTT = clock();
    for (unsigned int s = 0, outCount = 0; s < Nserver; s++) {
        serverDists[s] = NULL;
        for (unsigned int c = 0; c < Nclient; c++, outCount++) {
            double RTTfinal = RTTstarOverRTT(vertices, Ntotal, serverIds[s], clientIds[c], monitorIds, Nserver, Nclient, Nmonitor, &(serverDists[s]), &(clientDists[c]), monitorDists);
            outTArray[outCount] = createOutType(serverIds[s], clientIds[c], RTTfinal);
            // printf("RTT: %.15lf\n", RTTfinal);
        }
    }
    tallyRTT = clock() - tallyRTT;
    if (DEBUG_PRINT) printf("RTT calc took\t%.6lfs\n", (double) tallyRTT / CLOCKS_PER_SEC);

    // Aqui é o ponto crítico, onde o programa tem mais memória reservada. Ambos o outTarray precisou ser mantido ao mesmo tempo que o VertexList para os cálculos

    clock_t tallyFree = clock();
    destroyVertexList(vertices, Ntotal);
    free(serverIds);
    free(clientIds);
    free(monitorIds);
    for (unsigned int s = 0; s < Nserver; s++) {
        free(serverDists[s]);
    }
    for (unsigned int c = 0; c < Nclient; c++) {
        free(clientDists[c]);
    }
    for (unsigned int m = 0; m < Nmonitor; m++) {
        free(monitorDists[m]);
    }
    tallyFree = clock() - tallyFree;
    if (DEBUG_PRINT) printf("Freeing took\t%.6lfs\n", (double) tallyFree / CLOCKS_PER_SEC);

    clock_t tallyOut = clock();
    writeFile(outFileName, outTArray, Nlines);
    tallyOut = clock() - tallyOut;
    if (DEBUG_PRINT) printf("Writing took\t%.6lfs\n", (double) tallyOut / CLOCKS_PER_SEC);

    if (DEBUG_PRINT) printf("------------\nTotal:\t\t%.6lfs\n", (double) (tallyRead + tallyRTT + tallyFree + tallyOut) / CLOCKS_PER_SEC);

    return 0;
}
