#include "Wire.h"

const int MPU_ADDR = 0x68;

float AccX, AccY, AccZ;
float GyroX, GyroY, GyroZ;
float accAngleX, accAngleY, gyroAngleX, gyroAngleY, gyroAngleZ;
float roll, pitch, yaw;
float AccErrorX, AccErrorY, GyroErrorX, GyroErrorY, GyroErrorZ;
float elapsedTime, currentTime, previousTime;
int c = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}

void loop() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 6, true);
  
  AccX = Wire.read()<<8 | Wire.read();
  AccY = Wire.read()<<8 | Wire.read();
  AccZ = Wire.read()<<8 | Wire.read();

  AccX = AccX / 16384.0;
  AccY = AccY / 16384.0;
  AccZ = AccZ / 16384.0;

  accAngleX = (atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / PI) - 0.58;
  accAngleY = (atan(-1 * AccX / sqrt(pow(AccY, 2) + pow(AccZ, 2))) * 180 / PI) + 1.58;

  previousTime = currentTime;
  currentTime = millis();
  elapsedTime = (currentTime - previousTime) / 1000;
  
  GyroX = Wire.read()<<8 | Wire.read();
  GyroY = Wire.read()<<8 | Wire.read();
  GyroZ = Wire.read()<<8 | Wire.read();

  GyroX = GyroX / 131.0 + 0.56;
  GyroY = GyroY / 131.0 - 2;
  GyroZ = GyroZ / 131.0 + 0.79;

  gyroAngleX = gyroAngleX + GyroX * elapsedTime;
  gyroAngleY = gyroAngleY + GyroY * elapsedTime;
  gyroAngleZ = gyroAngleZ + GyroZ * elapsedTime;

  yaw =  yaw + GyroZ * elapsedTime;
  roll = 0.96 * gyroAngleX + 0.04 * accAngleX;
  pitch = 0.96 * gyroAngleY + 0.04 * accAngleY;
  
  // print out data
  Serial.print("aX = "); Serial.print(gyroAngleX);
  Serial.print(" | aY = "); Serial.print(gyroAngleY);
  Serial.print(" | aZ = "); Serial.print(gyroAngleZ);
  Serial.println();
  
  // delay
  delay(1000);
}
