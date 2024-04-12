#include <Pins.h>
#include <Motor.h>

Motor MotorLeft(PIN_MOTOR_LEFT_NSLEEP,
                PIN_MOTOR_LEFT_ENABLE,
                PIN_MOTOR_LEFT_PHASE,
                MOTOR_LEFT_CHANNEL);
Motor MotorRight(PIN_MOTOR_RIGHT_NSLEEP,
                 PIN_MOTOR_RIGHT_ENABLE,
                 PIN_MOTOR_RIGHT_PHASE,
                 MOTOR_RIGHT_CHANNEL);

void setup() {

}

void loop() {
    MotorLeft.goForward();
    MotorLeft.setSpeed(0.5);
    MotorRight.goBackward();
    MotorRight.setSpeed(0.5);
    delay(2000);
    MotorLeft.stop();
    MotorRight.stop();
    delay(2000);
    MotorLeft.goBackward();
    MotorLeft.setSpeed(0.5);
    MotorRight.goForward();
    MotorRight.setSpeed(0.5);
    delay(2000);
    MotorLeft.stop();
    MotorRight.stop();
    delay(2000);
}