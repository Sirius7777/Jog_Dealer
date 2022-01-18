#include <Adafruit_NeoPixel.h>

#define LED_PIN    6
#define LED_COUNT 32

int rate = 30;

Adafruit_NeoPixel strip (LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(225);
  Serial.begin(9600);
}

void loop() {
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
