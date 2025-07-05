#include <UIPEthernet.h>
#include <SPI.h>
#include <avr/pgmspace.h>

// ----------------------------------------
// Konfigurasi MAC dan IP Address
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(169, 254, 59, 4);     // IP static
IPAddress gateway(169, 254, 59, 3); // Gateway dummy (tidak wajib)

// Buat web server di port 80
EthernetServer server(80);
// ----------------------------------------

// LED Pins
const int led1 = 4;
const int led2 = 5;
const int led3 = 6;
const int led4 = 7;

// LM35 sensor pin
const int lm35Pin = A0;

// HTML Header disimpan di PROGMEM
const char headerHTML[] PROGMEM =
  "HTTP/1.1 200 OK\r\n"
  "Content-Type: text/html\r\n\r\n"
  "<html><head><title>Data Mahasiswa</title></head><body>"
  "<h2>Dibuat oleh: Kelompok</h2>"
  "<h3>Anggota 1</h3>"
  "<p>Nama: Gilang Ady Laksono</p>"
  "<p>NIM: 1462200039</p>"
  "<p>Tanggal Lahir: 22 Oktober 2002</p>"
  "<p>Email: gilangady@gmail.com</p>"
  "<h3>Anggota 2</h3>"
  "<p>Nama: Adhelia Shafira Lianjari</p>"
  "<p>NIM: 1462200225</p>"
  "<p>Tanggal Lahir: 15 Februari 2004</p>"
  "<p>Email: adhelia@gmail.com</p>";

void setup() {
  Serial.begin(9600);

  // Inisialisasi koneksi Ethernet
  Ethernet.begin(mac, ip, gateway);
  server.begin();

  // Inisialisasi pin LED
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  pinMode(lm35Pin, INPUT);

  // Tampilkan informasi IP dan biodata
  Serial.println();
  Serial.print(F("IP Address : "));
  Serial.println(Ethernet.localIP());
  Serial.println();
  Serial.println(F("=== DATA MAHASISWA ==="));
  Serial.println(F("Dibuat oleh: Kelompok"));
  Serial.println();
  Serial.println(F("Anggota 1:"));
  Serial.println(F("Nama          : Gilang Ady Laksono"));
  Serial.println(F("NIM           : 1462200039"));
  Serial.println(F("Tanggal Lahir : 22 Oktober 2002"));
  Serial.println(F("Email         : gilangady@gmail.com"));
  Serial.println();
  Serial.println(F("Anggota 2:"));
  Serial.println(F("Nama          : Adhelia Shafira Lianjari"));
  Serial.println(F("NIM           : 1462200225"));
  Serial.println(F("Tanggal Lahir : 15 Februari 2004"));
  Serial.println(F("Email         : adhelia@gmail.com"));
  Serial.println(F("======================"));
}

void loop() {
  // Baca suhu dari LM35
  int adcValue = analogRead(lm35Pin);
  float voltage = adcValue * (5.0 / 1023.0);
  float temp = voltage * 100.0;

  // Tampilkan ke Serial Monitor
  Serial.print(F("Suhu : "));
  Serial.print(temp, 2);
  Serial.println(F(" C"));

  // Kontrol LED berdasarkan suhu
  digitalWrite(led1, temp > 30.0 ? HIGH : LOW);
  digitalWrite(led2, temp > 35.0 ? HIGH : LOW);
  digitalWrite(led3, temp > 40.0 ? HIGH : LOW);
  digitalWrite(led4, temp > 45.0 ? HIGH : LOW);

  // Layani permintaan dari client
  EthernetClient client = server.available();
  if (client) {
    bool currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        // Jika header HTTP selesai (baris kosong)
        if (c == '\n' && currentLineIsBlank) {
          // Kirim HTML dari PROGMEM
          for (unsigned int i = 0; i < strlen_P(headerHTML); i++) {
            client.write(pgm_read_byte_near(headerHTML + i));
          }

          // Tampilkan suhu
          client.print(F("<h3>Suhu LM35: "));
          client.print(temp, 2);
          client.println(F(" &deg;C</h3></body></html>"));
          break;
        }

        if (c == '\n') currentLineIsBlank = true;
        else if (c != '\r') currentLineIsBlank = false;
      }
    }

    delay(1);
    client.stop();
  }

  delay(1000);
}
