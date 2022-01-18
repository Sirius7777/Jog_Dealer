#include <Wire.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN    6
#define LED_COUNT 32

const int MPU_ADDR = 0x68;

float AccX, AccY, AccZ;

Adafruit_NeoPixel strip (LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(225);
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
  AccZ = AccZ / 1638.4;
  
  Serial.print("aX = "); Serial.print(AccX);
  Serial.print(" | aY = "); Serial.print(AccY);
  Serial.print(" | aZ = "); Serial.print(AccZ);
  Serial.println();
  
  delay(1000);
}
