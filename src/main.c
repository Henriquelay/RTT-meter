#include<stdio.h>
#include<stdlib.h>
#include"../lib/input.h"

#define DEBUG_PRINT     (1)

int main(int argc, char** argv) {
    //definição da maioria das variaveis
    char* fileName = argv[1];
    unsigned int Nserver, Nclient, Nmonitor, Ntotal;
    vertex_t **vertices = readFile(fileName, Nserver, Nclient, Nmonitor, Ntotal);
    if(DEBUG_PRINT) {
        puts("Inserted vertices:");
        for (unsigned int i = 0; i < Ntotal; i++) {
            print_vertex(vertices[i]);
        }
    }
}
