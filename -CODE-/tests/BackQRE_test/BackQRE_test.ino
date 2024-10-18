#include <Arduino.h>

#define QRE 8

void setup() {
  pinMode(QRE, INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(QRE));
  delay(100);
}
