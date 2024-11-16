#include <Arduino.h>

#define PWM_OUT_PIN 17       // GPIO pin for PWM output
#define PWM_OUT_CHANNEL 1    // LEDC channel (0-15)
#define PWM_OUT_FREQ 50      // Frequency in Hz
#define PWM_OUT_RESOLUTION 8 // Resolution in bits (0-255 for 8-bit)

volatile uint8_t dutyCycle = 50; // Initial duty cycle (50%)

void pwmTask(void *param)
{
    while (true)
    {
        ledcWrite(PWM_OUT_PIN, dutyCycle);
        vTaskDelay(pdMS_TO_TICKS(1000));    // 1 second delay in task
        dutyCycle = (dutyCycle + 10) % 256; // Rotate between 0, 50%, 100%
    }
}

void pwmTask_Init()
{
    // Initialize LEDC for hardware PWM
    ledcSetup(PWM_OUT_CHANNEL, PWM_OUT_FREQ, PWM_OUT_RESOLUTION);
    ledcAttachPin(PWM_OUT_PIN, PWM_OUT_CHANNEL);

    // Set an initial duty cycle
    ledcWrite(PWM_OUT_CHANNEL, dutyCycle);

    // Create a FreeRTOS task for PWM control
    xTaskCreate(pwmTask, "PWM Task", 1024, NULL, 1, NULL);
}