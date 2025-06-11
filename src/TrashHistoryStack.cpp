#include "../include/TrashHistoryStack.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <fstream>
using namespace std;

HistoriStack historiList[maxLokasi];

void createHistori() {
   for (int i = 0; i < maxLokasi; i++) {
      historiList[i].top = -1;
   }
}

string getCurrentTime() {
   time_t now = time(0);
   tm* ltm = localtime(&now);
   stringstream ss;
   ss << setfill('0') << setw(2) << ltm->tm_hour << ":"
      << setw(2) << ltm->tm_min << ":"
      << setw(2) << ltm->tm_sec;
   return ss.str();
}

// string getCurrentDate() {
//    time_t now = time(0);
//    tm* ltm = localtime(&now);
//    stringstream ss;
//    ss << setfill ('0') << setw(2) << ltm->tm_mday << "/"
//       << setw(2) << (ltm->tm_mon +1) << "/"
//       << (ltm->tm_year + 1900);
//    return ss.str();
// }

void pushHistori(int index, HistoriData newData) {
   if (index < 0 || index >= maxLokasi) return; // validasi indeks
   if (historiList[index].top < kapasitas - 1) {
      historiList[index].top++;
      historiList[index].data[historiList[index].top] = newData;
   } else {
      for (int i = 0; i < kapasitas - 1; i++) {
         historiList[index].data[i] = historiList[index].data[i + 1];
      }
      historiList[index].data[kapasitas - 1] = newData;
   }
}

void displayHistori(int index) {
   if (historiList[index].top == -1) {
      cout << "Histori masih kosong untuk lokasi ini.\n";
      return;
   }

   cout << left
        << "+------------+---------+----------+\n"
        << "|   Waktu    |  Level  |  Status  |\n"
        << "+------------+---------+----------+\n";

   for (int i = historiList[index].top; i >= 0; i--) {
      cout << "| "
           << setw(10) << historiList[index].data[i].waktu << " | "
           << setw(6)  << fixed << setprecision(2) << historiList[index].data[i].level << "% | "
           << setw(8)  << historiList[index].data[i].status << " |\n";
   }

   cout << "+------------+---------+----------+\n";
}

void analisisHistori(int index) {
   if (historiList[index].top == -1) {
      cout << "Belum cukup data untuk dianalisis.\n";
      return;
   }

   float total = 0;
   int merah = 0, kuning = 0, hijau = 0;
   int count = historiList[index].top + 1;

   for (int i = 0; i < count; i++) {
      float val = historiList[index].data[i].level;
      string status = historiList[index].data[i].status;
      total += val;
      if (status == "Merah") merah++;
      else if (status == "Kuning") kuning++;
      else hijau++;
   }

   float rata = total / count;
   string dominan = merah >= kuning && merah >= hijau ? "Merah" :
                    (kuning >= hijau ? "Kuning" : "Hijau");

   cout << "\n=== Analisis Histori ===\n";
   cout << "- Rata-rata Kepenuhan: " << fixed << setprecision(1) << rata << "%\n";
   cout << "- Status Dominan     : " << dominan << "\n";

   if (rata >= 85)
      cout << "- Rekomendasi: Tempat sampah sering penuh. Jadwal pengambilan perlu ditingkatkan.\n";
   else if (rata >= 60)
      cout << "- Rekomendasi: Tempat sampah aktif digunakan, pantau secara berkala.\n";
   else
      cout << "- Rekomendasi: Frekuensi pemakaian rendah. Jadwal bisa dilonggarkan.\n";
}

void simpanHistoriKeFile() {
   ofstream file("data/histori.txt");
   if (file.is_open()) {
      for (int i = 0; i < maxLokasi; i++) {
         for (int j = 0; j <= historiList[i].top; j++) {
            file << i << ";"
               //   << historiList[i].data[j].tanggal << ";"
                 << historiList[i].data[j].waktu << ";"
                 << historiList[i].data[j].level << ";"
                 << historiList[i].data[j].status << "\n";
         }
      }
      file.close();
   } else {
      cout << "Gagal menyimpan histori ke file.\n";
   }
}

void bacaHistoriDariFile() {
   ifstream file("data/histori.txt");
   if (!file.is_open()) {
      createHistori();
      return;
   }

   createHistori();
   string line;
   while (getline(file, line)) {
      if (line.empty()) continue;

      stringstream ss(line);
      string tanggal, waktu, status, temp;
      float level;
      int index;

      getline(ss, temp, ';'); index = stoi(temp);
      // getline(ss, tanggal, ';');
      getline(ss, waktu, ';');
      getline(ss, temp, ';'); level = stof(temp);
      getline(ss, status);

      HistoriData data = {waktu, level, status};
      pushHistori(index, data);
   }

   file.close();
}
