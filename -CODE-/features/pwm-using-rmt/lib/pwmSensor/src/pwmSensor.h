#ifndef _PWM_SENSOR_H
#define _PWM_SENSOR_H

#include <Arduino.h>


hw_timer_t*    pwmRecFuncTimerHandle;
const uint8_t* pwmSensorPinArray;
uint8_t        pwmSensorPinArraySize;
uint8_t*       measuredDistanceArray;
uint8_t        pwmSensorArrayIndex;


/**
 * Callback on pwm change.
 */
void IRAM_ATTR pwmRecFuncCallbackFunc1() {
  uint8_t trigEdge = digitalRead(pwmSensorPinArray[pwmSensorArrayIndex]);
  if(trigEdge == 1) {  // Rising.
    timerRestart(pwmRecFuncTimerHandle);
    timerStart(pwmRecFuncTimerHandle);

  } else if(trigEdge == 0) {  // Faling.
    measuredDistanceArray[pwmSensorArrayIndex] = ((timerReadMicros(pwmRecFuncTimerHandle) - 1000) * 3 / 2) / 10;
    timerStop(pwmRecFuncTimerHandle);
    detachInterrupt(pwmSensorPinArray[pwmSensorArrayIndex]);
    if(pwmSensorArrayIndex + 1 > pwmSensorPinArraySize) {
      pwmSensorArrayIndex = 0;
    } else {
      pwmSensorArrayIndex++;
    }

    attachInterrupt(pwmSensorPinArray[pwmSensorArrayIndex], pwmRecFuncCallbackFunc1, CHANGE);
  }
}


/**
 * Setup.
 * @param pwmSensorPinArray  // Number of sensors.
 * @param pwmSensorPinArraySize  // Sensor pins.
 * @param measuredDistanceArray  // Array that stores the measured distances.
 */
void pwmSensor(const uint8_t* pwmSensorPinArrayU, uint8_t pwmSensorPinArraySizeU, uint8_t* measuredDistanceArrayU) {
  pwmSensorPinArray     = pwmSensorPinArrayU;
  pwmSensorPinArraySize = pwmSensorPinArraySizeU;
  measuredDistanceArray = measuredDistanceArrayU;

  // Timer channel, clock divisor (clock is 80MHz) (1600 should be 50Hz), count up.
  pwmRecFuncTimerHandle = timerBegin(0, 1600, true);
  timerStop(pwmRecFuncTimerHandle);
  
  pwmSensorArrayIndex = 0;
  attachInterrupt(pwmSensorPinArray[pwmSensorArrayIndex], pwmRecFuncCallbackFunc1, CHANGE);
}


#endif