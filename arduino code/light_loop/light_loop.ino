#include <Adafruit_CircuitPlayground.h>

#define ROTATION_RATE   200  //Delay

float volume;  //Define the volume

//Define the color set
uint32_t colors[] = {
  0xFF0000,   
  0xFF5500,
  0xFFFF00,
  0x00FF00,
  0x0000FF,
  0xFF00FF,
  0x008080,
  0x808000,
  0x00F0F0,
  0xF0F000
};

int colorIndex;
int startIndex;

void setup(){
  Serial.begin(9600);
  CircuitPlayground.begin();
  CircuitPlayground.setBrightness(30);
  startIndex = 0;
}

void loop(){

  volume = CircuitPlayground.mic.soundPressureLevel(10);

  if (volume<40){
    CircuitPlayground.setPixelColor(0, 0xFF0000);
    CircuitPlayground.setPixelColor(1, 0x000000);
    CircuitPlayground.setPixelColor(2, 0x000000);
    CircuitPlayground.setPixelColor(3, 0x000000);
    CircuitPlayground.setPixelColor(4, 0x000000);
    CircuitPlayground.setPixelColor(5, 0x000000);
    CircuitPlayground.setPixelColor(6, 0x000000);
    CircuitPlayground.setPixelColor(7, 0x000000);
    CircuitPlayground.setPixelColor(8, 0x000000);
    CircuitPlayground.setPixelColor(9, 0x000000);
  }else if (volume<50){
    CircuitPlayground.setPixelColor(0, 0xFF0000);
    CircuitPlayground.setPixelColor(1, 0xFF5500);
    CircuitPlayground.setPixelColor(2, 0x000000);
    CircuitPlayground.setPixelColor(3, 0x000000);
    CircuitPlayground.setPixelColor(4, 0x000000);
    CircuitPlayground.setPixelColor(5, 0x000000);
    CircuitPlayground.setPixelColor(6, 0x000000);
    CircuitPlayground.setPixelColor(7, 0x000000);
    CircuitPlayground.setPixelColor(8, 0x000000);
    CircuitPlayground.setPixelColor(9, 0x000000);
  }else if (volume<55){
    CircuitPlayground.setPixelColor(0, 0xFF0000);
    CircuitPlayground.setPixelColor(1, 0xFF5500);
    CircuitPlayground.setPixelColor(2, 0xFFFF00);
    CircuitPlayground.setPixelColor(3, 0x000000);
    CircuitPlayground.setPixelColor(4, 0x000000);
    CircuitPlayground.setPixelColor(5, 0x000000);
    CircuitPlayground.setPixelColor(6, 0x000000);
    CircuitPlayground.setPixelColor(7, 0x000000);
    CircuitPlayground.setPixelColor(8, 0x000000);
    CircuitPlayground.setPixelColor(9, 0x000000);
  }else if (volume<60){
    CircuitPlayground.setPixelColor(0, 0xFF0000);
    CircuitPlayground.setPixelColor(1, 0xFF5500);
    CircuitPlayground.setPixelColor(2, 0xFFFF00);
    CircuitPlayground.setPixelColor(3, 0x00FF00);
    CircuitPlayground.setPixelColor(4, 0x000000);
    CircuitPlayground.setPixelColor(5, 0x000000);
    CircuitPlayground.setPixelColor(6, 0x000000);
    CircuitPlayground.setPixelColor(7, 0x000000);
    CircuitPlayground.setPixelColor(8, 0x000000);
    CircuitPlayground.setPixelColor(9, 0x000000);
  }else if (volume<65){
    CircuitPlayground.setPixelColor(0, 0xFF0000);
    CircuitPlayground.setPixelColor(1, 0xFF5500);
    CircuitPlayground.setPixelColor(2, 0xFFFF00);
    CircuitPlayground.setPixelColor(3, 0x00FF00);
    CircuitPlayground.setPixelColor(4, 0x0000FF);
    CircuitPlayground.setPixelColor(5, 0x000000);
    CircuitPlayground.setPixelColor(6, 0x000000);
    CircuitPlayground.setPixelColor(7, 0x000000);
    CircuitPlayground.setPixelColor(8, 0x000000);
    CircuitPlayground.setPixelColor(9, 0x000000);
  }else if (volume<70){
    CircuitPlayground.setPixelColor(0, 0xFF0000);
    CircuitPlayground.setPixelColor(1, 0xFF5500);
    CircuitPlayground.setPixelColor(2, 0xFFFF00);
    CircuitPlayground.setPixelColor(3, 0x00FF00);
    CircuitPlayground.setPixelColor(4, 0x0000FF);
    CircuitPlayground.setPixelColor(5, 0xFF00FF);
    CircuitPlayground.setPixelColor(6, 0x000000);
    CircuitPlayground.setPixelColor(7, 0x000000);
    CircuitPlayground.setPixelColor(8, 0x000000);
    CircuitPlayground.setPixelColor(9, 0x000000);
  }else if (volume<75){
    CircuitPlayground.setPixelColor(0, 0xFF0000);
    CircuitPlayground.setPixelColor(1, 0xFF5500);
    CircuitPlayground.setPixelColor(2, 0xFFFF00);
    CircuitPlayground.setPixelColor(3, 0x00FF00);
    CircuitPlayground.setPixelColor(4, 0x0000FF);
    CircuitPlayground.setPixelColor(5, 0xFF00FF);
    CircuitPlayground.setPixelColor(6, 0x008080);
    CircuitPlayground.setPixelColor(7, 0x000000);
    CircuitPlayground.setPixelColor(8, 0x000000);
    CircuitPlayground.setPixelColor(9, 0x000000);
  }else if (volume<80){
    CircuitPlayground.setPixelColor(0, 0xFF0000);
    CircuitPlayground.setPixelColor(1, 0xFF5500);
    CircuitPlayground.setPixelColor(2, 0xFFFF00);
    CircuitPlayground.setPixelColor(3, 0x00FF00);
    CircuitPlayground.setPixelColor(4, 0x0000FF);
    CircuitPlayground.setPixelColor(5, 0xFF00FF);
    CircuitPlayground.setPixelColor(6, 0x008080);
    CircuitPlayground.setPixelColor(7, 0x808000);
    CircuitPlayground.setPixelColor(8, 0x000000);
    CircuitPlayground.setPixelColor(9, 0x000000);
  }else{
    colorIndex = startIndex;
    
    for (int pixel=0; pixel<10; pixel++) {
    CircuitPlayground.setPixelColor(pixel, colors[colorIndex]);
    colorIndex++;
    if (colorIndex > 9) colorIndex = 0;
    }
    startIndex++;
    if (startIndex > 9) startIndex = 0;
    delay(ROTATION_RATE);
  }

  delay(ROTATION_RATE);
}
