#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../lib/in_out.h"
#include "../lib/rtt.h"

#define DEBUG_PRINT     (1)

int main(int argc, char** argv) {
    //definição da maioria das variaveis
    char* inFileName = argv[1];
    char* outFileName = argv[2];
    unsigned int Nserver, Nclient, Nmonitor, Ntotal, *serverIds, *clientIds, *monitorIds;

    clock_t tallyRead = clock();
    vertex_t** vertices = readFile(inFileName, &Nserver, &Nclient, &Nmonitor, &Ntotal, &serverIds, &clientIds, &monitorIds);
    tallyRead = clock() - tallyRead;
    printf("Reading took\t%.6lfs\n", (double) tallyRead / CLOCKS_PER_SEC);

    unsigned int Nlines = Nserver * Nclient;
    OutType outTArray[Nlines];

    clock_t tallyRTT = clock();
    for (unsigned int s = 0, outCount = 0; s < Nserver; s++) {
        for (unsigned int c = 0; c < Nclient; c++, outCount++) {
            double rttstar = RTTmegaBlasted(vertices, Ntotal, serverIds[s], clientIds[c], monitorIds, Nserver, Nclient, Nmonitor);
            double rtttrue = RTT(vertices, Ntotal, serverIds[s], clientIds[c]);
            outTArray[outCount] = createOutType(serverIds[s], clientIds[c], (rttstar / rtttrue));
        }
    }
    tallyRTT = clock() - tallyRTT;
    printf("RTT calc took\t%.6lfs\n", (double) tallyRTT / CLOCKS_PER_SEC);

    // Aqui é o ponto crítico, onde o programa tem mais memória reservada. Ambos o outTarray precisou ser mantido ao mesmo tempo que o VertexList para os cálculos

    clock_t tallyFree = clock();
    destroyVertexList(vertices, Ntotal);
    free(serverIds);
    free(clientIds);
    free(monitorIds);
    tallyRead = clock() - tallyRead;
    printf("Freeing took\t%.6lfs\n", (double) tallyRead / CLOCKS_PER_SEC);

    clock_t tallyOut = clock();
    writeFile(outFileName, outTArray, Nlines);
    tallyOut = clock() - tallyOut;
    printf("Writing took\t%.6lfs\n", (double) tallyOut / CLOCKS_PER_SEC);

    printf("------------\nTotal:\t\t%.6lfs\n", (double) (tallyRead + tallyRTT + tallyFree + tallyOut) / CLOCKS_PER_SEC);

    return 0;
}
