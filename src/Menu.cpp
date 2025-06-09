#include <iostream>
#include <limits>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <cstdio>
#include "../include/Menu.h"
#include "../include/SensorSimulator.h"
#include "../include/NotificationQueue.h"
#include "../include/GraphRoute.h"
#include "../include/TrashHistoryStack.h"

using namespace std;

#ifdef _WIN32
   #define CLEAR "cls"
#else
   #define CLEAR "clear"
#endif

void clearScreen() {
   system(CLEAR);
}

void heading() {
   clearScreen();
   cout << "===============================" << endl;
   cout << "            STrashMon          " << endl;
   cout << "       Smart Trash Monitor     " << endl;
   cout << "Tempat Sampah Pintar Anti-Penuh" << endl;
   cout << "===============================" << endl;
   this_thread::sleep_for(chrono::milliseconds(700));
   cout << "System booting";
   for (int i = 0; i < 3; ++i) {
      cout << ".";
      cout.flush();
      this_thread::sleep_for(chrono::milliseconds(500));
   }
   cout << "\n\n";
}

void lihatStatusTempatSampah() {
   updateSensorLevels();
   updateSemuaHistori();
   displaySensorStatus();
}

void lihatAntrianNotifikasi() {
   cout << "Menampilkan antrian notifikasi...\n";
}
void lihatRuteOptimal() {
   clearScreen();
   cout << "===== MENU RUTE PENGAMBILAN OPTIMAL =====\n";

   inputGraph(); // tampilkan atau isi jarak

   cout << "\n1. Rute otomatis dari kantor untuk pengambilan penuh\n";
   cout << "2. Tentukan rute manual (lokasi ke lokasi)\n";
   cout << "Pilih opsi: ";
   int pilih;
   cin >> pilih;

   if (pilih == 1) {
      ruteKelilingPickup();
   } else if (pilih == 2) {
      int awal, akhir;
      cout << "\nDaftar Lokasi:\n";
      for (int i = 0; i < jumlahNode; i++) {
         if (namaTempat[i] != "") {
            cout << i << ". " << namaTempat[i] << endl;
         }
      }
      cout << "\nMasukkan nomor lokasi awal   : ";
      cin >> awal;
      cout << "Masukkan nomor lokasi tujuan : ";
      cin >> akhir;

      if (awal < 0 || akhir < 0 || awal >= jumlahNode || akhir >= jumlahNode || namaTempat[awal] == "" || namaTempat[akhir] == "") {
         cout << "\nInput lokasi tidak valid.\n";
      } else {
         shortestPath(awal, akhir);
      }
   } else {
      cout << "\nPilihan tidak valid.\n";
   }
}
void cekHistori() {
   cout << "Cek histori tempat sampah...\n";
}

void resetData() {
   cout << "Mereset data...\n";
}

void menuUtama() {
   int pilihan;
   bool aktif = true;

   while (aktif) {
      clearScreen();
      cout << "\n===== SMART TRASH MONITOR =====\n";
      cout << "1. Lihat status semua tempat sampah\n";
      cout << "2. Lihat antrian notifikasi\n";
      cout << "3. Lihat rute pengambilan optimal\n";
      cout << "4. Cek histori tempat sampah\n";
      cout << "5. Reset data\n";
      cout << "0. Keluar\n";
      cout << "Pilih menu: ";

      if (!(cin >> pilihan)) {
         cout << "\nInput tidak valid. Masukkan angka.\n";
         cin.clear();
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
         cout << "Tekan Enter untuk melanjutkan...";
         cin.get();
         continue;
      }

      switch (pilihan) {
         case 1:
               clearScreen();
               lihatStatusTempatSampah();
               break;
         case 2:
               clearScreen();
               lihatAntrianNotifikasi();
               break;
         case 3:
               clearScreen();
               lihatRuteOptimal();
               break;
         case 4:
               clearScreen();
               cekHistori();
               break;
         case 5:
               clearScreen();
               resetData();
               break;
         case 0:
               cout << "Keluar dari program.\n";
               aktif = false;
               break;
         default:
               cout << "\nPilihan tidak valid. Silakan pilih dari 0-5.\n";
               break;
      }

      if (aktif) {
         cout << "\nTekan Enter untuk kembali ke menu...";
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
         cin.get();
      }
   }
}
