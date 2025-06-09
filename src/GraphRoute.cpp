#include "../include/GraphRoute.h"
#include "../include/SensorSimulator.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

int jarak[jumlahNode][jumlahNode];
string namaTempat[jumlahNode];
bool sudahInput = false;

void createGraph() {
   for (int i = 0; i < jumlahNode; i++) {
      for (int j = 0; j < jumlahNode; j++) {
         jarak[i][j] = (i == j) ? 0 : TIDAK_TERHUBUNG;
      }
   }
}

void tampilkanGraph() {
   cout << "\n=== DATA GRAF TEMPAT SAMPAH ===\n";
   for (int i = 0; i < jumlahNode; i++) {
      if (namaTempat[i] != "") {
         for (int j = 0; j < jumlahNode; j++) {
               if (jarak[i][j] > 0) {
                  cout << "- " << namaTempat[i] << " --> " << namaTempat[j] 
                        << " = " << jarak[i][j] << " meter\n";
               }
         }
      }
   }
}

void inputGraph() {
   bacaGraphDariFile();
   if (sudahInput) {
      cout << "\nData jarak antar lokasi sudah tersedia:\n";
      tampilkanGraph();
      return;
   }

   cout << "\nMasukkan jarak antar lokasi tempat sampah (dalam meter).";
   cout << "\nGunakan 0 jika tidak ada jalan.\n\n";
   for (int i = 0; i < jumlahNode; i++) {
      if (namaTempat[i] == "") continue;
      for (int j = i + 1; j < jumlahNode; j++) {
         if (namaTempat[j] == "") continue;
         cout << "Jarak dari " << namaTempat[i] << " ke " << namaTempat[j] << " (meter): ";
         cin >> jarak[i][j];
         jarak[j][i] = jarak[i][j];
      }
   }
   simpanGraphKeFile();
   cout << "\nData jarak berhasil disimpan.\n";
}

void shortestPath(int awal, int akhir) {
   int tempVal[jumlahNode], path[jumlahNode], previous[jumlahNode];
   int visited[jumlahNode];
   for (int i = 0; i < jumlahNode; i++) {
      tempVal[i] = 9999;
      previous[i] = -1;
      visited[i] = 0;
   }

   tempVal[awal] = 0;
   int current = awal;
   while (!visited[akhir]) {
      visited[current] = 1;
      for (int i = 0; i < jumlahNode; i++) {
         if (jarak[current][i] > 0 && !visited[i]) {
               int update = tempVal[current] + jarak[current][i];
               if (update < tempVal[i]) {
                  tempVal[i] = update;
                  previous[i] = current;
               }
         }
      }
      int min = 9999, next = -1;
      for (int i = 0; i < jumlahNode; i++) {
         if (!visited[i] && tempVal[i] < min) {
               min = tempVal[i];
               next = i;
         }
      }
      if (next == -1) break;
      current = next;
   }

   // Tampilkan rute
   int rute[jumlahNode], count = 0;
   int temp = akhir;
   while (temp != -1) {
      rute[count++] = temp;
      temp = previous[temp];
   }
   cout << "\nRute optimal dari " << namaTempat[awal] << " ke " << namaTempat[akhir] << ": ";
   for (int i = count - 1; i >= 0; i--) {
      cout << namaTempat[rute[i]];
      if (i != 0) cout << " -> ";
   }
   cout << "\nTotal Jarak: " << tempVal[akhir] << " meter\n";
}

