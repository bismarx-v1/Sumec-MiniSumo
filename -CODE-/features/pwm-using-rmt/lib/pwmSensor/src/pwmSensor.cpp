#if 0
/**
 * 
 */

#include <Arduino.h>
#include <pwmSensor.h>


//#include <iostream>
//#include <functional>
//#include <algorithm>
using namespace std;

//int main () {
//  int numbers[] = {10,20,30,40,50,10};
//  int cx;
//  cx = count_if (numbers, numbers+6, bind1st(equal_to<int>(),10) );
//  cout << "There are " << cx << " elements that are equal to 10.\n";
//  return 0;
//}


/**
 * Constructor.
 */
void pwmSensor(const uint8_t* pwmSensorPinArray, uint8_t pwmSensorPinArraySize, uint8_t* measuredDistanceArray) {
  pwmSensorPinArray     = pwmSensorPinArray;
  pwmSensorPinArraySize = pwmSensorPinArraySize;
  measuredDistanceArray = measuredDistanceArray;

  // Timer channel, clock divisor (clock is 80MHz) (1600 should be 50Hz), count up.
  pwmRecFuncTimerHandle = timerBegin(0, 1600, true);
  timerStop(pwmRecFuncTimerHandle);
  
  pwmSensorArrayIndex = 0;
  attachInterrupt(pwmSensorPinArray[pwmSensorArrayIndex], pwmRecFuncCallbackFunc1, CHANGE);
}


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
#endif