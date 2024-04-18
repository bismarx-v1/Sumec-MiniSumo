#include <Pins.h>
#include <Motor.h>
#include <Motion.h>
#include <DohyoIR.h>
#include <LED.h>
#include <QRE1113.h>
#include <pinsAndVariables.h>
#include <TfLunaEsp32S3.h>
#include <Sharp_GP2Y0D810Z0F.h>

// OBJECTs

//motors objects
Motor MotorLeft(PIN_MOTOR_LEFT_NSLEEP, PIN_MOTOR_LEFT_ENABLE, PIN_MOTOR_LEFT_PHASE, MOTOR_LEFT_CHANNEL);
Motor MotorRight(PIN_MOTOR_RIGHT_NSLEEP, PIN_MOTOR_RIGHT_ENABLE, PIN_MOTOR_RIGHT_PHASE, MOTOR_RIGHT_CHANNEL);
Motion Move(MotorLeft, MotorRight);
DohyoIR Remote(PIN_IR);
LED LEDRed(PIN_LED_RED);

//qre objects
QRE qreLeft('L');
QRE qreRight('R');
QRE qreBack('B');

//sharp objects

Sharp sharpLeft('L');
Sharp sharpRight('R');


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



        //=========================Writeing value in sensors to variables=============

        //QREs

        QREleft = qreLeft.get();
        QREright = qreRight.get();
        QREback = qreBack.get();

        //Lunas

        LUNAleft = TfL_Get(TfL_Addr1);
        LUNAright = TfL_Get(TfL_Addr3);
        LUNAmiddle = TfL_Get(TfL_Addr2);

        //Sharps

        SHARPleft = sharpLeft.get();
        SHARPright = sharpRight.get();

        //Writeing value to TICK

        Tick_A.tickNumber = Tick_managing(Tick_A.tickTime, Tick_A.tickNumber, Tick_A.lastTick);
        Tick_A.lastTick = Tick_lastManaging(Tick_A.tickTime, Tick_A.tickNumber, Tick_A.lastTick);

        //==========================Rafinering inputs==============================




        if(state == 0)
        {
            // QRE = FIRST PRIORITY

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
                //LUNAs Senzors

            if(QREleft != 1 && QREright != 1)
            {
            
                if (LUNAmiddle < Range && LUNAmiddle > 0)
                {
                    state = 0;
                }
                else if (LUNAright < Range && LUNAright > 0)
                {
                    state = 3;
                }
                else if (LUNAleft < Range && LUNAleft > 0)
                {
                    state = 4;
                }
                else
                {
                    state = 0;
                }
                
            }

            }
        }

        //===========================Procesing resoluts - states===============================

        switch(state)
        {
            case 0:
                Move.turnLeft(1.0);
                break;
            case 1:

                if(Tick_A.tickNumber < 15)
                {
                    Move.turnRight(1.0);
                }
                else if(Tick_A.tickNumber < 30 )
                {
                    Move.goBackward(1.0);
                }

                else
                {
                    state = 0;

                }



                break;
            case 2:

                if(Tick_A.tickNumber < 15)
                {
                    Move.turnRight(1.0);
                }
                else if(Tick_A.tickNumber < 30 )
                {
                    Move.goForward(1.0);
                }
                else
                {
                    state = 0;
                }

                break;
            case 3:

                Move.goBackward(1.0);
                state = 0;

                break;
            case 4:

                Move.goForward(1.0);
                state = 0;

                break;
            case 5:                     //sharp left

                break;
            case 6:                     //sharp right

                break;


        }


    }

}