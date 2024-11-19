/**
 * a
 */

#include <Arduino.h>
#include "esp32-rmt-pwm-reader.h"

#define PWM_OUT_PIN        17  // GPIO pin for PWM output
#define PWM_IN_PIN         18  // GPIO pin for PWM input
#define PWM_OUT_CHANNEL    1   // LEDC channel (0-15)
#define PWM_OUT_FREQ       50  // Frequency in Hz
#define PWM_OUT_RESOLUTION 8   // Resolution in bits (0-255 for 8-bit)

volatile uint8_t dutyCycle = 50;  // Initial duty cycle (50%)


#define SENSOR_SIM_TASK_SIZE 2000
TaskHandle_t sensorSimTaskHandle;
/**
 * @brief task that simulates the sensour output by going through pwm duty cycles from ~1/20 to ~1/10
 */
void sensorSimFunc(void* parameter) {
  const uint8_t dutyCycleSweepLimits[2] = {13, 26};  // (255/20|255/10)  - (1ms pulse|2ms pulse)
  uint8_t       dutyCycle               = dutyCycleSweepLimits[0];
  int8_t        dutyCycleSweepDirection = 1;

  // Initialize LEDC for hardware PWM
  ledcSetup(PWM_OUT_CHANNEL, PWM_OUT_FREQ, PWM_OUT_RESOLUTION);
  ledcAttachPin(PWM_OUT_PIN, PWM_OUT_CHANNEL);

  // Set an initial duty cycle
  ledcWrite(PWM_OUT_CHANNEL, dutyCycle);
  while(1) {
    dutyCycle = dutyCycle + dutyCycleSweepDirection;
    if(dutyCycle < dutyCycleSweepLimits[0]) {
      dutyCycleSweepDirection = -1;
    } else if(dutyCycle > dutyCycleSweepLimits[1]) {
      dutyCycleSweepDirection = 1;
    }

    ledcWrite(PWM_OUT_CHANNEL, dutyCycle);
    vTaskDelay(100);
  }
}


void setup() {
  // Driver task  |Task func  |Name  |Stack size  |Parameter of the task  |Priority  |Task handle  |Core
  xTaskCreatePinnedToCore(sensorSimFunc, "sensorSimTask", SENSOR_SIM_TASK_SIZE, NULL, 1, &sensorSimTaskHandle, 1);
}


void loop() {
  taskYIELD();
}
