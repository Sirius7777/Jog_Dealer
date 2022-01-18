#include "Timer.h"
#include <Wire.h>
#include <Adafruit_NeoPixel.h>

Timer t;

#define HEARTBEAT_PIN    3
#define HEARTBEAT_COUNT 13
#define CALORIE_PIN      2
#define CALORIE_COUNT   15
#define ledPin 8
#define ledCount 3
#define ctsPin_left 5
#define ctsPin_right 4
const int echoPin = 6;
const int trigPin = 7;
byte buzzer = A0;

unsigned int buzzTime = 2000;
const int MPU_ADDR = 0x68;
float AccX, AccY, AccZ;
float elapsedTime, currentTime, previousTime;
float v = 0.0;
float sqrv;
int i = 0;
int moveTime = 0;
unsigned long nextTimer = 0;
unsigned long animTime;

int trigState = LOW;
int interval = 1;
int interval2 = 1000;
int printState = LOW;
unsigned long previousMillis = 0;
unsigned long previous = 0;
unsigned long capprevious = 0;
bool start_left = false;
bool start_right = false;
int count = 0;

Adafruit_NeoPixel strip1 (HEARTBEAT_COUNT, HEARTBEAT_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 (CALORIE_COUNT, CALORIE_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip (ledCount, ledPin, NEO_GRB + NEO_KHZ800);

void setup() {
  strip1.begin();
  strip1.show();
  strip1.setBrightness(200);
  strip2.begin();
  strip2.show();
  strip2.setBrightness(200);
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  nextTimer = millis();
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(buzzer, OUTPUT);
  strip.begin();
  strip.show();
  strip.setBrightness(200);
  pinMode(ctsPin_left, INPUT);
  pinMode(ctsPin_right, INPUT);
  strip1.setPixelColor(i, strip1.Color(255, 0, 0));
  strip1.show();
}

void loop(){
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
  
  if (v == 0){v = 0.01;}
  sqrv = sqrt(abs(v));
  animTime = 200 / sqrv;
  Serial.println(sqrv);
  HeartbeatStrip();
  
  CalorieStrip();
}

void HeartbeatStrip(){
  if(nextTimer + animTime < millis()){
    strip1.clear();
    strip1.setPixelColor(i, strip1.Color(255, 0, 0));
    strip1.show();
    i++;
    if(i>12){i=0;}
    nextTimer = millis();
  }
}

void CalorieStrip(){
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

  if (abs(v) > 1){
    moveTime = moveTime + 1;
    if (moveTime > 5000){
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
    }else if (moveTime > 4000){
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
    }else if (moveTime > 3000){
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
    }else if (moveTime > 2000){
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
  }else{
    moveTime = moveTime;
    if (moveTime > 5000){
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
    }else if (moveTime > 4000){
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
    }else if (moveTime > 3000){
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
    }else if (moveTime > 2000){
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
  }
  strip2.show();
}
