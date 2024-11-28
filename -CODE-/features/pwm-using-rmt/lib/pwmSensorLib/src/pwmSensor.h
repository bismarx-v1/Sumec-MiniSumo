#ifndef _PWM_SENSOR_H
#define _PWM_SENSOR_H

#include <Arduino.h>

/**
 * Constructor
 * @param pwmSensorPinArray  // Number of sensors.
 * @param pwmSensorPinArraySize  // Sensor pins.
 * @param measuredDistanceArray  // Array that stores the measured distances.
 */
class pwmSensor {
private:
  static hw_timer_t*    pwmRecFuncTimerHandle;
  static const uint8_t* pwmSensorPinArray;
  static uint8_t        pwmSensorPinArraySize;
  static uint8_t*       measuredDistanceArray;
  static uint8_t        pwmSensorArrayIndex;
  static void IRAM_ATTR pwmRecFuncCallbackFunc1();

public:
  pwmSensor(const uint8_t* pwmSensorPinArray, uint8_t pwmSensorPinArraySize, uint8_t* measuredDistanceArray);
};

#endif
