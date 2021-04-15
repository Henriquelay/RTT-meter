#include <stdio.h>
#include <stdlib.h>
#include "../lib/input.h"
#include "../lib/dijkstra.h"

#define DEBUG_PRINT     (1)

int main(int argc, char** argv) {
    //definição da maioria das variaveis
    char* fileName = argv[1];
    unsigned int Nserver, Nclient, Nmonitor, Ntotal, *serverIds, *clientIds, *monitorIds;
    vertex_t **vertices = readFile(fileName, &Nserver, &Nclient, &Nmonitor, &Ntotal, &serverIds, &clientIds, &monitorIds);
    // if(DEBUG_PRINT) {
    //     print_all_vertices(vertices, Ntotal, Nserver, Nclient, Nmonitor, serverIds, clientIds, monitorIds);
    // }

    puts("RODANTE DE DIJKSTRA");
    dijkstra(vertices, Ntotal, 5);


    if(DEBUG_PRINT) {
        print_all_vertices(vertices, Ntotal, Nserver, Nclient, Nmonitor, serverIds, clientIds, monitorIds);
    }
}
