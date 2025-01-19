/**
 * TODO:
 * FIX:
 * CHECK:
 */

#include <Arduino.h>

//#define N_OF_MOTORS 2 // Define this before the include to change it. Default is 2.
#include "motorsAndEncders.h"


#if 0  // Use custom pins?
// Array of arrays for each motor, defined as {PH_pin, ledc_channel, EN_pin, nsleep_pin, encoder_a_pin, encoder_b_pin, encoder_steps, wheel_circumference}.
uint8_t customPins[N_OF_MOTORS][MV_ARRAY_CONSTANTS_LEN] = {{40, 1, 42, 38, 9, 10, 154, 100}, {41, 2, 39, 38, 12, 11, 154, 100}};
// Constructor with custom values.
motors motorsObj = motors((uint8_t**)customPins);
#else
motors motorsObj = motors();
#endif


void setup() {
  Serial.begin(115200);
  delay(2000);

  motorsObj.setup();

  uint8_t mErr;  // Error var. Stores an output of the motor functions.

  mErr = 0;  // Reset error var.
  // Set the left motor to rotate counterclockwise at 20% speed.
  motorsObj.rotateSet(motorsObj.mvArrayAll[motorsObj.LEFT], &mErr, 0.2 * MAX_SPEED, motorsObj.CCW);
  delay(1000);
  motorsObj.rotateSet(motorsObj.mvArrayAll[motorsObj.LEFT], &mErr, 0, motorsObj.CW);
  delay(100);


  mErr = 0;  // Reset error var.
  // Set the left motor to rotate by 154 steps counterclockwise at 20% speed.
  motorsObj.rotateSteps(motorsObj.mvArrayAll[motorsObj.LEFT], &mErr, 0.2 * MAX_SPEED, motorsObj.CCW, 154);
  while(mErr == motorsObj.noErr) {  // Wait for the motor to finnish or fail.
    delay(10);
  }
  delay(100);


  mErr = 0;  // Reset error var.
  // Set the left motor to rotate by 360 degrees counterclockwise at 20% speed.
  motorsObj.rotateDegrees(motorsObj.mvArrayAll[motorsObj.LEFT], &mErr, 0.2 * MAX_SPEED, motorsObj.CCW, 360);
  while(mErr == motorsObj.noErr) {  // Wait for the motor to finnish or fail.
    delay(10);
  }
  delay(100);

  mErr = 0;  // Reset error var.
  // Set the left motor to travel 100mm counterclockwise at 20% speed.
  motorsObj.rotateDistance(motorsObj.mvArrayAll[motorsObj.LEFT], &mErr, 0.2 * MAX_SPEED, motorsObj.CCW, 100);
  while(mErr == motorsObj.noErr) {  // Wait for the motor to finnish or fail.
    delay(10);
  }
  delay(100);
}


void loop() {
  delay(1000);
}
