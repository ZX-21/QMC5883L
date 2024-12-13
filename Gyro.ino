#include <Wire.h>

// ที่อยู่ของ QMC5883L
#define QMC5883L_ADDR 0x0D

// ฟังก์ชันเริ่มต้น QMC5883L
void initQMC5883L() {
  Wire.beginTransmission(QMC5883L_ADDR);
  Wire.write(0x0B); // Register 0x0B: Control Register
  Wire.write(0x01); // Set to continuous measurement mode
  Wire.endTransmission();

  Wire.beginTransmission(QMC5883L_ADDR);
  Wire.write(0x09); // Register 0x09: Configuration
  Wire.write(0x1D); // Set output data rate and range
  Wire.endTransmission();
}

// ฟังก์ชันอ่านค่าจาก QMC5883L
void readQMC5883L(int16_t *x, int16_t *y, int16_t *z) {
  Wire.beginTransmission(QMC5883L_ADDR);
  Wire.write(0x00); // Register 0x00: Data output X LSB
  Wire.endTransmission();

  Wire.requestFrom(QMC5883L_ADDR, 6); // อ่านข้อมูล 6 ไบต์ (X, Y, Z)
  if (Wire.available() == 6) {
    *x = Wire.read() | (Wire.read() << 8); // X-axis
    *y = Wire.read() | (Wire.read() << 8); // Y-axis
    *z = Wire.read() | (Wire.read() << 8); // Z-axis
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin();

  initQMC5883L(); // เริ่มต้นการทำงานของเซนเซอร์
  Serial.println("QMC5883L Initialized!");
}

void loop() {
  int16_t x, y, z;

  readQMC5883L(&x, &y, &z); // อ่านค่าจากเซนเซอร์

  // แสดงผลบน Serial Monitor
  Serial.print("X: ");
  Serial.print(x);
  Serial.print("  Y: ");
  Serial.print(y);
  Serial.print("  Z: ");
  Serial.println(z);

  delay(10); // อ่านค่าทุกๆ 1 วินาที
}
