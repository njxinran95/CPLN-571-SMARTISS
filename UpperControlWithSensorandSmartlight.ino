
// Include RadioHead Amplitude Shift Keying Library
// The transmitter pin will use pin 12
// The receiver pin will use pin 11

#include <SPI.h>
#include <SD.h>
#include <TMRpcm.h>
#include <Adafruit_NeoPixel.h>
#include <Ultrasonic.h>

#define PIN 8 // LED pin
#define NUM_LEDS 12 // LED number
#define SD_ChipSelectionPin 7 // define CS pin
Ultrasonic ultrasonic(A0,A1);
TMRpcm tmrpcm;                            //crete an object for speaker library
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);


// Setting all the pins
// smartlight uses pin 6;
// PIR uses pin 5
// Current Crosswalk Light uses pin 1

int smartLightPin = 8;
int remoteControlPin = 2;
int additionalLED=6;
int trafficTrafLightStatePin=4;
int pirPin = 5;

// Setting the variables

int pirValue = 0;
int pirResult = 0;
int crossSmartHigh = 0;
int delayTime = 5000;
int sensorResult=0;
unsigned long currenttime = 0;
unsigned long redlightTimer = 0;

int USresult=0;
int TrafLightState=0;
int lightvoltage;
int photovoltage;
int volume=4;
char counterTransmitter;
char counterSmartLight;

void setup() {
  strip.begin();
  strip.show();
  strip.setBrightness(10);
  tmrpcm.speakerPin = 9;
  pinMode(smartLightPin,OUTPUT);
  pinMode(trafficTrafLightStatePin,INPUT);//1
  pinMode(additionalLED,OUTPUT);
  pinMode(remoteControlPin,OUTPUT);
  Serial.begin(9600);
  currenttime = millis();

  if(!SD.begin(SD_ChipSelectionPin)) 
  {
    return;
  }
    tmrpcm.setVolume(4);
    tmrpcm.play("1.wav");
}

void loop() {


  // To see if own side should turn on the light
  lightvoltage=analogRead(A5);//trafficlight
  if (lightvoltage>500)
  {TrafLightState=1;}
  else
  {
    TrafLightState=0;
    redlightTimer=millis();//record the current time
  }

  pirResult = readPIR();
  //pirResult=1;
  USresult = readDIS();
  sensorResult=pirResult*USresult;//yu
  delay(100);//detect every 100 ms
  photovoltage=analogRead(A4);//photo
  Serial.print("Light Levvel: ");
  Serial.println(photovoltage);
  if (photovoltage>400)
  {
    volume=6;
  }
  else{
    volume=2;
  }
//  Serial.println(lightvoltage);
//    Serial.println("sensor");
//  Serial.println(USresult);
//      Serial.println("traffic");
//    Serial.println(TrafLightState);

  crossSmartHigh = sensorResult*TrafLightState;  //
if ((millis()-redlightTimer < delayTime) && (TrafLightState*pirResult==1))//first 5 sec
  {
    Serial.println("Block detected from PIR in the first 5 seconds!");
    digitalWrite(remoteControlPin,HIGH);
    smartlightHigh();
    if(volume==2){
      digitalWrite(additionalLED,HIGH);
    }
    else{
      digitalWrite(additionalLED,LOW);
    }
    tmrpcm.setVolume(volume);
    tmrpcm.play("3.wav");
    delay(2000);
    currenttime = millis();
    Serial.println(currenttime);
  }
  if ((millis()-redlightTimer >= delayTime) && (crossSmartHigh == 1))
 //if (crossSmartHigh == 1)
  {
    Serial.println("Block detected!");
    digitalWrite(remoteControlPin,HIGH);
    smartlightHigh();
    if(volume==2){
      digitalWrite(additionalLED,HIGH);
    }
    else{
      digitalWrite(additionalLED,LOW);
    }
    tmrpcm.setVolume(volume);
    tmrpcm.play("2.wav");
    delay(2000);
    currenttime = millis();
    Serial.println(currenttime);
  }
  
if (crossSmartHigh == 0)
  {
  if ((millis()-currenttime < delayTime) && (TrafLightState=1))
    {
          Serial.println("Block not detected, light shut down in ");    
          Serial.println(millis()-currenttime);
          Serial.println(currenttime);

          smartlightHigh();
          if(volume==2){
            digitalWrite(additionalLED,HIGH);
          }
          else{
            digitalWrite(additionalLED,LOW);
          }
//          tmrpcm.setVolume(volume);
//          tmrpcm.play("2.wav");
//          delay(2000);
    }
    else
    {
    //Serial.println("PIR not detected!");
    digitalWrite(remoteControlPin,LOW);

    smartlightLow();
    digitalWrite(additionalLED,LOW);
    }
  }
}

void smartlightHigh(){
  for (int i = 0;i<12; i++) {
    strip.setPixelColor(i,0,100,100);
    strip.show();
  }
}

void smartlightLow() {
  for (int i = 0; i<12;i++) {
    strip.setPixelColor(i,0,0,0);
    strip.show();
  }
}


int readDIS(){
  int detectresult = 0;
  int distance;
  distance = ultrasonic.read(); //Use 'CM' for centimeters or 'INC' for inches
  Serial.print("Object found at: ");
  Serial.print(distance);
  Serial.println("cm");


  if (distance<30 && distance>20){
    detectresult=1;}
    else{
    detectresult=0;}
    
    return detectresult;
}

int readPIR(){
  pirValue = digitalRead(pirPin);
  if(pirValue== HIGH){
    pirResult = 1;
    Serial.println("PIR detected!");
    }
   if(pirValue== LOW){
    pirResult = 0;
    Serial.println("PIR not detected!");
    }
    return pirResult;
}
