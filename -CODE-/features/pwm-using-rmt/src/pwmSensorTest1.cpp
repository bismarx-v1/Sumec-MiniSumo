/**
 * Untested code.
 * Example of the pwm sensor.
 */

#include <Arduino.h>
#include "pwmSensor.h"

#define pwmSensorPinArrayLen_var 2  // Number of sensors.
const uint8_t pwmSensorPinArray_var[pwmSensorPinArrayLen_var] = {5, 16};  // Sensor pins (pcb_v.4 left = 5, right = 16).
uint8_t measuredDistanceArray_var[pwmSensorPinArrayLen_var];  // Array that stores the measured distances.

pwmSensor pwmSensorObj(pwmSensorPinArray_var, pwmSensorPinArrayLen_var, measuredDistanceArray_var); // Object constructor.

/**
 * @brief Set serial prints' cursor.
 * @param row Row.
 * @param col Column.
 */
void serialSetCursorPos(uint16_t row, uint16_t col) {
  Serial.print("\033[");  // Begin of escape sequence.
  Serial.print(row+1);  // Row number (begins with 1).
  Serial.print(";");
  Serial.print(col+1);  // Column (begins with 1).
  Serial.print("H");
}

void setup() {
  Serial.begin();
}

void loop () {
  serialSetCursorPos(1, 0);
  Serial.println("1st sensor | 2nd sensor");
  Serial.print(measuredDistanceArray_var[0]);
  Serial.print(" | ");
  Serial.println(measuredDistanceArray_var[1]);
  Serial.print("Millis: ");
  Serial.println(millis());
  
}
