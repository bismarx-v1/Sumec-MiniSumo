#include "line.h"

void setup() {
  Serial.begin(9600);
}



void loop() {
  Serial.println(LINE_Get(1, 3700));
  Serial.println(LINE_Get(2, 3700));
  //Serial.println(LINE_Get(3, 3500));
  //Serial.println(LINE_Get(4, 3500));
  Serial.println("====================");
  delay(50);
}
