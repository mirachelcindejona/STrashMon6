#ifndef TRASH_HISTORY_STACK_H
#define TRASH_HISTORY_STACK_H

#include <string>
using namespace std;

const int kapasitas = 5;
const int maxLokasi = 10; // termasuk kantor dan tempat sampah

struct HistoriData {
    string waktu;
    string tanggal;
    float level;
    string status;
};

struct HistoriStack {
    int top;
    HistoriData data[kapasitas];
};

extern HistoriStack historiList[maxLokasi];

void createHistori();
void pushHistori(int index, HistoriData newData);
void displayHistori(int index);
string getCurrentTime();
string getCurrentDate();

#endif