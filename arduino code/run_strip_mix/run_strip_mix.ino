#include <Adafruit_NeoPixel.h>
#include <Adafruit_CircuitPlayground.h>

#define LED_PIN    6
#define LED_COUNT 32

Adafruit_NeoPixel strip (LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  //CircuitPlayground.begin();
  strip.begin();
  strip.show();
  strip.setBrightness(225);
  Serial.begin(9600);
}

void loop() {
  /*float Z = CircuitPlayground.motionZ();

  if (Z > -2 && Z < 2){
    Z = 0;
  }
  float dv = Z * 0.01;
  float v = 0;
  v = v + dv;
  int abv = abs((int)v);

  int rate = 2000/abv;*/
  
  RunStripHeartbeat(30);
  //RunStripLoop(rate);
}

void RunStripHeartbeat(int rate) {
  for(int i=1;i<33;i++){
    if(i < 2){
      strip.fill(strip.Color(64, 0, 0), 0, 32);
      strip.fill(strip.Color(15, 0, 0), 0, 31);
      strip.fill(strip.Color(8, 0, 0), 0, 30);
      strip.fill(strip.Color(0, 0, 0), 0, 29);
      strip.fill(strip.Color(255, 0, 0), 0, 1);
    }else if(i < 3){
      strip.fill(strip.Color(15, 0, 0), 0, 32);
      strip.fill(strip.Color(8, 0, 0), 0, 31);
      strip.fill(strip.Color(0, 0, 0), 0, 30);
      strip.fill(strip.Color(255, 0, 0), 0, 2);
      strip.fill(strip.Color(64, 0, 0), 0, 1);
    }else if(i < 4){
      strip.fill(strip.Color(8, 0, 0), 0, 32);
      strip.fill(strip.Color(0, 0, 0), 0, 31);
      strip.fill(strip.Color(255, 0, 0), 0, 3);
      strip.fill(strip.Color(64, 0, 0), 0, 2);
      strip.fill(strip.Color(15, 0, 0), 0, 1);
    }else if(i<5){
      strip.fill(strip.Color(0, 0, 0), 0, 32);
      strip.fill(strip.Color(255, 0, 0), 0, 4);
      strip.fill(strip.Color(64, 0, 0), 0, 3);
      strip.fill(strip.Color(15, 0, 0), 0, 2);
      strip.fill(strip.Color(8, 0, 0), 0, 1);
    }else{
      strip.fill(strip.Color(255, 0, 0), 0, i);
      strip.fill(strip.Color(64, 0, 0), 0, i-1);
      strip.fill(strip.Color(15, 0, 0), 0, i-2);
      strip.fill(strip.Color(8, 0, 0), 0, i-3);
      strip.fill(strip.Color(0, 0, 0), 0, i-4);
    }
    
    strip.show();
    delay(rate);
  }
}

void RunStripLoop(int rate){
  int R = 0;
  int G = 0;
  int B = 0;

  G = 0;
  for(int i=0;i<255;i++){
    R = 255;
    G = G + 1;
    B = 0;
    strip.fill(strip.Color(R, G, B), 0, 32);
    strip.show();
    delay(rate);
  }

  R = 255;
  for(int i=0;i<255;i++){
    R = R - 1;
    G = 255;
    B = 0;
    strip.fill(strip.Color(R, G, B), 0, 32);
    strip.show();
    delay(rate);
  }

  B = 0;
  for(int i=0;i<255;i++){
    R = 0;
    G = 255;
    B = B + 1;
    strip.fill(strip.Color(R, G, B), 0, 32);
    strip.show();
    delay(rate);
  }

  G = 255;
  for(int i=0;i<255;i++){
    R = 0;
    G = G - 1;
    B = 255;
    strip.fill(strip.Color(R, G, B), 0, 32);
    strip.show();
    delay(rate);
  }

  R = 0;
  for(int i=0;i<255;i++){
    R = R + 1;
    G = 0;
    B = 255;
    strip.fill(strip.Color(R, G, B), 0, 32);
    strip.show();
    delay(rate);
  }

  B = 255;
  for(int i=0;i<255;i++){
    R = 255;
    G = 0;
    B = B - 1;
    strip.fill(strip.Color(R, G, B), 0, 32);
    strip.show();
    delay(rate);
  }
}
