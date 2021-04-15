#ifndef RTT_H_
#define RTT_H_

#include "PQ.h"

double RTT(vertex_t* vertices[], unsigned int nVert, unsigned int from, unsigned int to);
double RTTmegaBlasted(vertex_t* vertices[], unsigned int nVert, unsigned int server, unsigned int client, unsigned int monitor[], unsigned int serverCount, unsigned int clientCount, unsigned int monitorCount);

#endif
