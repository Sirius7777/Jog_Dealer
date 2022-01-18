#include <Adafruit_CircuitPlayground.h>

#define rate 20

float Z;
float dv;
float v = 0;

int colorIndex;
int startIndex;

uint32_t colors[] = {
  0xff0000,   
  0xff4500,
  0xffff00,
  0x008000,
  0xf0fff0,
  0x00ffff,
  0x000080,
  0x9400d3,
  0xdc143c,
  0x000000
};

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  CircuitPlayground.setBrightness(30);
  startIndex = 0;
}

void loop() {
  Z = CircuitPlayground.motionZ();

  if (Z > -2 && Z < 2){
    Z = 0;
  }
  dv = Z * 0.01;
  v = v + dv;

  if (v < 5){
    CircuitPlayground.setPixelColor(0, 0xff0000);
    CircuitPlayground.setPixelColor(1, 0x000000);
    CircuitPlayground.setPixelColor(2, 0x000000);
    CircuitPlayground.setPixelColor(3, 0x000000);
    CircuitPlayground.setPixelColor(4, 0x000000);
    CircuitPlayground.setPixelColor(5, 0x000000);
    CircuitPlayground.setPixelColor(6, 0x000000);
    CircuitPlayground.setPixelColor(7, 0x000000);
    CircuitPlayground.setPixelColor(8, 0x000000);
    CircuitPlayground.setPixelColor(9, 0x000000);
  }else if (v < 10){
    CircuitPlayground.setPixelColor(0, 0xff0000);
    CircuitPlayground.setPixelColor(1, 0xff4500);
    CircuitPlayground.setPixelColor(2, 0x000000);
    CircuitPlayground.setPixelColor(3, 0x000000);
    CircuitPlayground.setPixelColor(4, 0x000000);
    CircuitPlayground.setPixelColor(5, 0x000000);
    CircuitPlayground.setPixelColor(6, 0x000000);
    CircuitPlayground.setPixelColor(7, 0x000000);
    CircuitPlayground.setPixelColor(8, 0x000000);
    CircuitPlayground.setPixelColor(9, 0x000000);
  }else if (v < 15){
    CircuitPlayground.setPixelColor(0, 0xff0000);
    CircuitPlayground.setPixelColor(1, 0xff4500);
    CircuitPlayground.setPixelColor(2, 0xffff00);
    CircuitPlayground.setPixelColor(3, 0x000000);
    CircuitPlayground.setPixelColor(4, 0x000000);
    CircuitPlayground.setPixelColor(5, 0x000000);
    CircuitPlayground.setPixelColor(6, 0x000000);
    CircuitPlayground.setPixelColor(7, 0x000000);
    CircuitPlayground.setPixelColor(8, 0x000000);
    CircuitPlayground.setPixelColor(9, 0x000000);
  }else if (v < 20){
    CircuitPlayground.setPixelColor(0, 0xff0000);
    CircuitPlayground.setPixelColor(1, 0xff4500);
    CircuitPlayground.setPixelColor(2, 0xffff00);
    CircuitPlayground.setPixelColor(3, 0x008000);
    CircuitPlayground.setPixelColor(4, 0x000000);
    CircuitPlayground.setPixelColor(5, 0x000000);
    CircuitPlayground.setPixelColor(6, 0x000000);
    CircuitPlayground.setPixelColor(7, 0x000000);
    CircuitPlayground.setPixelColor(8, 0x000000);
    CircuitPlayground.setPixelColor(9, 0x000000);
  }else if (v < 25){
    CircuitPlayground.setPixelColor(0, 0xff0000);
    CircuitPlayground.setPixelColor(1, 0xff4500);
    CircuitPlayground.setPixelColor(2, 0xffff00);
    CircuitPlayground.setPixelColor(3, 0x008000);
    CircuitPlayground.setPixelColor(4, 0xf0fff0);
    CircuitPlayground.setPixelColor(5, 0x000000);
    CircuitPlayground.setPixelColor(6, 0x000000);
    CircuitPlayground.setPixelColor(7, 0x000000);
    CircuitPlayground.setPixelColor(8, 0x000000);
    CircuitPlayground.setPixelColor(9, 0x000000);
  }else if (v < 30){
    CircuitPlayground.setPixelColor(0, 0xff0000);
    CircuitPlayground.setPixelColor(1, 0xff4500);
    CircuitPlayground.setPixelColor(2, 0xffff00);
    CircuitPlayground.setPixelColor(3, 0x008000);
    CircuitPlayground.setPixelColor(4, 0xf0fff0);
    CircuitPlayground.setPixelColor(5, 0x00ffff);
    CircuitPlayground.setPixelColor(6, 0x000000);
    CircuitPlayground.setPixelColor(7, 0x000000);
    CircuitPlayground.setPixelColor(8, 0x000000);
    CircuitPlayground.setPixelColor(9, 0x000000);
  }else if (v < 35){
    CircuitPlayground.setPixelColor(0, 0xff0000);
    CircuitPlayground.setPixelColor(1, 0xff4500);
    CircuitPlayground.setPixelColor(2, 0xffff00);
    CircuitPlayground.setPixelColor(3, 0x008000);
    CircuitPlayground.setPixelColor(4, 0xf0fff0);
    CircuitPlayground.setPixelColor(5, 0x00ffff);
    CircuitPlayground.setPixelColor(6, 0x000080);
    CircuitPlayground.setPixelColor(7, 0x000000);
    CircuitPlayground.setPixelColor(8, 0x000000);
    CircuitPlayground.setPixelColor(9, 0x000000);
  }else if (v < 40){
    CircuitPlayground.setPixelColor(0, 0xff0000);
    CircuitPlayground.setPixelColor(1, 0xff4500);
    CircuitPlayground.setPixelColor(2, 0xffff00);
    CircuitPlayground.setPixelColor(3, 0x008000);
    CircuitPlayground.setPixelColor(4, 0xf0fff0);
    CircuitPlayground.setPixelColor(5, 0x00ffff);
    CircuitPlayground.setPixelColor(6, 0x000080);
    CircuitPlayground.setPixelColor(7, 0x9400d3);
    CircuitPlayground.setPixelColor(8, 0x000000);
    CircuitPlayground.setPixelColor(9, 0x000000);
  }else if (v < 45){
    CircuitPlayground.setPixelColor(0, 0xff0000);
    CircuitPlayground.setPixelColor(1, 0xff4500);
    CircuitPlayground.setPixelColor(2, 0xffff00);
    CircuitPlayground.setPixelColor(3, 0x008000);
    CircuitPlayground.setPixelColor(4, 0xf0fff0);
    CircuitPlayground.setPixelColor(5, 0x00ffff);
    CircuitPlayground.setPixelColor(6, 0x000080);
    CircuitPlayground.setPixelColor(7, 0x9400d3);
    CircuitPlayground.setPixelColor(8, 0xdc143c);
    CircuitPlayground.setPixelColor(9, 0x000000);
  }else {
    colorIndex = startIndex;
    
    for (int pixel=0; pixel<10; pixel++) {
    CircuitPlayground.setPixelColor(pixel, colors[colorIndex]);
    colorIndex++;
    if (colorIndex > 9) colorIndex = 0;
    }
    startIndex++;
    if (startIndex > 9) startIndex = 0;
    delay(rate);
  }
  delay(rate);
}
