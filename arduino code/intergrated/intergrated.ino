#include "Timer.h"
#include <Adafruit_NeoPixel.h>
Timer t;

unsigned int buzzTime = 2000; //ms

const int trigPin = 7; //set pin variables
const int echoPin = 6;

int trigState = LOW; //state of trigPin
int interval = 1; // interval in milliseconds at which trigPin turns on
int interval2 = 1000; //time in milliseconds at which the distance is printed in serial monitors
int printState = LOW; //whether or not to print distance
unsigned long previousMillis = 0; //microsecond at which the pin was last writen

byte buzzer = A0; //vibration module

unsigned long previous = 0;

//LED
#define ledPin 8
#define ledCount 3
Adafruit_NeoPixel strip (ledCount, ledPin, NEO_GRB + NEO_KHZ800);

//cap
#define ctsPin_left 5
#define ctsPin_right 4
unsigned long capprevious = 0;
bool start_left = false;
bool start_right = false;
int count = 0;

void setup() {
  Serial.begin(9600); //begin serial communication
  pinMode(trigPin,OUTPUT); //set pinmodes
  pinMode(echoPin,INPUT);
  
  pinMode(buzzer, OUTPUT);

  strip.begin();
  strip.show();
  strip.setBrightness(50);

  pinMode(ctsPin_left, INPUT);
  pinMode(ctsPin_right, INPUT);
}

void loop()
{
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
      strip.fill(strip.Color(255,215,0), 1, strip.numPixels()-1);
      strip.show();
    }
    if(current - capprevious >= 900){
      capprevious = current;
      count++;
//      Serial.println(count);
      if (count == 8) {
        start_right = false;
        count = 0;
        strip.fill(strip.Color(0,0,0),1,strip.numPixels()-1);
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
