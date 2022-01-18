#include <Adafruit_NeoPixel.h>
#include <Adafruit_CircuitPlayground.h>

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
    strip.fill(strip.Color(255, 0, 0), 0, i);
    if(i != 1){
      strip.fill(strip.Color(0, 0, 0), 0, i-1);
    }else{
      strip.fill(strip.Color(0, 0, 0), 0, 32);
      strip.fill(strip.Color(255, 0, 0), 0, 1);
    }
    strip.show();
    delay(rate);
  }
}
