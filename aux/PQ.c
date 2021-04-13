#include <stdio.h>
#include <stdlib.h>
#include "PQ.h"

// static Item *pq;
// static int *map;
// static int N;

void swap(int i, int j, Item *pq, int *map) {
    exch(pq[i], pq[j]);
    map[id(pq[i])] = i;
    map[id(pq[j])] = j;
}

void fix_up(Item *a, int k, int *map) {
    while (k > 1 && more(a[k/2], a[k])) {
        swap(k, k/2,a,map);
        k = k/2;
    }
}

void fix_down(Item *a, int sz, int k, int *map){
  while (2*k <= sz) {
    int j = 2*k;
    if (j < sz && more(a[j], a[j+1])){
      j++;
    }
    if (!more(a[k], a[j])) {
      break;
    }
    swap(k, j,a, map);
    k = j;
  }
}

Item* PQ_init(int maxN) {
    Item *pq = (Item *) malloc((maxN+1) * sizeof (Item));
    // map = (int *) malloc((maxN+1) * sizeof (int));
    // N = 0;
    //tem q fazer isso na main
    return pq;
}

void PQ_insert(Item **pq, int id, double value, int *map, int N) {
    N++;
    pq[N]->id = id;
    pq[N]->value = value;
    map[pq[N]->id] = N;
    fix_up(pq, N, map);
}

Item PQ_delmin() {
    Item min = pq[1];
    swap(1, N);
    N--;
    fix_down(pq, N, 1);
    return min;
}

Item PQ_min() {
    return pq[1];
}

void PQ_decrease_key(int id, double value) {
    int i = map[id];
    value(pq[i]) = value;
    fix_up(pq, i);
}

bool PQ_empty() {
    return N == 0;
}

int  PQ_size() {
    return N;
}

void PQ_finish() {
    free(pq);
    free(map);
}


