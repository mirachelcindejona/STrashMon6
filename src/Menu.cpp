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
   updateSensorLevels();          // update sensor dulu
   updateSemuaHistori();
   checkTrashNotification();      // cek dan isi antrian
   displayQueue();                // tampilkan isi antrian
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
   clearScreen();
   bacaGraphDariFile();

   cout << "===== HISTORI TEMPAT SAMPAH =====\n\n";

   cout << "Daftar Lokasi:\n";
   for (int i = 1; i < jumlahNode; i++) {
      if (namaTempat[i] != "") {
         cout << i << ". " << namaTempat[i] << endl;
      }
   }

   // Validasi input lokasi
   int pilih;
   while (true) {
      cout << "\nPilih nomor lokasi yang ingin dicek: ";
      if (!(cin >> pilih)) {
         cout << "Input harus berupa angka.\n";
         cin.clear();
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
         continue;
      }
      if (pilih < 1 || pilih >= jumlahNode || namaTempat[pilih] == "") {
         cout << "Nomor lokasi tidak valid. Silakan coba lagi.\n";
         continue;
      }
      break;
   }

   cout << "\nHistori Kepenuhan - " << namaTempat[pilih] << endl;
   displayHistori(pilih);

   // Opsi lanjutan
   int opsi;
   while (true) {
      cout << "\n[1] Analisis tren kepenuhan\n[2] Kembali\nPilihan Anda: ";
      if (!(cin >> opsi)) {
         cout << "Input harus berupa angka.\n";
         cin.clear();
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
         continue;
      }
      if (opsi == 1) {
         analisisHistori(pilih);
         break;
      } else if (opsi == 2) {
         break;
      } else {
         cout << "Pilihan tidak valid. Coba lagi.\n";
      }
   }
}

void resetQueueData() {
   createQueue();
   simpanQueueKeFile(); // kosongkan dan simpan ulang
   cout << "Queue berhasil dikosongkan.\n";
}

void resetHistoryData() {
   createHistori();         // kosongkan stack histori
   simpanHistoriKeFile();   // kosongkan file
   cout << "Histori berhasil dikosongkan.\n";
}

void resetJarakData() {
   if (remove("data/jarak.txt") == 0) {
      cout << "Data jarak berhasil dihapus.\n";
   } else {
      cout << "Gagal menghapus file jarak.txt (mungkin belum ada).\n";
   }
}

void resetSemuaData() {
   resetQueueData();
   resetHistoryData();
   resetJarakData();
   cout << "Seluruh data telah direset.\n";
}

void resetData() {
   int pilihan;
   bool kembali = false;

   while (!kembali) {
      clearScreen();
      cout << "===== MENU RESET DATA =====\n";
      cout << "1. Reset Semua Data\n";
      cout << "2. Reset Queue Notifikasi\n";
      cout << "3. Reset Stack Histori\n";
      cout << "4. Reset Data Jarak Tempat Sampah\n";
      cout << "0. Kembali\n";
      cout << "Pilih menu: ";

      if (!(cin >> pilihan)) {
         cin.clear();
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
         cout << "Input tidak valid. Masukkan angka.\n";
         continue;
      }

      char konfirmasi;
      switch (pilihan) {
         case 1:
            cout << "Konfirmasi reset semua? (y/n): ";
            cin >> konfirmasi;
            if (konfirmasi == 'y' || konfirmasi == 'Y') {
               resetSemuaData();
            } else {
               cout << "Dibatalkan.\n";
            }
            break;
         case 2:
            cout << "Konfirmasi reset queue? (y/n): ";
            cin >> konfirmasi;
            if (konfirmasi == 'y' || konfirmasi == 'Y') {
               resetQueueData();
            } else {
               cout << "Dibatalkan.\n";
            }
            break;
         case 3:
            cout << "Konfirmasi reset histori? (y/n): ";
            cin >> konfirmasi;
            if (konfirmasi == 'y' || konfirmasi == 'Y') {
               resetHistoryData();
            } else {
               cout << "Dibatalkan.\n";
            }
            break;
         case 4:
            cout << "Konfirmasi reset data jarak? (y/n): ";
            cin >> konfirmasi;
            if (konfirmasi == 'y' || konfirmasi == 'Y') {
               resetJarakData();
            } else {
               cout << "Dibatalkan.\n";
            }
            break;
         case 0:
            kembali = true;
            break;
         default:
            cout << "Pilihan tidak valid.\n";
      }

      if (!kembali) {
         cout << "\nTekan Enter untuk kembali ke menu reset...";
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
         cin.get();
      }
   }
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
