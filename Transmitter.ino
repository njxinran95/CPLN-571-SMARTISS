int remoteControlPin = 4;
int SmartLightRead = 0;

#include <RH_ASK.h>
#include <SPI.h>

RH_ASK driver;

void setup() {
      Serial.begin(9600);   // Debugging only

   if (!driver.init())
    {
      Serial.println("Init Failed! Please Check Your Transmitter or Receiver.");
    }
}

void loop() {
    const char *msg = ("11");
    const char *mgs = ("00");
 
  if (digitalRead(remoteControlPin)==HIGH){
    SmartLightRead = 1;
    Serial.println(SmartLightRead);
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    delay(100);

  }

  if (digitalRead(remoteControlPin)==LOW){
    SmartLightRead = 0;
    Serial.println(SmartLightRead);
    driver.send((uint8_t *)mgs, strlen(mgs));
    driver.waitPacketSent();
    delay(100);
    }


}
