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
   {"RM1", "Rumah Ica", 0.0},
   {"RM2", "Rumah Rere", 0.0},
   {"RM3", "Rumah Rakel", 0.0},
   {"RM4", "Rumah Ipul", 0.0},
   {"RM5", "Rumah Nugi", 0.0},
   {"RM6", "Rumah Rafli", 0.0},
   {"RM7", "Rumah Vina", 0.0},
   {"RM8", "Rumah Marwa", 0.0}
};

// Simulasi update sensor naik 1–3% per update
void updateSensorLevels() {
   srand(time(0));
   for (auto& bin : sensorList) {
      float naik = (rand() % 9 + 5); // +1% sampai +3%
      bin.level += naik;
      if (bin.level > 100.0) bin.level = 100.0;
   }
}

// Status indikator dari level
string getStatusIndikator(float level) {
   if (level < 60.0) return "Hijau";
   else if (level <= 90.0) return "Kuning";
   else return "Merah";
}

// Tampilan tabel status seperti histori
void displaySensorStatus() {
   cout << "\n+---------------------+--------------------------+------------------------+----------+\n";
   cout << "| ID Tempat Sampah    | Lokasi                   | Persentase Kepenuhan   |Indikator |\n";
   cout << "+---------------------+--------------------------+------------------------+----------+\n";

   for (const auto& bin : sensorList) {
      cout << "| "
           << setw(20) << left << bin.id
           << "| " << setw(25) << left << bin.location
           << "| " << setw(22) << left << fixed << setprecision(1) << bin.level << "%"
           << "| " << setw(9)  << left << getStatusIndikator(bin.level)
           << "|\n";
   }

   cout << "+---------------------+--------------------------+------------------------+----------+\n";
}

// Menyimpan ID dan lokasi ke file
void simpanTempatKeFile() {
   ofstream file("data/tempat.txt");
   if (file.is_open()) {
      for (const auto& bin : sensorList) {
         file << bin.id << ";" << bin.location << "\n";
      }
      file.close();
   } else {
      cout << "Gagal menyimpan data tempat ke file.\n";
   }
}

// Setiap sensor di-update, histori langsung dicatat
void updateSemuaHistori() {
   for (int i = 1; i < sensorList.size(); i++) {
      HistoriData data;
      data.level = sensorList[i].level;
      data.status = getStatusIndikator(data.level);
      data.waktu = getCurrentTime();
      pushHistori(i, data);
   }
}
