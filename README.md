# 🗑️ Smart Trash Monitor - Tempat Sampah Pintar Anti-Penuh

![Smart Trash Monitor Banner](https://img.shields.io/badge/ESP32-IoT-blue?style=flat-square)
![C++](https://img.shields.io/badge/Language-C%2B%2B-informational?style=flat-square)
![Wokwi](https://img.shields.io/badge/Simulator-Wokwi-green?style=flat-square)

## 📌 Deskripsi

**Smart Trash Monitor (STrashMon)** adalah sistem monitoring tempat sampah berbasis **IoT dan C++** yang mampu:

- Mendeteksi tingkat kepenuhan tempat sampah secara otomatis
- Mengirim notifikasi ke petugas jika penuh
- Menentukan rute optimal pengambilan menggunakan struktur graph
- Menyimpan histori kepenuhan dan menganalisis tren penggunaan

Proyek ini merupakan implementasi dari **Ujian Akhir Semester 2** dengan menggabungkan materi:

- Struktur Data: **Stack, Queue, Graph**
- Simulasi **Internet of Things (IoT)** menggunakan **ESP32** dan **sensor ultrasonik (HC-SR04)** di **Wokwi**
- Pemrograman berbasis **Command Line Interface (CLI)** dengan bahasa **C++**
- Manajemen file (histori, notifikasi, dan data jarak)

## 🎯 Fitur Utama

### 🔍 Menu CLI:

```
1. Lihat status semua tempat sampah
2. Lihat antrian notifikasi
3. Lihat rute pengambilan optimal
4. Cek histori tempat sampah
5. Reset data
```

### 📡 Komponen IoT (Wokwi)

- ESP32
- Sensor Ultrasonik HC-SR04
- 3 LED indikator (Hijau, Kuning, Merah)
- Breadboard, resistor, kabel jumper
- Buzzer (opsional)

**Link Proyek Wokwi:** [Klik untuk membuka simulasi](https://wokwi.com/projects/433469030091109377)

### 🧠 Struktur Data yang Diimplementasikan

- **Stack** untuk histori kepenuhan (maks 5 data)
- **Queue** untuk antrian notifikasi FIFO
- **Graph** untuk rute pengambilan sampah menggunakan algoritma Dijkstra

## 👨‍💻 Anggota Kelompok 6

| Nama                     | NIM     |
| ------------------------ | ------- |
| Ica Apriyanti Rahayu     | 2408415 |
| Mirachel Cindejona       | 2401638 |
| Nugra Hasahatan Lubis    | 2403457 |
| Rafli Ahmad Fauzi        | 2405815 |
| Regina Nur Fadhilah      | 2406043 |
| Saifulloh Fattah Bintoro | 2408256 |

## 🧪 Cara Menjalankan Proyek

### 💻 1. Clone Repository dari GitHub

```bash
git clone https://github.com/mirachelcindejona/STrashMon6.git
cd STrashMon6
```

### 🛠️ 2. Compile Program (Windows CMD atau Linux terminal)

```bash
g++ main.cpp ^
  .\src\Menu.cpp ^
  .\src\SensorSimulator.cpp ^
  .\src\NotificationQueue.cpp ^
  .\src\GraphRoute.cpp ^
  .\src\TrashHistoryStack.cpp ^
  -o .\exe\STrashMon
```

> Untuk Linux/MacOS: ganti `^` dengan `\` atau gunakan satu baris

### ▶️ 3. Jalankan Aplikasi

```bash
.\exe\STrashMon
```

> Ikuti tampilan menu CLI yang muncul.

## 🤝 Kontribusi & Lisensi

Proyek ini dibuat untuk kepentingan edukasi dan pengembangan skill rekayasa perangkat lunak serta integrasi perangkat IoT.  
Silakan gunakan dan kembangkan ulang dengan mencantumkan kredit kepada tim pengembang.

> _"Bangun teknologi yang ramah lingkungan dan berbasis data, dimulai dari tempat sampah cerdas."_ 🌱
