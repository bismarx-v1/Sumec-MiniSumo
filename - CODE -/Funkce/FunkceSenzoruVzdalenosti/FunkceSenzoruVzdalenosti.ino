#include "laser.h"


void setup() {
  Serial.begin (9600);
  LASER_Setup();
}


void loop() {
  Serial.print("Range: ");
  Serial.println(Range);
  Serial.print("Right: ");
  Serial.println(String(LASER_Get(1, Range)));  //pravy senzor (1) z pohledu sumce
  Serial.print("Front: ");
  Serial.println(String(LASER_Get(3, Range)));  //prostredni senzor (3) z pohledu sumce
  Serial.print("Left: ");
  Serial.println(String(LASER_Get(2, Range)));  //levy senzor (2) z pohledu sumce
  Serial.print("======================== \n");
  delay(500);
}
