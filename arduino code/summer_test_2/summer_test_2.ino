 #include <Adafruit_NeoPixel.h>
const int FSR_PIN = A0; // Pin connected to FSR/resistor divider
const int FSR_PIN2 = A1;
const int FSR_PIN3 = A3;
const int LED_PIN1 = 7;


bool musicOn = false;
bool musicSwitchReading = false;
bool musicOn2 = false;
bool musicSwitchReading2 = false;
bool musicOn3 = false;
bool musicSwitchReading3 = false;







const float VCC = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV = 3230.0; // Measured resistance of 3.3k resistor

float force = 0;
float force2 = 0;
float force3 = 0;
//led strip details
#define LEDPIN1 7

#define NUMPIXELS 96

Adafruit_NeoPixel ledstrip1(NUMPIXELS, LEDPIN1, NEO_GRB + NEO_KHZ800);

void setup() 
{
  Serial.begin(9600);
  pinMode(FSR_PIN, INPUT);
  pinMode(FSR_PIN2, INPUT);
  pinMode(FSR_PIN3, INPUT);
  pinMode(LED_PIN1, OUTPUT);


  ledstrip1.begin();
  ledstrip1.show();
  ledstrip1.setBrightness(255); // 0 to 255


  
}

void loop() 
{
  int fsrADC = analogRead(FSR_PIN);
  // If the FSR has no pressure, the resistance will be
  // near infinite. So the voltage should be near 0.
  if (fsrADC != 0) // If the analog reading is non-zero
  {
    // Use ADC reading to calculate voltage:
    float fsrV = fsrADC * VCC / 1023.0;
    // Use voltage and static resistor value to 
    // calculate FSR resistance:
    float fsrR = R_DIV * (VCC / fsrV - 1.0);
    //Serial.println("Resistance: " + String(fsrR) + " ohms");
    // Guesstimate force based on slopes in figure 3 of
    // FSR datasheet:
//    float force;
    float fsrG = 1.0 / fsrR; // Calculate conductance
    // Break parabolic curve down into two linear slopes:
    if (fsrR <= 600) 
      force = (fsrG - 0.00075) / 0.00000032639;
    else
      force =  fsrG / 0.000000642857;


//    Serial.print(force);
//    Serial.print(" ");
    
    //Serial.println();
    
    if(force>5 and force<40)
    {
      colorWipe1(ledstrip1.Color(255, 0, 0), 19, 29);//red
      delay(100);
      colorWipe1(ledstrip1.Color(0, 0, 0), 19, 29);//no

    }
    if(force>40 and force<60)
    {
      colorWipe1(ledstrip1.Color(233, 0, 138), 13, 18); //purple
      colorWipe1(ledstrip1.Color(233, 0, 138), 30, 35); //purple
      
      delay(100);
      colorWipe1(ledstrip1.Color(0, 0, 0), 13, 18);//no
      colorWipe1(ledstrip1.Color(0, 0, 0), 30, 35);//no
    }
    if(force>60 and force<105)
    {
       colorWipe1(ledstrip1.Color(251, 255, 21), 7, 12); //yellow
       colorWipe1(ledstrip1.Color(251, 255, 21), 32, 37); //yellow
       delay(100);
       colorWipe1(ledstrip1.Color(0, 0, 0), 7, 12);//no
       colorWipe1(ledstrip1.Color(0, 0, 0), 32, 37);//no
    }
    if(force>105 and force<350)
    {
      colorWipe1(ledstrip1.Color(5, 252, 238), 0, 6);//blue
      colorWipe1(ledstrip1.Color(5, 252, 238), 38, 42);//blue
      delay(100);
      colorWipe1(ledstrip1.Color(0, 0, 0), 0, 6);//no
      colorWipe1(ledstrip1.Color(0, 0, 0), 38, 42);//no
      
    }

  
    delay(10);
    
  } else {
    force = 0;
  }

  
   int musicSwitch = 0;

//    Serial.println(force);
    
    if (force > 1 && !musicOn)
    {
      musicSwitch = 1;
      musicOn = true;
    }
    
    if (force < 1 && musicOn)
    {
      musicSwitch = 2;
      musicOn = false;
    }

  Serial.print(String(musicSwitch));
  Serial.print(" ");
  Serial.print(force);
  Serial.print(" ");
  //Serial.println();
  // add in if for the second reading
  int fsrADC2 = analogRead(FSR_PIN2);
  if (fsrADC2 != 0) // If the analog reading is non-zero
  {
    // Use ADC reading to calculate voltage:
    float fsrV2 = fsrADC2 * VCC / 1023.0;
    // Use voltage and static resistor value to 
    // calculate FSR resistance:
    float fsrR2 = R_DIV * (VCC / fsrV2 - 1.0);
    //Serial.println("Resistance: " + String(fsrR) + " ohms");
    // Guesstimate force based on slopes in figure 3 of
    // FSR datasheet:
    //float force2;
    float fsrG2 = 1.0 / fsrR2; // Calculate conductance
    // Break parabolic curve down into two linear slopes:
    if (fsrR2 <= 600) 
      force2 = (fsrG2 - 0.00075) / 0.00000032639;
    else
      force2 =  fsrG2 / 0.000000642857;
    
    //Serial.println();
    
    if(force2>5 and force2<30)
    {
      colorWipe1(ledstrip1.Color(127, 255, 0), 25, 27);//green
      colorWipe1(ledstrip1.Color(127, 255, 0), 49, 55);//green
      delay(100);
      colorWipe1(ledstrip1.Color(0, 0, 0), 25, 27);//no
      colorWipe1(ledstrip1.Color(0, 0, 0), 49, 55);//no
    }
    if(force2>30 and force2<42)
    {
      colorWipe1(ledstrip1.Color(205, 92, 92), 47, 48); //ir
      colorWipe1(ledstrip1.Color(205, 92, 92), 56, 61); //ir
      colorWipe1(ledstrip1.Color(205, 92, 92), 32, 37); //ir
      colorWipe1(ledstrip1.Color(205, 92, 92), 71, 72); //ir
      delay(100);
      colorWipe1(ledstrip1.Color(0, 0, 0), 47, 48); //no
      colorWipe1(ledstrip1.Color(0, 0, 0), 56, 61); //no
      colorWipe1(ledstrip1.Color(0, 0, 0), 32, 37); //no
      colorWipe1(ledstrip1.Color(0, 0, 0), 71, 72); //no
    }
    if(force2>42 and force2<70)
    {
       colorWipe1(ledstrip1.Color(255, 165, 0), 45, 46); //orange
       colorWipe1(ledstrip1.Color(255, 165, 0), 30, 35); //orange
       colorWipe1(ledstrip1.Color(255, 165, 0), 58, 63); //orange
       colorWipe1(ledstrip1.Color(255, 165, 0), 73, 74); //orange
       delay(100);
       colorWipe1(ledstrip1.Color(0, 0, 0), 45, 46); //no
       colorWipe1(ledstrip1.Color(0, 0, 0), 30, 35); //no
       colorWipe1(ledstrip1.Color(0, 0, 0), 58, 63); //no
       colorWipe1(ledstrip1.Color(0, 0, 0), 73, 74); //no
    }
    if(force2>70 and force2<350)
    {
      colorWipe1(ledstrip1.Color(60, 179, 113), 40, 44);//pink
      colorWipe1(ledstrip1.Color(60, 179, 113), 64, 68);//pink
      delay(100);
      colorWipe1(ledstrip1.Color(0, 0, 0), 40, 44);//no
      colorWipe1(ledstrip1.Color(0, 0, 0), 64, 68);//no
    }

  
    delay(10);
    
  } else {
    force2 = 0;
  }

  int musicSwitch2 = 0;

//    Serial.println(force);
    
    if (force2 > 1 && !musicOn2)
    {
      musicSwitch2 = 1;
      musicOn2 = true;
    }
    
    if (force2 < 1 && musicOn2)
    {
      musicSwitch2 = 2;
      musicOn2 = false;
    }

  Serial.print(String(musicSwitch2));
  Serial.print(" ");
  Serial.print(force2);
  Serial.print(" ");
  //Serial.println();

    // add in if for the third reading
  int fsrADC3 = analogRead(FSR_PIN3);
  if (fsrADC3 != 0) // If the analog reading is non-zero
  {
    // Use ADC reading to calculate voltage:
    float fsrV3 = fsrADC3 * VCC / 1023.0;
    // Use voltage and static resistor value to 
    // calculate FSR resistance:
    float fsrR3 = R_DIV * (VCC / fsrV3 - 1.0);
    //Serial.println("Resistance: " + String(fsrR) + " ohms");
    // Guesstimate force based on slopes in figure 3 of
    // FSR datasheet:
    //float force3;
    float fsrG3 = 1.0 / fsrR3; // Calculate conductance
    // Break parabolic curve down into two linear slopes:
    if (fsrR3 <= 600) 
      force3 = (fsrG3 - 0.00075) / 0.00000032639;
    else
      force3 =  fsrG3 / 0.000000642857;
    
    if(force3>5 and force3<32)
    {
      colorWipe1(ledstrip1.Color(255, 250, 250), 75, 82);//white
      colorWipe1(ledstrip1.Color(255, 250, 250), 51, 53);//white
      delay(100);
      colorWipe1(ledstrip1.Color(0, 0, 0), 75, 82);//no
      colorWipe1(ledstrip1.Color(0, 0, 0), 51, 53);//no
    }
    if(force3>32 and force3<52)
    {
      colorWipe1(ledstrip1.Color(0, 0, 128), 73, 74); //blue
      colorWipe1(ledstrip1.Color(0, 0, 128), 83, 86); //blue
      colorWipe1(ledstrip1.Color(0, 0, 128), 58, 63); //blue
      delay(100);
      colorWipe1(ledstrip1.Color(0, 0, 0), 73, 74); //no
      colorWipe1(ledstrip1.Color(0, 0, 0), 83, 86); //no
      colorWipe1(ledstrip1.Color(0, 0, 0), 58, 63); //no
    }
    if(force3>52 and force3<82)
    {
       colorWipe1(ledstrip1.Color(255, 105, 180), 71, 72); //sg
       colorWipe1(ledstrip1.Color(255, 105, 180), 56, 61); //sg
       
       colorWipe1(ledstrip1.Color(255, 105, 180), 87, 90); //sg
       delay(100);
       colorWipe1(ledstrip1.Color(0, 0, 0), 71, 72); //no
       colorWipe1(ledstrip1.Color(0, 0, 0), 56, 61); //no
       
       colorWipe1(ledstrip1.Color(0, 0, 0), 87, 90); //no
    }
    if(force3>82 and force3<350)
    {
      colorWipe1(ledstrip1.Color(110, 139, 51), 66, 70);//dg
      colorWipe1(ledstrip1.Color(110, 139, 51), 91, 96);//dg
      delay(100);
      colorWipe1(ledstrip1.Color(0, 0, 0), 66, 70);//no
      colorWipe1(ledstrip1.Color(0, 0, 0), 91, 96);//no
    }

  
    delay(10);
    
  } else {
    force3 = 0;
  }

  int musicSwitch3 = 0;

//    Serial.println(force);
    
    if (force3 > 1 && !musicOn3)
    {
      musicSwitch3 = 1;
      musicOn3 = true;
    }
    
    if (force3 < 1 && musicOn3)
    {
      musicSwitch3 = 2;
      musicOn3 = false;
    }

  Serial.print(String(musicSwitch3));
  Serial.print(" ");
  
  //Serial.print("force3 ");
  Serial.print(force3);
  //Serial.print(" ");
  
  Serial.println();
  //Serial.println();
}
void colorWipe1(uint32_t color, int start_pixel, int end_pixel)
{
 for(int i=start_pixel; i<(end_pixel+1); i++)
  {
    ledstrip1.setPixelColor(i, color);
    ledstrip1.show();
    delay(0);
  }
  
}
//void theaterChase(uint32_t color, int start_pixel, int end_pixel)
//{
//  for(int a=0; a<10; a++)
//  {
//    for(int b=0; b<3; b++)
//    {
//      ledstrip2.clear();
//      for(int c=b; c<ledstrip2.numPixels(); c += 3)
//      {
//        ledstrip2.setPixelColor(c, color);
//      }
//      ledstrip2.show();
//      delay(wait);
//    }
//  }
//}
