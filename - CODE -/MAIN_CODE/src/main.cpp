#include <Pins.h>
#include <Motor.h>
#include <Motion.h>
#include <DohyoIR.h>
#include <LED.h>
#include <QRE1113.h>
#include <variablesForMAIN.h>
#include <TfLunaEsp32S3.h>
#include <Sharp_GP2Y0D810Z0F.h>

//=================== DECLARING OBJECTs ===================

// motors objects
Motor MotorLeft(PIN_MOTOR_LEFT_NSLEEP, PIN_MOTOR_LEFT_ENABLE, PIN_MOTOR_LEFT_PHASE, MOTOR_LEFT_CHANNEL);
Motor MotorRight(PIN_MOTOR_RIGHT_NSLEEP, PIN_MOTOR_RIGHT_ENABLE, PIN_MOTOR_RIGHT_PHASE, MOTOR_RIGHT_CHANNEL);
Motion Move(MotorLeft, MotorRight);

// IR, RC-5 and led objects
DohyoIR Remote(PIN_IR);
LED LEDRed(PIN_LED_RED);
LED LEDOrange(PIN_LED_ORABGE);

// Line sonzors objects
QRE qreLeft('L');
QRE qreRight('R');
QRE qreBack('B');

// side sonzors objects
Sharp sharpLeft('L');
Sharp sharpRight('R');

//=================== DECLARING OBJECTs ===================

void setup()
{

    // logic settings:
    Tick_QRE.tickTime = 10;
    Tick_Sharp.tickTime = 10;

    // hardware settings:
    TfL_Setup();
    pinMode(button, INPUT);
    Serial.begin(115200);
    LEDRed.blink(1000);
}

void loop()
{

    // controling led flashing time and   
    LEDRed.update();
    LEDOrange.update();
    Remote.update();

    // start with button
    if(digitalRead(button) == 1)
    {
        while(digitalRead(button) == 1)
        {
            LEDRed.setOn();
            LEDOrange.setOn();
        }
        isStarted = 1;
    }

    // start with IR
    if (Remote.hasDohyoID() && !Remote.isStarted())
        LEDRed.blink(500, 100);

    // after start comand, running this main code
    if (!Remote.isStarted() && isStarted == 1)
    {

        //=========================Writeing value in sensors to variables=============

        // Line sonzors
        QREleft = qreLeft.get();
        QREright = qreRight.get();
        QREback = qreBack.get();

        // Length senzors
        LUNAleft = TfL_Get(TfL_Addr1);
        LUNAright = TfL_Get(TfL_Addr3);
        LUNAmiddle = TfL_Get(TfL_Addr2);

        // side sonzors
        SHARPleft = sharpLeft.get();
        SHARPright = sharpRight.get();

        // Writeing value to TICK
        Tick_managing(Tick_QRE.tickTime, Tick_QRE.tickNumber, Tick_QRE.lastTick, &Tick_QRE.lastTick, &Tick_QRE.tickNumber);
        Tick_managing(Tick_Sharp.tickTime, Tick_Sharp.tickNumber, Tick_Sharp.lastTick, &Tick_Sharp.lastTick, &Tick_Sharp.tickNumber);

        //==========================Rafinering inputs==============================

        // if Sumec started, program continuing to main logic
        if (state != 0)
        {

            // line senzors -> first priority - Defence 
            if (QREleft == 1 && QREright != 1)
            {
                state = 2;
                sharpON_OFF = 0;
                lunaON_OFF = 0;

                Tick_QRE.lastTick = millis();
                Tick_QRE.tickNumber = 0;
            }
            else if (QREright == 1 && QREleft != 1)
            {
                state = 3;
                sharpON_OFF = 0;
                lunaON_OFF = 0;

                Tick_QRE.lastTick = millis();
                Tick_QRE.tickNumber = 0;
            }
            else if (state == 1)
            {
                // side senzors -> second priority - Defence
                if (sharpON_OFF == 1)
                {
                    if (SHARPleft == 1)
                    {
                        state = 6;
                        lunaON_OFF = 0;

                        Tick_Sharp.lastTick = millis();
                        Tick_Sharp.tickNumber = 0;
                    }
                    else if (SHARPright == 1)
                    {
                        state = 7;
                        lunaON_OFF = 0;

                        Tick_Sharp.lastTick = millis();
                        Tick_Sharp.tickNumber = 0;
                    }

                    else // Length Senzors
                    {
                        // Length senzors -> thirth priority - Attack
                        if (lunaON_OFF)
                        {
                            if (LUNAmiddle < Range && LUNAmiddle > 0)
                            {
                                state = 8;
                            }
                            else if (LUNAright < Range && LUNAright > 0)
                            {
                                state = 5;
                            }
                            else if (LUNAleft < Range && LUNAleft > 0)
                            {
                                state = 4;
                            }
                            else
                            {
                                state = 1;
                            }
                        }
                    }
                }
            }
        }

        Serial.println(isStarted);

        //===========================Procesing resoluts - states===============================

        switch (state)
        {
        case 0:
            LEDRed.blink(100, 100);

            if(QREleft)
            {
                Range = 50;
                Move.turnRight(1.0);
            }
            else if(QREright)
            {
                Range = 50;
                Move.turnLeft(1.0);
                QRE_left_started = 1;

            }
            else if(QRE_left_started == 0)
            {
                Move.turnRight(1.0);
                Range = 35;
            }

            if (LUNAmiddle < Range )
            {
                state = 1;
                Range = 50;
            }

            break;
        case 1:
            Move.goForward(1.0);

            LEDOrange.setOff();
            LEDRed.blink(100, 100);

            break;
        case 2: // Line sonzor - Left

            LEDRed.setOn();

            if (Tick_QRE.tickNumber < 15)
            {
                Move.goBackward(1.0);
            }
            else if (Tick_QRE.tickNumber < 30)
            {
                Move.turnRight(1.0);
            }

            else
            {
                state = 1;
                sharpON_OFF = 1;
                lunaON_OFF = 1;
            }

            break;
        case 3: // Line sonzor - Right

            LEDRed.setOn();

            if (Tick_QRE.tickNumber < 15)
            {
                Move.goBackward(1.0);
            }
            else if (Tick_QRE.tickNumber < 30)
            {
                Move.turnLeft(1.0);
            }
            else
            {
                state = 1;
                sharpON_OFF = 1;
                lunaON_OFF = 1;
            }

            break;
        case 4: // Length senzor - left

            LEDOrange.blink(100, 100);
            Move.turnLeft(1.0);
            state = 1;

            break;
        case 5: // Length senzor - right

            LEDOrange.blink(100, 100);
            Move.turnRight(1.0);
            state = 1;

            break;

        case 8: // Length senzor - middle

            LEDOrange.blink(100, 100);
            Move.goForward(1.0);
            state = 1;

            break;
        case 6: // side sonzors - left

            LEDOrange.setOn();

            if (sharpON_OFF == 1)
            {
                if (Tick_Sharp.tickNumber < 20)
                {
                    Move.turnLeft(0.5, (0.5 * rotate_coeficient));
                }
                else if (Tick_Sharp.tickNumber < 50)
                {
                    Move.turnLeft(0.5, (0.5 * rotate_coeficient));
                }
                else if (Tick_Sharp.tickNumber < 60)
                {
                    Move.turnLeft(1.0);
                }
                else
                {
                    lunaON_OFF = 1;
                    state = 1;
                }

                if (Tick_Sharp.tickNumber > Tick_Sharp.lastNumberTick)
                {
                    rotate_coeficient = rotate_coeficient + 0.02;
                }
            }

            break;
        case 7: // side sonzors - right

            LEDOrange.setOn();

            if (sharpON_OFF == 1)
            {
                if (Tick_Sharp.tickNumber < 20)
                {
                    Move.turnRight(0.5, (0.5 * rotate_coeficient));
                }
                else if (Tick_Sharp.tickNumber < 50)
                {
                    Move.turnRight(0.5, (0.5 * rotate_coeficient));
                }
                else if (Tick_Sharp.tickNumber < 60)
                {
                    Move.turnRight(1.0);
                }
                else
                {
                    lunaON_OFF = 1;
                    state = 1;
                }

                if (Tick_Sharp.tickNumber > Tick_Sharp.lastNumberTick)
                {
                    rotate_coeficient = rotate_coeficient + 0.02;
                }
            }

            break;
        }
    }
    else
    {
        Move.stop();
    }
}