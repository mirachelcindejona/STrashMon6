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

string getCurrentDate() {
   time_t now = time(0);
   tm* ltm = localtime(&now);
   stringstream ss;
   ss << setfill ('0') << setw(2) << ltm->tm_mday << "/"
      << setw(2) << (ltm->tm_mon +1) << "/"
      << (ltm->tm_year + 1900);
   return ss.str();
}

void pushHistori(int index, HistoriData newData) {
   if (historiList[index].top < kapasitas - 1) {
      historiList[index].top++;
      historiList[index].data[historiList[index].top] = newData;
   } else {
      // geser semua ke atas (buang yang paling lama)
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
      << "+------------+------------+---------+---------+\n"
      << "|  Tanggal   |   Waktu    |  Level  | Status  |\n"
      << "+------------+------------+---------+---------+\n";

   for (int i = historiList[index].top; i >= 0; i--) {
      cout << "| "
            << setw(10) << historiList[index].data[i].tanggal << " | "
            << setw(10) << historiList[index].data[i].waktu << " | "
            << setw(6)  << fixed << setprecision(2) << historiList[index].data[i].level << "% | "
            << setw(7)  << historiList[index].data[i].status << " |\n";
   }

 cout << "+------------+------------+---------+---------+\n";
}


