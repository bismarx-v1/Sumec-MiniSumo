#include "Adafruit_VL53L0X.h"


int analogPin = 35;
int SensVal = 0;
#define led 14


void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}


void loop() {
  int SensVal = analogRead(analogPin);
  Serial.println(SensVal);


  if(SensVal < 3500) {
    digitalWrite(led, HIGH);
  }

  else {
    digitalWrite(led, LOW);
  }

}
