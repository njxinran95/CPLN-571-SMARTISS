int crossRed1 = 3;
int crossGreen1 = 4;
int crossRed2 = 5;
int crossGreen2 = 6;
int vehicleRed = 7;
int vehicleYellow = 8;
int vehicleGreen = 9;
int delayTime = 20000;
int yellowTime = 3000;


void setup() {
  // put your setup code here, to run once:
    pinMode(crossRed1,OUTPUT);
    pinMode(crossRed2,OUTPUT);
    pinMode(crossGreen1,OUTPUT);
    pinMode(crossGreen2,OUTPUT);
    pinMode(vehicleRed,OUTPUT);
    pinMode(vehicleYellow,OUTPUT);
    pinMode(vehicleGreen,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
    digitalWrite(crossRed1,HIGH);  // red light is on
    digitalWrite(crossRed2,HIGH);  // red light is on
    digitalWrite(crossGreen1,LOW); // green light is off
    digitalWrite(crossGreen2,LOW); // green light is off

    digitalWrite(vehicleGreen,HIGH);
    digitalWrite(vehicleRed,LOW);
    digitalWrite(vehicleYellow,LOW);
    
    delay(delayTime);

    digitalWrite(vehicleGreen,LOW);
    digitalWrite(vehicleRed,LOW);
    digitalWrite(vehicleYellow,HIGH);

    delay(yellowTime);
    
    digitalWrite(crossRed1,LOW);  // red light is on
    digitalWrite(crossRed2,LOW);  // red light is on
    digitalWrite(crossGreen1,HIGH); // green light is off
    digitalWrite(crossGreen2,HIGH); // green light is off
    
    digitalWrite(vehicleGreen,LOW);
    digitalWrite(vehicleRed,HIGH);
    digitalWrite(vehicleYellow,LOW);

    delay(delayTime);
}
