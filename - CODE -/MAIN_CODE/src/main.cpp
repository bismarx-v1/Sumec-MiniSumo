#include <Pins.h>
#include <Motor.h>
#include <Motion.h>
#include <DohyoIR.h>
#include <LED.h>
#include <QRE1113.h>
#include <variablesForMAIN.h>
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

void setup() {
    
    //logic settings: 

    Tick_QRE.tickTime = 10; 
    Tick_Sharp.tickTime = 10;

    //hardware settings:

    TfL_Setup();
    Serial.begin(115200);
    LEDRed.blink(1000);

}

void loop() {

    LEDRed.update();
    Remote.update();

    if (Remote.hasDohyoID() && !Remote.isStarted()) LEDRed.blink(500, 100);

    if (Remote.isStarted()) {

        LEDRed.blink(200, 200);

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

        Tick_QRE.tickNumber = Tick_managing(Tick_QRE.tickTime, Tick_QRE.tickNumber, Tick_QRE.lastTick);
        Tick_QRE.lastTick = Tick_lastManaging(Tick_QRE.tickTime, Tick_QRE.tickNumber, Tick_QRE.lastTick);

        Tick_Sharp.tickNumber = Tick_managing(Tick_Sharp.tickTime, Tick_Sharp.tickNumber, Tick_Sharp.lastTick);
        Tick_Sharp.lastTick = Tick_lastManaging(Tick_Sharp.tickTime, Tick_Sharp.tickNumber, Tick_Sharp.lastTick);



        //==========================Rafinering inputs==============================


        if(state == 0)
        {
            // QRE = FIRST PRIORITY

            if(QREleft == 1 && QREright != 1)
            {
                state = 1;
                sharpON_OFF = 0;
                lunaON_OFF = 0;

                Tick_QRE.lastTick = millis();
                Tick_QRE.tickNumber = 0;

            }
            else if(QREright == 1 && QREleft != 1)
            {
                state = 2;
                sharpON_OFF = 0;
                lunaON_OFF = 0;

                Tick_QRE.lastTick = millis();
                Tick_QRE.tickNumber = 0;
            }
            else if(QREback == 1 )
            {
                state = 0;
            }
            
            else                                        //Sharp Senzors
            {
                if(sharpON_OFF == 1)
                {        
                    if(SHARPleft == 1)
                    {
                        state = 5;
                        //lunaON_OFF = 0;

                        Tick_Sharp.lastTick = millis();
                        Tick_Sharp.tickNumber = 0;
                    }
                    else if(SHARPright == 1)
                    {
                        state = 6;
                        //lunaON_OFF = 0;

                        Tick_Sharp.lastTick = millis();
                        Tick_Sharp.tickNumber = 0;
                    }

                    else                                    //LUNAs Senzors
                        {
                        
                        if(lunaON_OFF)
                        {
                            if (LUNAmiddle < Range && LUNAmiddle > 0)
                            {
                                state = 7;
                            }
                            else if (LUNAright < Range && LUNAright > 0)
                            {
                                state = 4;
                            }
                            else if (LUNAleft < Range && LUNAleft > 0)
                            {
                                state = 3;
                            }
                            else
                            {
                                state = 0;
                            }
                        }
                    }
                }
            }
        }

        //===========================Procesing resoluts - states===============================
        Serial.print(LUNAleft);
        Serial.print("\t");
        Serial.print(LUNAmiddle);
        Serial.print("\t");
        Serial.println(LUNAright);


        switch(state)
        {
            case 0:
                Move.goForward(1.0);
                //Serial.println("nn");

                break;
            case 1:                         //Left QRE

                if(Tick_QRE.tickNumber < 15)
                {
                    Move.goBackward(1.0);
                    
                }
                else if(Tick_QRE.tickNumber < 30 )
                {
                    Move.turnRight(1.0);
                }

                else
                {
                    state = 0;
                    sharpON_OFF = 1;
                    lunaON_OFF = 1;

                }



                break;
            case 2:                         //Right QRE

                if(Tick_QRE.tickNumber < 15)
                {
                    Move.goBackward(1.0);
                }
                else if(Tick_QRE.tickNumber < 30 )
                {
                    Move.turnLeft(1.0);
                }
                else
                {
                    state = 0;
                    sharpON_OFF = 1;
                    lunaON_OFF = 1;
                }

                break;
            case 3:                     //Luna left

                Move.turnLeft(1.0);
                state = 0;

                break;
            case 4:                     //Luna right

                Move.turnRight(1.0);
                state = 0;

                break;

            case 7:

                Move.goForward(1.0);
                state = 0;

                break;
            /*case 5:                     //sharp left
                  
                if(sharpON_OFF == 1)
                {
                    if(Tick_Sharp.tickNumber < 20)
                    {
                        Move.turnLeft(0.5, 0.5);
                    }
                    else if(Tick_Sharp.tickNumber < 50)
                    {
                        Move.turnLeft(0.5, 0.5);
                        lunaON_OFF = 1;
                    }
                    else
                    {
                        state = 0;
                    }
                }

            */    break;
            /*case 6:                     //sharp right

                if(sharpON_OFF == 1)
                {
                    if(Tick_Sharp.tickNumber < 00)
                    {
                        Move.turnRight(0.5, 0.5);
                    }
                    else if(Tick_Sharp.tickNumber < 50)
                    {
                        Move.turnLeft(0.5, 0.5);
                        lunaON_OFF = 1;
                    }
                    else
                    {
                        state = 0;
                    }
                }

                break;
            */

        }

    }

}