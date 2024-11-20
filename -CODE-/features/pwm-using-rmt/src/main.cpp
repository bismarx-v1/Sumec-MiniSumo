/**
 * a
 */

#include <Arduino.h>
#include "esp32-rmt-pwm-reader.h"

#define PWM_IN_PIN 18  // GPIO pin for PWM input

#define PWM_OUT_PIN        17  // GPIO pin for PWM output
#define PWM_OUT_CHANNEL    1   // LEDC channel (0-15)
#define PWM_OUT_FREQ       50  // Frequency in Hz
#define PWM_OUT_RESOLUTION 8   // Resolution in bits (0-255 for 8-bit)

#define SENSOR_SIM_TASK_SIZE 2000
TaskHandle_t sensorSimTaskHandle;
/**
 * @brief task that simulates the sensour output by going through pwm duty cycles from ~1/20 to ~1/10
 */
void sensorSimFunc(void* parameter) {
  const uint8_t dutyCycleSweepLimits[2] = {13, 26};  // (255/20|255/10)  - (1ms pulse|2ms pulse)
  uint8_t       dutyCycle               = dutyCycleSweepLimits[0];
  static int8_t dutyCycleSweepDirection = 1;

  // Initialize LEDC for hardware PWM
  ledcSetup(PWM_OUT_CHANNEL, PWM_OUT_FREQ, PWM_OUT_RESOLUTION);
  ledcAttachPin(PWM_OUT_PIN, PWM_OUT_CHANNEL);

  // Set an initial duty cycle
  ledcWrite(PWM_OUT_CHANNEL, dutyCycle);
  while(1) {
    dutyCycle = dutyCycle + dutyCycleSweepDirection;
    if(dutyCycle - 1 < dutyCycleSweepLimits[0]) {
      dutyCycleSweepDirection = 1;
    } else if(dutyCycle + 1 > dutyCycleSweepLimits[1]) {
      dutyCycleSweepDirection = -1;
    }

    ledcWrite(PWM_OUT_CHANNEL, dutyCycle);

#if 1
    // Position the cursor at the desired position (row, col)
    Serial.print("\033[");  // Begin of escape sequence
    Serial.print(2);        // row number (begins with 1)
    Serial.print(";");
    Serial.print(1);  // column (begins with 1)
    Serial.print("H");
#endif
    Serial.printf("set dc = %04i\n", dutyCycle);
    vTaskDelay(1000);
  }
}

hw_timer_t* pwmRecFuncTimerHandle;
uint64_t    temp1 = 0;

void IRAM_ATTR pwmRecFuncCallbackFunc1() {
  uint8_t trigEdge = digitalRead(PWM_IN_PIN);
  if(trigEdge == 1) {  // Rising.
    timerRestart(pwmRecFuncTimerHandle);
    timerStart(pwmRecFuncTimerHandle);

  } else if(trigEdge == 0) {  // Faling.
    temp1 = timerReadMicros(pwmRecFuncTimerHandle);
    timerStop(pwmRecFuncTimerHandle);
  }
}

#define PWM_RECORDER_TASK_SIZE 2000
TaskHandle_t pwmRecFuncHandle;


void pwmRecFunc(void* parameter) {
  pinMode(PWM_IN_PIN, INPUT);
  attachInterrupt(PWM_IN_PIN, pwmRecFuncCallbackFunc1, CHANGE);

  pwmRecFuncTimerHandle = timerBegin(0, 1600, true);
  // Timer channel, clock divisor (clock is 80MHz) (1600 should be 50Hz), count up.
  timerStop(pwmRecFuncTimerHandle);

  while(1) {
#if 1
    // Position the cursor at the desired position (row, col)
    Serial.print("\033[");  // Begin of escape sequence
    Serial.print(3);        // row number (begins with 1)
    Serial.print(";");
    Serial.print(1);  // column (begins with 1)
    Serial.print("H");
#endif

    const uint8_t  loadingAnimCharSet[4] = {'/', '-', '\\', '|'};
    static uint8_t loadingAnimCharPos    = 0;
    if(loadingAnimCharPos + 1 > 3) {
      loadingAnimCharPos = 0;
    } else {
      loadingAnimCharPos++;
    }

    Serial.printf("pulse len %04i[us]\n", temp1);
    Serial.printf("still alive %c", loadingAnimCharSet[loadingAnimCharPos]);
    vTaskDelay(100);
  }
}


void setup() {
  Serial.begin(115200);

  // Driver task  |Task func  |Name  |Stack size  |Parameter of the task  |Priority  |Task handle  |Core
  xTaskCreatePinnedToCore(sensorSimFunc, "sensorSimTask", SENSOR_SIM_TASK_SIZE, NULL, 1, &sensorSimTaskHandle, 1);

  // Reciever task  |Task func  |Name  |Stack size  |Parameter of the task  |Priority  |Task handle  |Core
  xTaskCreatePinnedToCore(pwmRecFunc, "pwmRecTask", PWM_RECORDER_TASK_SIZE, NULL, 1, &pwmRecFuncHandle, 1);
}


void loop() {
  vTaskDelay(1000);
}
