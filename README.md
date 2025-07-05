# 🌡️ Tugas 13 IoT – Monitoring Suhu LM35 + Ethernet ENC28J60

Proyek ini merupakan simulasi **monitoring suhu menggunakan sensor LM35**, yang ditampilkan melalui **Virtual Terminal** dan juga **Web Browser** menggunakan modul Ethernet ENC28J60. Seluruh simulasi dilakukan di dalam **Proteus 8 Professional** menggunakan **Arduino Uno R3**.

---

## 👨‍💻 Anggota Kelompok

**Anggota 1**  
- Nama  : Gilang Ady Laksono  
- NIM   : 1462200039  
- Email : gilangady@gmail.com  

**Anggota 2**  
- Nama  : Adhelia Shafira Lianjari  
- NIM   : 1462200225  
- Email : adhelia@gmail.com  

---

## 🔧 Komponen yang Digunakan
- Arduino Uno R3  
- Sensor Suhu LM35  
- Modul Ethernet ENC28J60  
- Virtual Terminal (Serial Monitor)  
- 4x LED + resistor 220Ω  
- Software Proteus 8

---

## ⚙️ Fitur Utama
- Membaca suhu dari sensor LM35 (10mV = 1°C)  
- Menampilkan suhu ke Serial Monitor dan halaman Web  
- Indikator LED menyala bertingkat sesuai suhu:
  - LED1: > 30°C  
  - LED2: > 35°C  
  - LED3: > 40°C  
  - LED4: > 45°C  

---

## 💡 Penjelasan LED
LED bertindak sebagai indikator suhu berdasarkan data dari sensor LM35. Logika kerja sebagai berikut:

- Suhu < 30°C → Semua LED **mati**  
- Suhu > 30°C → LED 1 **menyala**  
- Suhu > 35°C → LED 2 **menyala**  
- Suhu > 40°C → LED 3 **menyala**  
- Suhu > 45°C → LED 4 **menyala**

Semakin tinggi suhu, semakin banyak LED yang menyala sebagai indikator visual.

---

## 🌐 Cara Simulasi
1. Buka file `EAS_IOT_13.pdsprj` di Proteus.
2. Jika tidak tersedia LM35, ganti dengan **Voltage Source**.
3. Set nilai tegangan (misalnya 0.35V ≈ 35°C).
4. Jalankan simulasi dan lihat:
   - Output suhu di **Virtual Terminal**
   - Tampilan suhu di web browser melalui IP:
     ```
     http://192.168.0.177
     ```

---

## 📁 Struktur File
Tugas13_Kelompok_IoT/
├── proteus_project/
│ └── EAS_IOT_13.pdsprj
├── arduino_code/
│ ├── iot_suhu_lm35.ino
│ └── iot_suhu_lm35.hex
├── README.md
└── EAS_IOT.pdf
