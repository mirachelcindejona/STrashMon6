#include "../include/SensorSimulator.h"
#include "../include/TrashHistoryStack.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <fstream>

using namespace std;

vector<TrashBin> sensorList = {
   {"KTR", "Kantor Petugas", 0.0},
   {"TS1", "Depan Sekolah", 25.0},
   {"TS2", "Taman Belakang", 60.0},
   {"TS3", "Halte Utama", 85.0},
   {"TS4", "Samping Kantin", 40.0}
};

void updateSensorLevels() {
   srand(time(0));
   for (auto& bin : sensorList) {
      float change = (rand() % 2001 - 1000) / 100.0; // -10.0% to +10.0%
      bin.level += change;
      if (bin.level < 0) bin.level = 0;
      if (bin.level > 100) bin.level = 100;
   }
}

string getStatusIndikator(float level) {
   if (level < 60.0) return "Hijau";
   else if (level <= 90.0) return "Kuning";
   else return "Merah";
}

void displaySensorStatus() {
   cout << "\nStatus Semua Tempat Sampah:\n";
   cout << left
      << setw(20) << "ID Tempat Sampah"
      << setw(25) << "Lokasi"
      << setw(20) << "Persentase Kepenuhan"
      << setw(10) << "Indikator"
      << "\n";
   cout << string(75, '-') << "\n";

   for (const auto& bin : sensorList) {
      cout << left
            << setw(20) << bin.id
            << setw(25) << bin.location
            << setw(20) << (to_string((int)bin.level) + "%")
            << setw(10) << getStatusIndikator(bin.level)
            << "\n";
   }
}

void simpanTempatKeFile() {
   ofstream file("data/tempat.txt");

   if (file.is_open()) {
      for (int i = 0; i < sensorList.size(); i++) {
         file << sensorList[i].id << ";" << sensorList[i].location << "\n";
      }
      file.close();
   } else {
      cout << "Gagal menyimpan data tempat ke file.\n";
   }
}

void updateSemuaHistori() {
   for (int i = 1; i < sensorList.size(); i++) {
      HistoriData data;
      data.level = sensorList[i].level;
      data.status = getStatusIndikator(data.level);
      data.waktu = getCurrentTime();
      pushHistori(i, data);
   }
}