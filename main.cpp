#include <iostream>
#include "include/Menu.h"
#include "include/SensorSimulator.h"
#include "include/NotificationQueue.h"
#include "include/TrashHistoryStack.h"
#include "include/GraphRoute.h"

int main() {
   // initializeSensorSimulator();  // inisialisasi sensorList lebih dulu
   simpanTempatKeFile();         // simpan ID dan lokasi ke file tempat.txt
   createHistori();              // siapkan struktur stack histori
   bacaQueueDariFile();
   bacaHistoriDariFile();
   updateSensorLevels();         // isi sensorList dengan level acak
   updateSemuaHistori();         // histori terisi dari data sensor
   simpanHistoriKeFile();  
   heading();                    // tampilkan header boot
   menuUtama();                  // baru tampilkan menu
   simpanQueueKeFile();
   return 0;
}