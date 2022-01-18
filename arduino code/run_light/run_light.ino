#include <Adafruit_CircuitPlayground.h>

float Z;
float dv;
float v = 0;

int abv;
int rate;

int colorIndex;
int startIndex;

uint32_t colors[] = {
  0xFF0000,   
  0x400000,
  0x0F0000,
  0x080000,
  0x000000,
  0x000000,
  0x000000,
  0x000000,
  0x000000,
  0x000000
};

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
  CircuitPlayground.setBrightness(60);
  startIndex = 0;
}


void loop() {
  Z = CircuitPlayground.motionZ();

  if (Z > -2 && Z < 2){
    Z = 0;
  }
  dv = Z * 0.01;
  v = v + dv;

  abv = abs((int)v);
  int i = 2000/abv;
  rate = i;

  Serial.print("  velocity: ");
  Serial.println(abv);

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
