#include <Adafruit_CircuitPlayground.h>

float Z;
float dv;
float v = 0;

void setup() {
  Serial.begin(9600);
  CircuitPlayground.begin();
}

void loop() {
  Z = CircuitPlayground.motionZ();

  if (Z > -2 && Z < 2){
    Z = 0;
  }
  dv = Z * 0.01;
  v = v + dv;
  
  Serial.print("  velocity: ");
  Serial.println(v);

  delay(10);
}
