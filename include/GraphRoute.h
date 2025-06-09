#ifndef GRAPH_ROUTE_H
#define GRAPH_ROUTE_H

#include <string>
using namespace std;

const int jumlahNode = 10;
const int TIDAK_TERHUBUNG = 0;

extern int jarak[jumlahNode][jumlahNode];
extern string namaTempat[jumlahNode];
extern bool sudahInput;

void createGraph();
void inputGraph();
void tampilkanGraph();
void shortestPath(int awal, int akhir);
void simpanGraphKeFile();
void bacaGraphDariFile();
void ruteKelilingPickup();

#endif
