#include <Wire.h>
#include <Adafruit_NeoPixel.h>

#define HEARTBEAT_PIN    6
#define HEARTBEAT_COUNT 32
#define CALORIE_PIN      7
#define CALORIE_COUNT   32

const int MPU_ADDR = 0x68;
float AccX, AccY, AccZ;
float elapsedTime, currentTime, previousTime;
float v;
int abv;
int runningTime = 0;
int rate;

Adafruit_NeoPixel strip1 (HEARTBEAT_COUNT, HEARTBEAT_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 (CALORIE_COUNT, CALORIE_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip1.begin();
  strip1.show();
  strip1.setBrightness(225);
  strip2.begin();
  strip2.show();
  strip2.setBrightness(225);
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
  AccZ = AccZ / 1638.4;

  previousTime = currentTime;
  currentTime = millis();
  elapsedTime = (currentTime - previousTime) / 1000;

  v = 0.0;
  v = v + AccZ * elapsedTime;
  abv = abs(v);
  if (abv == 0){
    abv = 1;
  }else{
    runningTime = runningTime + elapsedTime;
  }

  rate = 5000 / abv;

  for(int i=1;i<33;i++){
    if(i < 2){
      strip1.fill(strip1.Color(64, 0, 0), 0, 32);
      strip1.fill(strip1.Color(15, 0, 0), 0, 31);
      strip1.fill(strip1.Color(8, 0, 0), 0, 30);
      strip1.fill(strip1.Color(0, 0, 0), 0, 29);
      strip1.fill(strip1.Color(255, 0, 0), 0, 1);
    }else if(i < 3){
      strip1.fill(strip1.Color(15, 0, 0), 0, 32);
      strip1.fill(strip1.Color(8, 0, 0), 0, 31);
      strip1.fill(strip1.Color(0, 0, 0), 0, 30);
      strip1.fill(strip1.Color(255, 0, 0), 0, 2);
      strip1.fill(strip1.Color(64, 0, 0), 0, 1);
    }else if(i < 4){
      strip1.fill(strip1.Color(8, 0, 0), 0, 32);
      strip1.fill(strip1.Color(0, 0, 0), 0, 31);
      strip1.fill(strip1.Color(255, 0, 0), 0, 3);
      strip1.fill(strip1.Color(64, 0, 0), 0, 2);
      strip1.fill(strip1.Color(15, 0, 0), 0, 1);
    }else if(i<5){
      strip1.fill(strip1.Color(0, 0, 0), 0, 32);
      strip1.fill(strip1.Color(255, 0, 0), 0, 4);
      strip1.fill(strip1.Color(64, 0, 0), 0, 3);
      strip1.fill(strip1.Color(15, 0, 0), 0, 2);
      strip1.fill(strip1.Color(8, 0, 0), 0, 1);
    }else{
      strip1.fill(strip1.Color(255, 0, 0), 0, i);
      strip1.fill(strip1.Color(64, 0, 0), 0, i-1);
      strip1.fill(strip1.Color(15, 0, 0), 0, i-2);
      strip1.fill(strip1.Color(8, 0, 0), 0, i-3);
      strip1.fill(strip1.Color(0, 0, 0), 0, i-4);
    }
  
  Serial.print(" | aZ = "); Serial.print(AccZ);
  Serial.println();
  Serial.print(currentTime);Serial.print(", ");Serial.print(previousTime);Serial.print(", ");Serial.print(elapsedTime);
  Serial.println();
  Serial.print(v);
  Serial.println();
  Serial.print(rate);
  Serial.println();
  Serial.print(runningTime);
  Serial.println();

  strip1.show();
  }
  delay(rate);
}
