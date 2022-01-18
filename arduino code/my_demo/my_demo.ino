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

  unsigned long currentMillis = millis(); //time in milliseconds from which the code was started
  if (currentMillis-previousMillis >= interval) { //check "blink without delay" code
    previousMillis = currentMillis;
    if (trigState == LOW){
      (trigState = HIGH);
    }
    else {
      (trigState = LOW);
    }
  }
  // printing if statement
  if (currentMillis-previousMillis >= interval2) { //check "blink without delay" code
    previousMillis = currentMillis;
    if (printState == LOW){
      (printState = HIGH);
    }
    else {
      (printState = LOW);
    }
  }
  digitalWrite(trigPin,trigState);
  int duration, distance; //variables
  duration = pulseIn(echoPin,HIGH);
  distance = (duration/2) / 29.1;
  /*if (printState = HIGH){
  Serial.print(distance);
  Serial.println("cm");}*/
  
  if (distance <= 100 && distance != 0){
    Serial.print(distance);
    Serial.println("cm");
    unsigned long current = millis();
    if (current - previous >= 0 && current - previous <= 500) {
      strip.fill(strip.Color(0,0,0), 0, strip.numPixels());
      strip.show();
    } else if(current - previous >= 500 && current - previous <= 1000){
      strip.fill(strip.Color(0,0,255), 0, strip.numPixels());
      strip.show();
    }
    if(current - previous >= 900){
      previous = current;
    }
    t.pulseImmediate(buzzer,buzzTime,HIGH);
    t.update();
  } else {
    // turn off 
    strip.fill(strip.Color(0,0,0), 0, strip.numPixels());
    strip.show();
    }

  /*if (distance > 100 && distance <=150) {
    t.pulseImmediate(buzzer,buzzTime - 500, HIGH);
    t.update();
  }*/

  //cap for turning
  int ctsValue_left = digitalRead(ctsPin_left);

  if (start_left) {
    unsigned long current = millis();
    if (current - capprevious >= 0 && current -capprevious <= 500) {
      strip.fill(strip.Color(0,0,0), 2, strip.numPixels());
      strip.show();
    } else if(current - capprevious >= 500 && current - capprevious <= 1000){
      strip.fill(strip.Color(255,215,0), 0, strip.numPixels()-1);
      strip.show();
    }
    if(current - capprevious >= 900){
      capprevious = current;
      count++;
//      Serial.println(count);
      if (count == 8) {
        start_left = false;
        count = 0;
        strip.fill(strip.Color(0,0,0),0,strip.numPixels()-1);
        strip.show();
      }
    }
  }
  

  if (ctsValue_left == HIGH) {
    start_left = true;
    Serial.println("LEFT");
  }

  if (start_right) {
    unsigned long current = millis();
    if (current - capprevious >= 0 && current - capprevious <= 500) {
      strip.fill(strip.Color(0,0,0), 1, strip.numPixels()-1);
      strip.show();
    } else if(current - capprevious >= 500 && current - capprevious <= 1000){
      strip.fill(strip.Color(255,215,0), 1, strip.numPixels());
      strip.show();
    }
    if(current - capprevious >= 900){
      capprevious = current;
      count++;
//      Serial.println(count);
      if (count == 8) {
        start_right = false;
        count = 0;
        strip.fill(strip.Color(0,0,0),1,strip.numPixels());
        strip.show();
      }
    }
  }
  int ctsValue_right = digitalRead(ctsPin_right);

  if (ctsValue_right == HIGH) {
    start_right = true;
    Serial.println("RIGHT");
  }
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
