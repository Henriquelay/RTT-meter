#include<stdio.h>
#include<stdlib.h>
#include"../lib/input.h"

#define DEBUG_PRINT     (1)

int main(int argc, char** argv) {
    //definição da maioria das variaveis
    char* fileName = argv[1];
    unsigned int Nserver, Nclient, Nmonitor, Ntotal, *serverIds, *clientIds, *monitorIds;
    vertex_t **vertices = readFile(fileName, &Nserver, &Nclient, &Nmonitor, &Ntotal, &serverIds, &clientIds, &monitorIds);
    if(DEBUG_PRINT) {
        puts("Inserted vertices:");
        for (unsigned int i = 0; i < Ntotal; i++) {
            print_vertex(vertices[i]);
        }
        printf("Servers:\t[");
        for (unsigned int i = 0; i < Nserver; i++) {
            printf("%u ", serverIds[i]);
        }
        printf("]\nClients:\t[");
        for (unsigned int i = 0; i < Nclient; i++) {
            printf("%u ", clientIds[i]);
        }
        printf("]\nMonitors:\t[");
        for (unsigned int i = 0; i < Nmonitor; i++) {
            printf("%u ", monitorIds[i]);
        }
        printf("]\n");
    }
}
