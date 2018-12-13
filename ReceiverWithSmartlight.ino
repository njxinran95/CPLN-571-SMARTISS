int rec_val = 0;

#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile
#include <Adafruit_NeoPixel.h>

RH_ASK driver;
#define NUM_LEDS 12 // LED number
#define PIN 5 // LED pin

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
    strip.begin();
    strip.show();
    Serial.begin(9600); // Debugging only
    if (!driver.init())
    {
      Serial.println("init failed");
    }
}

void loop()
{

  uint8_t i[2];
  uint8_t ilen = sizeof(i);
  if (driver.recv(i,&ilen)) // Non-blocking
  {
    // Message with a good checksum received, dump it.
    Serial.println((char *)i);

     
     
    if (i[1] == 49 ){
      Serial.println(1);
      smartlightHigh();
    }
    else
    {
      Serial.println(0);
      smartlightLow();
    }
  }   
}


void smartlightHigh(){
  for (int j = 0;j<12; j++){
    strip.setPixelColor(j,0,255,255);
    strip.show();
    }
}

void smartlightLow() {
  for (int j = 0; j<12;j++) {
    strip.setPixelColor(j,0,0,0);
    strip.show(); 
    
  }
}
