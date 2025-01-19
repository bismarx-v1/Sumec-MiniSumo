//#include <Arduino.h>
#include "motorsAndEncders.h"

/**
 * @param MVGC_ARRAY The motor variables array.
 * @param MVGC_CONSTS The constants block containing the desired constant.
 * @param MVGC_CONSTS_SEGMENT The constatnt segment offset.
 * @returns Value of the constant.
 * @brief Extracts a constant from a motor variables array
 */
#define MV_CONST_GET(MVCG_ARRAY, MVCG_CONSTS, MVCG_CONSTS_SEGMENT)                                                             \
  ((((uint32_t*)MVCG_ARRAY)[MVCG_CONSTS] >> (8 * MVCG_CONSTS_SEGMENT)) & 0xff)


/**
 * @param MVGC_ARRAY The motor variables array.
 * @param MVGC_CONSTS The constants block containing the desired constant.
 * @param MVGC_CONSTS_SEGMENT The constatnt segment offset.
 * @param MVGS_VALUE Value to set to.
 * @returns Value of the constant.
 * @brief Extracts a constant from a motor variables array
 */
#define MV_CONST_SET(MVCS_ARRAY, MVCS_CONSTS, MVCS_CONSTS_SEGMENT, MVCS_VALUE)                                                 \
  ((((uint32_t*)MVCS_ARRAY)[MVCS_CONSTS] =                                                                                     \
    ((MVCS_VALUE & 0xff) << (8 * MVCS_CONSTS_SEGMENT)) |                                                                       \
    (((uint32_t*)MVCS_ARRAY)[MVCS_CONSTS] & (0xffffffff ^ ((uint32_t)(0xff << (8 * MVCS_CONSTS_SEGMENT)))))));


// Settings
#ifndef PWM_RESOLUTION
  #define PWM_RESOLUTION 8
#endif
#ifndef PWM_FREQUENCY
  #define PWM_FREQUENCY 8000
#endif
#ifndef N_OF_MOTORS
  #define N_OF_MOTORS 2  // Number of motors.
#endif
// Left motor.
#define PIN_ENCODER_1_A                9    // Encoder pin a.
#define PIN_ENCODER_1_B                10   // Encoder pin b.
#define PIN_MOTOR_1_NSLEEP             38   // NSleep.
#define PIN_MOTOR_1_EN                 42   // Speed, pwm.
#define PIN_MOTOR_1_PH                 40   // Direction.
#define MOTOR_1_CHANNEL                1    // Ledc channel.
#define MOTOR_1_ENC_STEPS_PER_ROTATION 154  // Encoder steps per rotation.
#define MOTOR_1_WHEEL_CIRCUMFERENCE    100  // Wheel circumference. Wrong bcos i dunno.
// Right motor.
#define PIN_ENCODER_2_A                12   // Encoder pin a.
#define PIN_ENCODER_2_B                11   // Encoder pin b.
#define PIN_MOTOR_2_NSLEEP             38   // NSleep.
#define PIN_MOTOR_2_EN                 39   // Speed, pwm.
#define PIN_MOTOR_2_PH                 41   // Direction.
#define MOTOR_2_CHANNEL                2    // Ledc channel.
#define MOTOR_2_ENC_STEPS_PER_ROTATION 154  // Encoder steps per rotation.
#define MOTOR_2_WHEEL_CIRCUMFERENCE    100  // Wheel circumference. Wrong bcos i dunno.

#define MAX_SPEED ((1 << PWM_RESOLUTION) - 1)  // Max speed of the motor.


/**
 * Pos - Value
 * 0(0-7)   - PH pin.              --const
 * 0(8-15)  - Ledc channel.        --const
 * 0(16-23) - EM pin.              --const
 * 0(24-31) - NSleep pin.          --const
 * 1(0-7)   - Encoder A pin.       --const
 * 1(8-15)  - Encoder B pin.       --const
 * 1(16-23) - Steps per rotation.  --const
 * 1(24-31) - Wheel circumference. --const
 * 2        - Steps var.
 * 3        - Target steps.
 * 4        - Error.
 */
//
#define MV_ARRAY_LEN                       5  // Number of 32bit values in the array.
#define MV_ARRAY_CONSTANTS_LEN             8  // Number of 8bit constants in the array.
#define MV_CONSTS_M                        0
#define MV_CONSTS_M_OFFSET_PH              0  // 8bit.
#define MV_CONSTS_M_OFFSET_LEDC_CHANNEL    1  // 8bit.
#define MV_CONSTS_M_OFFSET_EN              2  // 8bit.
#define MV_CONSTS_M_OFFSET_NSLEEP          3  // 8bit.
#define MV_CONSTS_H                        1
#define MV_CONSTS_H_ENC_A                  0  // 8bit.
#define MV_CONSTS_H_ENC_B                  1  // 8bit.
#define MV_CONSTS_H_ENC_STEPS_PER_ROTATION 2  // 8bit.
#define MV_CONSTS_H_WHEEL_CIRCUMFERENCE    3  // 8bit.
#define MV_STEPS                           2  // 32bit.
#define MV_TARGET_STEPS                    3  // 32bit.
#define MV_ERR                             4  // 32bit.


class motors {
private:
  static void encoderInterrupt(void* motorVars);  // Callback on encoder A interrupt.
public:
  typedef uint8_t motorErr;
  const motorErr  noErr = 0;  // Not set.
  const motorErr  oki   = 1;  // Success.

  typedef uint8_t motorN;
  const motorN    LEFT  = 0;
  const motorN    RIGHT = 1;

  typedef uint8_t motorDir;
  const motorDir  CW  = 0;
  const motorDir  CCW = 1;


  uint32_t mvArrayAll[N_OF_MOTORS][MV_ARRAY_LEN] = {
  0};  // I should have just used a struct. Array storing all motor variables for all motors.

  motors();
  motors(uint8_t** customMotorPinsArrays);
  void setup();
  void rotateSet(void* motorVars, motorErr* err, uint8_t speed, motorDir dir);
  void rotateSteps(void* motorVars, motorErr* err, uint8_t speed, motorDir dir, uint32_t stepsTarget);
  void rotateDegrees(void* motorVars, motorErr* err, uint8_t speed, motorDir dir, uint32_t degreesTarget);
  void rotateDistance(void* motorVars, motorErr* err, uint8_t speed, motorDir dir, uint16_t distanceTarget);
};
