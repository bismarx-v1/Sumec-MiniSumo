/**
 * TODO:
 * FIX:
 * CHECK:
 *  - //DEBUG
 * 
 * M1_A 9
 * M1_B 10
 * M2_A 12
 * M2_B 11
 */

#include <Arduino.h>


/**
 * nSleep -  EN   - PH    - Status
 * 0      -  any  - any   - Sleep
 * 1      -  0    - any   - Brake
 * 1      -  1    - 0     - Backward
 * 1      -  1    - 1     - Forward
 */
#define PWM_RESOLUTION 8
#define PWM_FREQUENCY  8000
#define MAX_SPEED      ((1 << PWM_RESOLUTION) - 1)

// Left.
#define PIN_ENCODER_1_A      9   // Encoder pin a.
#define PIN_ENCODER_1_B      10  // Encoder pin b.
#define PIN_MOTOR_1_NSLEEP   38  // NSleep.
#define PIN_MOTOR_1_EN_SPEED 42  // Pwm.
#define PIN_MOTOR_1_PH_DIR   40  // Direction.
#define MOTOR_1_CHANNEL      1   // Ledc channel.

// Right.
#define PIN_ENCODER_2_A      12  // Encoder pin a.
#define PIN_ENCODER_2_B      11  // Encoder pin b.
#define PIN_MOTOR_2_NSLEEP   38  // NSleep.
#define PIN_MOTOR_2_EN_SPEED 39  // Pwm.
#define PIN_MOTOR_2_PH_DIR   41  // Direction.
#define MOTOR_2_CHANNEL      2   // Ledc channel.


#define N_OF_MOTORS                   2
#define MV_CONSTS                     0
#define MV_CONSTS_OFFSET_PH           0
#define MV_CONSTS_OFFSET_LEDC_CHANNEL 1
#define MV_CONSTS_OFFSET_EN           2
#define MV_CONSTS_OFFSET_NSLEEP       3
#define MV_STEPS                      1
#define MV_TARGET_STEPS               2
/**
 * Pos - Value
 * 0(0-7)   - PH pin.
 * 0(8-15)  - Ledc channel.
 * 0(16-23) - EM pin.
 * 0(24-31) - NSleep pin.
 * 1        - Steps var.
 * 2        - Target steps.
 */
uint32_t motorValuesAllMotors[N_OF_MOTORS][3] = {
{PIN_MOTOR_1_PH_DIR << 8 * MV_CONSTS_OFFSET_PH | MOTOR_1_CHANNEL << 8 * MV_CONSTS_OFFSET_LEDC_CHANNEL |
 PIN_MOTOR_1_EN_SPEED << 8 * MV_CONSTS_OFFSET_EN | PIN_MOTOR_1_NSLEEP << 8 * MV_CONSTS_OFFSET_NSLEEP,
 0, 0},
{PIN_MOTOR_2_PH_DIR << 8 * MV_CONSTS_OFFSET_PH | MOTOR_2_CHANNEL << 8 * MV_CONSTS_OFFSET_LEDC_CHANNEL |
 PIN_MOTOR_2_EN_SPEED << 8 * MV_CONSTS_OFFSET_EN | PIN_MOTOR_2_NSLEEP << 8 * MV_CONSTS_OFFSET_NSLEEP,
 0, 0}};

#define ENC_STEPS_PER_ROTATION 154  // Encoder steps per rotation.

typedef uint8_t motorN;
const motorN    LEFT  = 0;
const motorN    RIGHT = 1;

typedef uint8_t motorDir;
const motorDir  CW  = 0;
const motorDir  CCW = 1;


/**
 * @param MVGC_ARRAY The motor variables array.
 * @param MVGC_CONSTS The constants block containing the desired constant.
 * @param MVGC_CONSTS_SEGMENT The constatnt.
 * @returns Value of the constant.
 * @brief Extracts a constant from a motor variables array
 */
#define MV_GET_CONST(MVGC_ARRAY, MVGC_CONSTS, MVGC_CONSTS_SEGMENT)                                                             \
  ((((uint32_t*)MVGC_ARRAY)[MVGC_CONSTS] >> 8 * MVGC_CONSTS_SEGMENT) & 0xff)


// Encoder step callback.
IRAM_ATTR void encoderInterrupt(void* motorVars) {
  if(((uint32_t*)motorVars)[MV_TARGET_STEPS] == 0) {  // Return if the step counting is not active.
    return;
  }

  ((uint32_t*)motorVars)[MV_STEPS]++;                                                // Increment step counter.
  if(((uint32_t*)motorVars)[MV_STEPS] >= ((uint32_t*)motorVars)[MV_TARGET_STEPS]) {  // If steps reached.
    ledcWrite(MV_GET_CONST(motorVars, MV_CONSTS, MV_CONSTS_OFFSET_LEDC_CHANNEL),
              0);                                 // Stop the motor. Write 0 to it's ledc channel.
    ((uint32_t*)motorVars)[MV_TARGET_STEPS] = 0;  // Reset target.
  }
}


/**
 * @param motorVars Motor data array.
 * @param dir direction (CW|CCW) - (clockwise|counterclockwise).
 * @param speed Speed to rotate at (0-255).
 * @brief Starts rotating the motor in a set direction with a set speed.
 * @note Direction is measured from the direction looking at the motor from the axel side.
 */
void motorSet(void* motorVars, motorDir dir, uint8_t speed) {
  if(dir != CW && dir != CCW) {  // Wrong direction. Return.
    log_e("WRONG!");
    return;
  }

  ((uint32_t*)motorVars)[MV_STEPS]        = 0;  // Reset steps. Not needed.
  ((uint32_t*)motorVars)[MV_TARGET_STEPS] = 0;  // Set target steps to 0, disabling step counting.
  digitalWrite(MV_GET_CONST(motorVars, MV_CONSTS, MV_CONSTS_OFFSET_PH), dir);           // Set direction.
  ledcWrite(MV_GET_CONST(motorVars, MV_CONSTS, MV_CONSTS_OFFSET_LEDC_CHANNEL), speed);  // Set speed.
}


/**
 * @param motorVars Motor data array.
 * @param stepsTarget Steps the motor should do.
 * @param dir direction (CW|CCW) - (clockwise|counterclockwise).
 * @param speed Speed to rotate at (0-255).
 * @brief Rotates the motor by set steps in a set direction and with set speed.
 * @note Direction is measured from the direction looking at the motor from the axel side.
 */
void motorRotateSteps(void* motorVars, uint32_t stepsTarget, motorDir dir, uint8_t speed) {
  if(dir != CW && dir != CCW) {  // Wrong direction. Return.
    log_e("WRONG!");
    return;
  }

  ((uint32_t*)motorVars)[MV_STEPS]        = 0;                                          // Reset steps.
  ((uint32_t*)motorVars)[MV_TARGET_STEPS] = stepsTarget;                                // Set target steps.
  digitalWrite(MV_GET_CONST(motorVars, MV_CONSTS, MV_CONSTS_OFFSET_PH), dir);           // Set direction.
  ledcWrite(MV_GET_CONST(motorVars, MV_CONSTS, MV_CONSTS_OFFSET_LEDC_CHANNEL), speed);  // Set speed.
}


/**
 * @param motorVars Motor data array.
 * @param degreesTarget Degrees the motor should do.
 * @param dir direction (CW|CCW) - (clockwise|counterclockwise).
 * @param speed Speed to rotate at (0-255).
 * @brief Rotates the motor by set degrees in a set direction and with set speed.
 * @note Direction is measured from the direction looking at the motor from the axel side.
 */
void motorRotateDegrees(void* motorVars, uint32_t degreesTarget, motorDir dir, uint8_t speed, uint16_t stepsPerRotation) {
  if(dir != CW && dir != CCW) {  // Wrong direction. Return.
    log_e("WRONG!");
    return;
  }

  Serial.println(degreesTarget / 360.0 * stepsPerRotation);  //DEBUG
  motorRotateSteps(motorVars, degreesTarget / 360.0 * stepsPerRotation, dir, speed);
}


void setup() {
  Serial.begin(115200);
  delay(2000);

  // Left.
  pinMode(PIN_ENCODER_1_A, INPUT);
  pinMode(PIN_ENCODER_1_B, INPUT);
  pinMode(MV_GET_CONST(motorValuesAllMotors[LEFT], MV_CONSTS, MV_CONSTS_OFFSET_EN), OUTPUT);
  pinMode(MV_GET_CONST(motorValuesAllMotors[LEFT], MV_CONSTS, MV_CONSTS_OFFSET_PH), OUTPUT);
  ledcSetup(MV_GET_CONST(motorValuesAllMotors[LEFT], MV_CONSTS, MV_CONSTS_OFFSET_LEDC_CHANNEL), PWM_FREQUENCY, PWM_RESOLUTION);
  ledcAttachPin(MV_GET_CONST(motorValuesAllMotors[LEFT], MV_CONSTS, MV_CONSTS_OFFSET_EN),
                MV_GET_CONST(motorValuesAllMotors[LEFT], MV_CONSTS, MV_CONSTS_OFFSET_LEDC_CHANNEL));
  attachInterruptArg(PIN_ENCODER_1_A, encoderInterrupt, (void*)(motorValuesAllMotors[LEFT]), RISING);
  pinMode(MV_GET_CONST(motorValuesAllMotors[LEFT], MV_CONSTS, MV_CONSTS_OFFSET_NSLEEP), OUTPUT);
  digitalWrite(MV_GET_CONST(motorValuesAllMotors[LEFT], MV_CONSTS, MV_CONSTS_OFFSET_NSLEEP), 1);

  // Right.
  pinMode(PIN_ENCODER_2_A, INPUT);
  pinMode(PIN_ENCODER_2_B, INPUT);
  pinMode(MV_GET_CONST(motorValuesAllMotors[RIGHT], MV_CONSTS, MV_CONSTS_OFFSET_EN), OUTPUT);
  pinMode(MV_GET_CONST(motorValuesAllMotors[RIGHT], MV_CONSTS, MV_CONSTS_OFFSET_PH), OUTPUT);
  ledcSetup(MV_GET_CONST(motorValuesAllMotors[RIGHT], MV_CONSTS, MV_CONSTS_OFFSET_LEDC_CHANNEL), PWM_FREQUENCY, PWM_RESOLUTION);
  ledcAttachPin(MV_GET_CONST(motorValuesAllMotors[RIGHT], MV_CONSTS, MV_CONSTS_OFFSET_EN),
                MV_GET_CONST(motorValuesAllMotors[RIGHT], MV_CONSTS, MV_CONSTS_OFFSET_LEDC_CHANNEL));
  attachInterruptArg(PIN_ENCODER_2_A, encoderInterrupt, (void*)(motorValuesAllMotors[RIGHT]), RISING);
  // Setup NSleep for motor 2 if it's different from the motor 1's.
  if(MV_GET_CONST(motorValuesAllMotors[LEFT], MV_CONSTS, MV_CONSTS_OFFSET_NSLEEP) !=
     MV_GET_CONST(motorValuesAllMotors[RIGHT], MV_CONSTS,
                  MV_CONSTS_OFFSET_NSLEEP)) {
    pinMode(MV_GET_CONST(motorValuesAllMotors[RIGHT], MV_CONSTS, MV_CONSTS_OFFSET_NSLEEP), OUTPUT);
    digitalWrite(MV_GET_CONST(motorValuesAllMotors[RIGHT], MV_CONSTS, MV_CONSTS_OFFSET_NSLEEP), 1);
  }


  //motorRotateSteps(motorValuesAllMotors[LEFT], ENC_STEPS_PER_ROTATION, CCW, 0.2 * MAX_SPEED);  // Encoder has 154 steps.
  //motorRotateSteps(motorValuesAllMotors[RIGHT], ENC_STEPS_PER_ROTATION, CW, 0.2*MAX_SPEED);  // Too low speed causes the motor to just beep (~0.1).

  motorRotateDegrees(motorValuesAllMotors[LEFT], 90, CCW, 0.2 * MAX_SPEED, ENC_STEPS_PER_ROTATION);
}


void loop() {
  delay(1000);  //DEBUG
}
