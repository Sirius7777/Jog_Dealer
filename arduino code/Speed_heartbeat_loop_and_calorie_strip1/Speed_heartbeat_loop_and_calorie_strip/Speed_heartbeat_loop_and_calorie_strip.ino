#include <Wire.h>
#include <Adafruit_NeoPixel.h>

#define HEARTBEAT_PIN    3
#define HEARTBEAT_COUNT 13
#define CALORIE_PIN      2
#define CALORIE_COUNT   15

const int MPU_ADDR = 0x68;
float AccX, AccY, AccZ;
float elapsedTime, currentTime, previousTime;
float v = 0.0;
int abv;
int runningTime = 0;
int rate;

int i = 0;
int moveTime = 0;

bool runLight = true;
int nextTimer = 0;

int animTime;

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

  nextTimer = millis() ;
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

  
  v = v + AccZ * elapsedTime;
  abv = abs(v);
  if (abv == 0){
    abv = 1;
  }else{
    runningTime = runningTime + elapsedTime;
  }
  if (abv > 2000){abv = 2000;}
Serial.println(nextTimer + animTime > millis());
  rate = 5000 / abv;
  animTime = 2000 / abv;
if(runLight == true){
  if(nextTimer + animTime < millis()){
    strip1.clear();
      strip1.setPixelColor(i, strip1.Color(255, 0, 0));
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
        i++;
        if(i>13){i=0; }
        nextTimer = millis();
    }

  }

  strip2.clear();
  strip2.setPixelColor(0, strip1.Color(0, 255, 0));
  strip2.setPixelColor(1, strip1.Color(0, 255, 0));
  strip2.setPixelColor(2, strip1.Color(0, 255, 0));
  strip2.setPixelColor(3, strip1.Color(0, 255, 255));
  strip2.setPixelColor(4, strip1.Color(0, 255, 255));
  strip2.setPixelColor(5, strip1.Color(0, 255, 255));
  strip2.setPixelColor(6, strip1.Color(255, 255, 255));
  strip2.setPixelColor(7, strip1.Color(255, 255, 255));
  strip2.setPixelColor(8, strip1.Color(255, 255, 255));
  strip2.setPixelColor(9, strip1.Color(255, 0, 255));
  strip2.setPixelColor(10, strip1.Color(255, 0, 255));
  strip2.setPixelColor(11, strip1.Color(255, 0, 255));
  strip2.setPixelColor(12, strip1.Color(255, 0, 0));
  strip2.setPixelColor(13, strip1.Color(255, 0, 0));
  strip2.setPixelColor(14, strip1.Color(255, 0, 0));
  if (abv > 5){
    moveTime = moveTime + 1;
    if (moveTime > 2500){
      strip2.setPixelColor(0, strip1.Color(0, 0, 0));
      strip2.setPixelColor(1, strip1.Color(0, 0, 0));
      strip2.setPixelColor(2, strip1.Color(0, 0, 0));
      strip2.setPixelColor(3, strip1.Color(0, 0, 0));
      strip2.setPixelColor(4, strip1.Color(0, 0, 0));
      strip2.setPixelColor(5, strip1.Color(0, 0, 0));
      strip2.setPixelColor(6, strip1.Color(0, 0, 0));
      strip2.setPixelColor(7, strip1.Color(0, 0, 0));
      strip2.setPixelColor(8, strip1.Color(0, 0, 0));
      strip2.setPixelColor(9, strip1.Color(0, 0, 0));
      strip2.setPixelColor(10, strip1.Color(0, 0, 0));
      strip2.setPixelColor(11, strip1.Color(0, 0, 0));
      strip2.setPixelColor(12, strip1.Color(0, 0, 0));
      strip2.setPixelColor(13, strip1.Color(0, 0, 0));
      strip2.setPixelColor(14, strip1.Color(0, 0, 0));
    }else if (moveTime > 2000){
      strip2.setPixelColor(0, strip1.Color(0, 255, 0));
      strip2.setPixelColor(1, strip1.Color(0, 255, 0));
      strip2.setPixelColor(2, strip1.Color(0, 255, 0));
      strip2.setPixelColor(3, strip1.Color(0, 0, 0));
      strip2.setPixelColor(4, strip1.Color(0, 0, 0));
      strip2.setPixelColor(5, strip1.Color(0, 0, 0));
      strip2.setPixelColor(6, strip1.Color(0, 0, 0));
      strip2.setPixelColor(7, strip1.Color(0, 0, 0));
      strip2.setPixelColor(8, strip1.Color(0, 0, 0));
      strip2.setPixelColor(9, strip1.Color(0, 0, 0));
      strip2.setPixelColor(10, strip1.Color(0, 0, 0));
      strip2.setPixelColor(11, strip1.Color(0, 0, 0));
      strip2.setPixelColor(12, strip1.Color(0, 0, 0));
      strip2.setPixelColor(13, strip1.Color(0, 0, 0));
      strip2.setPixelColor(14, strip1.Color(0, 0, 0));
    }else if (moveTime > 1500){
      strip2.setPixelColor(0, strip1.Color(0, 255, 0));
      strip2.setPixelColor(1, strip1.Color(0, 255, 0));
      strip2.setPixelColor(2, strip1.Color(0, 255, 0));
      strip2.setPixelColor(3, strip1.Color(0, 255, 255));
      strip2.setPixelColor(4, strip1.Color(0, 255, 255));
      strip2.setPixelColor(5, strip1.Color(0, 255, 255));
      strip2.setPixelColor(6, strip1.Color(0, 0, 0));
      strip2.setPixelColor(7, strip1.Color(0, 0, 0));
      strip2.setPixelColor(8, strip1.Color(0, 0, 0));
      strip2.setPixelColor(9, strip1.Color(0, 0, 0));
      strip2.setPixelColor(10, strip1.Color(0, 0, 0));
      strip2.setPixelColor(11, strip1.Color(0, 0, 0));
      strip2.setPixelColor(12, strip1.Color(0, 0, 0));
      strip2.setPixelColor(13, strip1.Color(0, 0, 0));
      strip2.setPixelColor(14, strip1.Color(0, 0, 0));
    }else if (moveTime > 1000){
      strip2.setPixelColor(0, strip1.Color(0, 255, 0));
      strip2.setPixelColor(1, strip1.Color(0, 255, 0));
      strip2.setPixelColor(2, strip1.Color(0, 255, 0));
      strip2.setPixelColor(3, strip1.Color(0, 255, 255));
      strip2.setPixelColor(4, strip1.Color(0, 255, 255));
      strip2.setPixelColor(5, strip1.Color(0, 255, 255));
      strip2.setPixelColor(6, strip1.Color(255, 255, 255));
      strip2.setPixelColor(7, strip1.Color(255, 255, 255));
      strip2.setPixelColor(8, strip1.Color(255, 255, 255));
      strip2.setPixelColor(9, strip1.Color(0, 0, 0));
      strip2.setPixelColor(10, strip1.Color(0, 0, 0));
      strip2.setPixelColor(11, strip1.Color(0, 0, 0));
      strip2.setPixelColor(12, strip1.Color(0, 0, 0));
      strip2.setPixelColor(13, strip1.Color(0, 0, 0));
      strip2.setPixelColor(14, strip1.Color(0, 0, 0));
    }else if (moveTime > 500){
      strip2.setPixelColor(0, strip1.Color(0, 255, 0));
      strip2.setPixelColor(1, strip1.Color(0, 255, 0));
      strip2.setPixelColor(2, strip1.Color(0, 255, 0));
      strip2.setPixelColor(3, strip1.Color(0, 255, 255));
      strip2.setPixelColor(4, strip1.Color(0, 255, 255));
      strip2.setPixelColor(5, strip1.Color(0, 255, 255));
      strip2.setPixelColor(6, strip1.Color(255, 255, 255));
      strip2.setPixelColor(7, strip1.Color(255, 255, 255));
      strip2.setPixelColor(8, strip1.Color(255, 255, 255));
      strip2.setPixelColor(9, strip1.Color(255, 0, 255));
      strip2.setPixelColor(10, strip1.Color(255, 0, 255));
      strip2.setPixelColor(11, strip1.Color(255, 0, 255));
      strip2.setPixelColor(12, strip1.Color(0, 0, 0));
      strip2.setPixelColor(13, strip1.Color(0, 0, 0));
      strip2.setPixelColor(14, strip1.Color(0, 0, 0));
    }else{
      strip2.setPixelColor(0, strip1.Color(0, 255, 0));
      strip2.setPixelColor(1, strip1.Color(0, 255, 0));
      strip2.setPixelColor(2, strip1.Color(0, 255, 0));
      strip2.setPixelColor(3, strip1.Color(0, 255, 255));
      strip2.setPixelColor(4, strip1.Color(0, 255, 255));
      strip2.setPixelColor(5, strip1.Color(0, 255, 255));
      strip2.setPixelColor(6, strip1.Color(255, 255, 255));
      strip2.setPixelColor(7, strip1.Color(255, 255, 255));
      strip2.setPixelColor(8, strip1.Color(255, 255, 255));
      strip2.setPixelColor(9, strip1.Color(255, 0, 255));
      strip2.setPixelColor(10, strip1.Color(255, 0, 255));
      strip2.setPixelColor(11, strip1.Color(255, 0, 255));
      strip2.setPixelColor(12, strip1.Color(255, 0, 0));
      strip2.setPixelColor(13, strip1.Color(255, 0, 0));
      strip2.setPixelColor(14, strip1.Color(255, 0, 0));
    }
    strip2.show();
  }
  
  }
