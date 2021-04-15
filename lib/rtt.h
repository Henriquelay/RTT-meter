#ifndef RTT_H_
#define RTT_H_

#include "PQ.h"

double RTTstarOverRTT(vertex_t* vertices[], unsigned int nVert, unsigned int server, unsigned int client, unsigned int monitor[], unsigned int serverCount, unsigned int clientCount, unsigned int monitorCount, double** serverDists, double** clientDists, double* monitorDists[monitorCount]);

#endif
