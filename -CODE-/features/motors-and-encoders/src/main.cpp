//#include "mbcontroller.h"
#include <Arduino.h>


#define PIN_ENC_A 0
#define PIN_ENC_B 0


void encCallback() {
  uint8_t direction = digitalRead(PIN_ENC_B);
   
}


void encSetup(uint8_t pinEncA, uint8_t pinEncB) {
  pinMode(pinEncA, INPUT);
  pinMode(pinEncB, INPUT);

  attachInterrupt(pinEncA, encCallback, RISING);
  //attachInterruptArg();
}


void rotateNSteps(int64_t steps) {

}


void setup() {
  encSetup(PIN_ENC_A, PIN_ENC_B);
}


void loop() {

}