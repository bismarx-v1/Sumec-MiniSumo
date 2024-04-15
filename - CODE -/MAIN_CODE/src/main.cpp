
#include <Pins.h>
//#include <pinsAndVariables.h>
#include <Motor.h>
//#include <QRE1113.h>


//===========================Objects===============================

//Motors

Motor MotorLeft(PIN_MOTOR_LEFT_NSLEEP,
                PIN_MOTOR_LEFT_ENABLE,
                PIN_MOTOR_LEFT_PHASE,
                MOTOR_LEFT_CHANNEL);
Motor MotorRight(PIN_MOTOR_RIGHT_NSLEEP,
                 PIN_MOTOR_RIGHT_ENABLE,
                 PIN_MOTOR_RIGHT_PHASE,
                 MOTOR_RIGHT_CHANNEL);

//QRE

//QRE qreLeft('L');
//QRE qreRight('R');
//QRE qreBack('B');






void setup() 
{
    Serial.begin(9600);
    Serial.println("jok");
    //irrecv.enableIRIn();
    //IRstart();
    //Tick_A.tickTime = 10; 
}

void loop() {

   
    Serial.println("ok");

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
    
   /*
   QREleft = qreLeft.get();
    QREright = qreRight.get();
    QREback = qreBack.get();

    //Writeing value to TICK

    Tick_A.tickNumber = Tick_managing(Tick_A.tickTime, Tick_A.tickNumber, Tick_A.lastTick);
    Tick_A.lastTick = Tick_lastManaging(Tick_A.tickTime, Tick_A.tickNumber, Tick_A.lastTick);

    //==========================Rafinering inputs==============================


    if(state == 0)
    {
        
        if(QREleft == 1 && QREright != 1)
        {
            state = 1;

            Tick_A.lastTick = millis();
            Tick_A.tickNumber = 0;
        }
        else if(QREright == 1 && QREleft != 1)
        {
            state = 2;

            Tick_A.lastTick = millis();
            Tick_A.tickNumber = 0;
        }
        else if(QREback == 1 )
        {
            state = 0;
        }
        else
        {
            state = 0;
        }
    }

    //===========================Procesing resoluts - states===============================

    
    Serial.print("state: ");
    Serial.println(state);
    delay(10);

    switch(state)
    {
        case 0:

            MotorLeft.goForward();
            MotorLeft.setSpeed(0.9);

            MotorRight.goForward();
            MotorRight.setSpeed(0.9);

            break;
        case 1:

            if(Tick_A.tickNumber < 10)
            {
                MotorLeft.goBackward();
                MotorLeft.setSpeed(0.9);

                MotorRight.goBackward();
                MotorRight.setSpeed(0.9);
            }
            else if(Tick_A.tickNumber < 30 )
            {
                MotorLeft.goForward();
                MotorLeft.setSpeed(0.9);

                MotorRight.goBackward();
                MotorRight.setSpeed(0.9);
            }

            else
            {
                state = 0;

            }

            break;
        case 2:

            if(Tick_A.tickNumber < 10)
            {
                MotorLeft.goBackward();
                MotorLeft.setSpeed(0.9);

                MotorRight.goBackward();
                MotorRight.setSpeed(0.9);
            }
            else if(Tick_A.tickNumber < 30 )
            {
                MotorLeft.goForward();
                MotorLeft.setSpeed(0.9);

                MotorRight.goForward();
                MotorRight.setSpeed(0.9);
            }
            else
            {
                state = 0;
            }

            break;

    }
    */
}