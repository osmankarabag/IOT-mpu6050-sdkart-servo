#include <Wire.h> // I2C haberleşme kütüphanesi
#include <Adafruit_GFX.h> // Grafik kütüphanesi
#include <Adafruit_SSD1306.h> // SSD1306 ekran kontrol kütüphanesi
#include <Adafruit_MPU6050.h> // MPU6050 ivmeölçer/gyro sensörü kütüphanesi
#include <Adafruit_Sensor.h> // Adafruit sensör kütüphanesi
#include <Servo.h> // Servo motor kontrol kütüphanesi
#include <SD.h> // SD kart kütüphanesi

const int chipSelect = 53; // SD kart seçimi

#define SCREEN_WIDTH 128 // Ekran genişliği
#define SCREEN_HEIGHT 64 // Ekran yüksekliği

Adafruit_MPU6050 mpu; // MPU6050 nesnesi oluşturulması

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // SSD1306 ekran nesnesi oluşturulması

Servo servoMotor1; // 1. servo motor nesnesi
int servoMin1 = 0; // 1. servo motor için minimum açı
int servoMax1 = 180; // 1. servo motor için maksimum açı
Servo servoMotor2; // 2. servo motor nesnesi
int servoMin2 = 0; // 2. servo motor için minimum açı
int servoMax2 = 180; // 2. servo motor için maksimum açı

void setup() {
  Serial.begin(115200); // Seri haberleşme başlatılıyor
  
  while (!Serial) {
    ; // Seri bağlantı bekleniyor
  }
  
  servoMotor1.attach(7); // 1. servo motor pinine bağlanıyor
  servoMotor2.attach(8); // 2. servo motor pinine bağlanıyor

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 initialization failed")); // Ekran başlatılamadı uyarısı
    while(true);
  }
  
  Serial.println("Adafruit MPU6050 test!"); // MPU6050 test mesajı

  // İvmeölçer/gyro başlatılıyor
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip"); // MPU6050 bulunamadı uyarısı
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!"); // MPU6050 bulundu mesajı

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G); // İvmeölçer aralığı ayarlanıyor

  Serial.println("Initializing SD card..."); // SD kart başlatılıyor mesajı

  // SD kart başlatılıyor
  if (!SD.begin(chipSelect)) {
    Serial.println("SD card initialization failed."); // SD kart başlatılamadı uyarısı
    return;
  }
  Serial.println("SD card initialized successfully."); // SD kart başlatıldı mesajı
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp); // Sensör verileri alınıyor

  // Ekran temizleniyor ve veriler yazdırılıyor
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Accelerometer (m/s^2)");

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.print(a.acceleration.x);
  display.setCursor(35, 10);
  display.print(",");
  display.setCursor(45, 10);
  display.print(a.acceleration.y);
  display.setCursor(80, 10);
  display.print(",");
  display.setCursor(90, 10);
  display.print(a.acceleration.z);

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 20);
  display.print("Gyroscope (rps)");

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 30);
  display.print(g.gyro.x);
  int servoPos1 = map(g.gyro.x, -4.3, +4.3, servoMin1, servoMax1); // 1. servo motor pozisyonu hesaplanıyor
  servoMotor1.write(servoPos1); // 1. servo motor hareket ettiriliyor
  display.setCursor(35, 30);
  display.print(",");
  display.setCursor(45, 30);
  display.print(g.gyro.y);
  int servoPos2 = map(g.gyro.y, -4.3, +4.3, servoMin2, servoMax2); // 2. servo motor pozisyonu hesaplanıyor
  servoMotor2.write(servoPos2); // 2. servo motor hareket ettiriliyor
  display.setCursor(80, 30);
  display.print(",");
  display.setCursor(90, 30);
  display.print(g.gyro.z);

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 40);
  display.print("Temperature ");

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 50);
  display.print(temp.temperature);
  display.setCursor(45, 50);
  display.print("degC");

  display.display();

  File dataFile = SD.open("mpu6050.txt", FILE_WRITE); // SD karta yazma modunda dosya açılıyor
  
  if (dataFile) {
    // Veriler dosyaya yazılıyor
    dataFile.println("Accelerometer (m/s^2)");
    dataFile.print(a.acceleration.x);
    dataFile.print(", ");
    dataFile.print(a.acceleration.y);
    dataFile.print(", ");
    dataFile.println(a.acceleration.z);

    dataFile.println("Gyroscope (rps)");
    dataFile.print(g.gyro.x);
    dataFile.print(", ");
    dataFile.print(g.gyro.y);
    dataFile.print(", ");
    dataFile.print(g.gyro.z);

    dataFile.println("Temperature ");
    dataFile.print(temp.temperature);
    dataFile.println(" degC");

    dataFile.println("*******************************************");

    dataFile.close();
  }
  else {
    Serial.println("Error opening file."); // Dosya açılamadı uyarısı
  }
  delay(1000); // 1 saniye bekle

  File dataFile2 = SD.open("mpu6050.txt", FILE_READ); // SD karta okuma modunda dosya açılıyor
  
  if (dataFile2) {
    while (dataFile2.available()) { // Dosya okunuyor
      Serial.write(dataFile2.read());
    }
    dataFile2.close(); // Dosya kapatılıyor
  }
  else {
    Serial.println("Error opening file."); // Dosya açılamadı uyarısı
  }

  SD.remove("mpu6050.txt"); // Dosya siliniyor
}
