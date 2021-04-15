#include <stdio.h>
#include <stdlib.h>
#include "../lib/input.h"
#include "../lib/rtt.h"

#define DEBUG_PRINT     (1)

int main(int argc, char** argv) {
    //definição da maioria das variaveis
    char* fileName = argv[1];
    unsigned int Nserver, Nclient, Nmonitor, Ntotal, * serverIds, * clientIds, * monitorIds;
    vertex_t** vertices = readFile(fileName, &Nserver, &Nclient, &Nmonitor, &Ntotal, &serverIds, &clientIds, &monitorIds);

    for (unsigned int s = 0; s < Nserver; s++) {
        for (unsigned int c = 0; c < Nclient; c++) {
            double rttstar = RTTmegaBlasted(vertices, Ntotal, serverIds[s], clientIds[c], monitorIds, Nserver, Nclient, Nmonitor);
            double rtttrue = RTT(vertices, Ntotal, serverIds[s], clientIds[c]);
            printf("RTT* from %u to %u = %lf\n", serverIds[s], clientIds[c], rttstar/rtttrue);
        }
    }

}
