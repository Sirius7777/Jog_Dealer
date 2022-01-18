#include <Adafruit_NeoPixel.h>

#define LED_PIN    6
#define LED_COUNT 32

int R = 0;
int G = 0;
int B = 0;

int rate = 5;

Adafruit_NeoPixel strip (LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(225);
  Serial.begin(9600);
}

void loop() {
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
