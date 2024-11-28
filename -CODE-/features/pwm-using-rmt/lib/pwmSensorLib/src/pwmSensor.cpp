/**
 * 
 */

#include <Arduino.h>
#include <pwmSensor.h>


/**
 * Constructor, nya~ :3.
 */
pwmSensor::pwmSensor(const uint8_t* pwmSensorPinArray, uint8_t pwmSensorPinArraySize, uint8_t* measuredDistanceArray) {
  this->pwmSensorPinArray     = pwmSensorPinArray;
  this->pwmSensorPinArraySize = pwmSensorPinArraySize;
  this->measuredDistanceArray = measuredDistanceArray;

  // Timer channel, clock divisor (clock is 80MHz) (1600 should be 50Hz), count up.
  pwmRecFuncTimerHandle = timerBegin(0, 1600, true);
  timerStop(pwmRecFuncTimerHandle);
  
  pwmSensorArrayIndex = 0;
  attachInterrupt(pwmSensorPinArray[pwmSensorArrayIndex], pwmRecFuncCallbackFunc1, CHANGE);
}

/**
 * Callback on pwm change.
 */
void IRAM_ATTR pwmSensor::pwmRecFuncCallbackFunc1() {
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
