#include "../include/GraphRoute.h"
#include "../include/SensorSimulator.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
#include <limits>
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

void simpanGraphKeFile() {
   ofstream file("data/jarak.txt");
   if (file.is_open()) {
      for (int i = 0; i < jumlahNode; i++) {
         for (int j = 0; j < jumlahNode; j++) {
               file << jarak[i][j];
               if (j < jumlahNode - 1) file << " ";
         }
         file << "\n";
      }
      file.close();
   }
}

void bacaGraphDariFile() {
   ifstream file("data/jarak.txt");
   if (file.is_open()) {
      for (int i = 0; i < jumlahNode; i++) {
         for (int j = 0; j < jumlahNode; j++) {
               file >> jarak[i][j];
         }
      }
      file.close();
      sudahInput = true;
   }

   ifstream temp("data/tempat.txt");
   if (temp.is_open()) {
      string line;
      int index = 0;
      while (getline(temp, line) && index < jumlahNode) {
         stringstream ss(line);
         string id, lokasi;
         getline(ss, id, ';');
         getline(ss, lokasi);
         namaTempat[index] = lokasi;
         index++;
      }
      temp.close();
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

         int inputJarak;
         while (true) {
            cout << "Jarak dari " << namaTempat[i] << " ke " << namaTempat[j] << " (meter): ";
            if (cin >> inputJarak && inputJarak >= 0) {
               jarak[i][j] = inputJarak;
               jarak[j][i] = inputJarak;
               break;
            } else {
               cout << "Input tidak valid. Harap masukkan angka >= 0.\n";
               cin.clear();
               cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
         }
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

void ruteKelilingPickup() {
   cout << "\n=== Rute Pengambilan Sampah Otomatis dari Kantor ===\n";
   vector<int> titikDiambil;
   for (int i = 1; i < jumlahNode; i++) {
      if (namaTempat[i] == "") continue;
      string status = getStatusIndikator(sensorList[i].level);
      if (status == "Merah") {
         titikDiambil.push_back(i);
      }
   }

   if (titikDiambil.empty()) {
      cout << "Tidak ada tempat sampah yang perlu diambil.\n";
      return;
   }

   int current = 0;
   vector<bool> visited(jumlahNode, false);
   visited[0] = true;
   int total = 0;

   cout << "Rute: " << namaTempat[0];
   while (!titikDiambil.empty()) {
      int terdekat = -1;
      int jarakMin = 9999;
      for (int i = 0; i < titikDiambil.size(); i++) {
         int target = titikDiambil[i];
         if (!visited[target] && jarak[current][target] > 0 && jarak[current][target] < jarakMin) {
               terdekat = target;
               jarakMin = jarak[current][target];
         }
      }
      if (terdekat == -1) break;

      total += jarakMin;
      visited[terdekat] = true;
      cout << " -> " << namaTempat[terdekat];
      current = terdekat;
      titikDiambil.erase(remove(titikDiambil.begin(), titikDiambil.end(), terdekat), titikDiambil.end());
   }

   if (jarak[current][0] > 0) {
      total += jarak[current][0];
      cout << " -> " << namaTempat[0];
   }

   cout << "\nTotal jarak rute: " << total << " meter\n";
}