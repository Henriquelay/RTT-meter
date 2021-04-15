#include <stdio.h>
#include <stdlib.h>
#include "../lib/in_out.h"
#include "../lib/rtt.h"

#define DEBUG_PRINT     (1)

int main(int argc, char** argv) {
    //definição da maioria das variaveis
    char* inFileName = argv[1];
    char* outFileName = argv[2];
    unsigned int Nserver, Nclient, Nmonitor, Ntotal, * serverIds, * clientIds, * monitorIds;
    vertex_t** vertices = readFile(inFileName, &Nserver, &Nclient, &Nmonitor, &Ntotal, &serverIds, &clientIds, &monitorIds);
    writeFile(outFileName, Nserver, Nclient, Nmonitor, Ntotal, serverIds, clientIds, monitorIds, vertices);
    return 0;
}
