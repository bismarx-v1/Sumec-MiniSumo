#include <Pins.h>
#include <Motor.h>
#include <Motion.h>
#include <DohyoIR.h>
#include <LED.h>
#include <QRE1113.h>
#include <pinsAndVariables.h>
#include <TfLunaEsp32S3.h>

// OBJECTs
Motor MotorLeft(PIN_MOTOR_LEFT_NSLEEP, PIN_MOTOR_LEFT_ENABLE, PIN_MOTOR_LEFT_PHASE, MOTOR_LEFT_CHANNEL);
Motor MotorRight(PIN_MOTOR_RIGHT_NSLEEP, PIN_MOTOR_RIGHT_ENABLE, PIN_MOTOR_RIGHT_PHASE, MOTOR_RIGHT_CHANNEL);
Motion Move(MotorLeft, MotorRight);
DohyoIR Remote(PIN_IR);
LED LEDRed(PIN_LED_RED);

//qre objects
QRE qreLeft('L');
QRE qreRight('R');
QRE qreBack('B');


//TICKs 


void setup() {
    
    //logic settings: 

    Tick_A.tickTime = 10; 


    //hardware settings:

    TfL_Setup();
    Serial.begin(115200);
    LEDRed.blink(1000);

}

void loop() {

    LEDRed.update();
    Remote.update();

    if (Remote.hasDohyoID()) LEDRed.blink(500, 100);

    if (Remote.isStarted()) {
        
        Move.goForward(1.0);

    }

}