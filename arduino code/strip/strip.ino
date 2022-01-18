// touch for turning on external led
int LEFT_FSRPIN = 0;
int RIGHT_FSRPIN = 1;
#include <Adafruit_NeoPixel.h>

#include <Adafruit_CircuitPlayground.h>

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    6

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 14

//leave the light shining
#define FLASH_RATE    500     


#define CAP_THRESHOLD   50

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip (LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

////////////////////////////////////////////////////////////////////////////
boolean capButton(uint8_t pad) {
  if (CircuitPlayground.readCap(pad) > CAP_THRESHOLD) {
    return true;  
  } else {
    return false;
  }
}


void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(225);

  Serial.begin(9600);
}

void loop() {
//  int leftfsrADC = analogRead(LEFT_FSRPIN); // restore pressure for left
//  int rightfsrADC = analogRead(RIGHT_FSRPIN); // restore pressure for right
//
//  if (leftfsrADC != 0) {
//    float force;
//    }
  

 //brighten one by one, for each one brighten 6 times
//  if (capButton(0)) {
//    for (int i = 0; i < 6; i++) {
//      for (int j = 0; j < LED_COUNT; j++) { // didnt break
//        //brighten
//        strip.setPixelColor(i, 128, 128, 0); 
//        strip.show();
//        delay(FLASH_RATE);
//
//        //clear
//        strip.setPixelColor(i, 0, 0, 0); 
//        strip.show();
//        delay(300);
//      }
//    }
//  }
    

//brighten one by one, for a circle
//  if (capButton(0)) {
//    for (int j = 0; j < LED_COUNT; j++) {
//      for (int i = 0; i < 6; i++) { 
//        //brighten
//        strip.setPixelColor(i, 128, 128, 0); 
//        strip.show();
//        delay(FLASH_RATE);
//
//        //clear
//        strip.setPixelColor(i, 0, 0, 0); 
//        strip.show();
//        delay(300);
//      }
//    }
//  }

// left turning 
  if (capButton(0)) {
      for (int i = 0; i < 6; i++) { 
        //brighten
        strip.fill(strip.Color(128, 128, 0), 0, 10);
        strip.show();
        delay(FLASH_RATE);

        //clear
        strip.fill(strip.Color(0,0,0), 0, 10);
        strip.show();
        delay(300);
      }
  }

// right turning
  if (capButton(1)) {
      for (int i = 0; i < 6; i++) { 
        //brighten
        strip.fill(strip.Color(128, 128, 0), 4, strip.numPixels());
        strip.show();
        delay(FLASH_RATE);

        //clear
        strip.fill(strip.Color(0,0,0), 4, strip.numPixels());
        strip.show();
        delay(300);
      }
  }

}
