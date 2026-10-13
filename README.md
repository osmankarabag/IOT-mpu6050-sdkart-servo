# 🧭 MPU6050 + Servo + SD Kart (Arduino)

![Arduino](https://img.shields.io/badge/Arduino-00878F?style=flat-square&logo=arduino&logoColor=white)
![Wokwi](https://img.shields.io/badge/Wokwi-Simülasyon-blueviolet?style=flat-square)

MPU6050 ivmeölçer/jiroskop sensöründen alınan verilere göre servo motorun hareketini değiştiren ve ölçümleri SD karta kaydeden IoT projesi. Veriler SSD1306 OLED ekranda da gösterilir.

## 🔧 Bileşenler
- Arduino Mega
- MPU6050 (ivmeölçer + jiroskop)
- Servo motor
- microSD kart modülü
- SSD1306 OLED ekran

## 📚 Kütüphaneler
`Adafruit MPU6050` · `Adafruit SSD1306` · `Servo` · `SD`

## 📁 Dosyalar
| Dosya | Açıklama |
|---|---|
| `mpu6050-sdkart-servo/sketch/sketch.ino` | Arduino kaynak kodu |
| `mpu6050-sdkart-servo/diagram.json` | Wokwi devre diyagramı |
| `mpu6050-sdkart-servo/libraries.txt` | Kullanılan kütüphaneler |

## ▶️ Çalıştırma
Proje [Wokwi](https://wokwi.com) üzerinde simüle edilebilir: `sketch.ino`, `diagram.json` ve `libraries.txt` dosyalarını yeni bir Wokwi projesine yükleyin.
