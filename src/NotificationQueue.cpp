#include "../include/NotificationQueue.h"
#include "../include/SensorSimulator.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

NotifQueue notif;

void createQueue() {
   notif.top = 0;
}

int isEmptyQueue() {
   return notif.top == 0 ? 1 : 0;
}

int isFullQueue() {
   return notif.top >= maxNotif ? 1 : 0;
}

void insertQueue(string data) {
   if (isFullQueue() == 1) {
      cout << "Maaf, antrian notifikasi penuh." << endl;
   } else {
      notif.isi[notif.top] = data;
      notif.top++;
   }
   simpanQueueKeFile();
}

void deleteQueue() {
   if (isEmptyQueue() == 1) {
      cout << "Tidak ada notifikasi yang bisa dihapus." << endl;
   } else {
      string keluar = notif.isi[0];
      for (int i = 0; i < notif.top - 1; i++) {
         notif.isi[i] = notif.isi[i + 1];
      }
      notif.top--;
      cout << "Notifikasi '" << keluar << "' telah dihapus dari antrian." << endl;
   }
}

void displayQueue() {
   if (isEmptyQueue() == 1) {
      cout << "Tidak ada notifikasi saat ini." << endl;
   } else {
      cout << "\nDaftar Notifikasi Sampah Penuh:\n";
      for (int i = 0; i < notif.top; i++) {
         cout << "- " << notif.isi[i] << endl;
      }
   }
}