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
        if(digitalRead(button) == 1)
        {
            LEDRed.setOn();
            LEDOrange.setOn();
        }
        isStarted = 1;
        StartTime = millis();
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

        //==========================Out of line Error==============================

        switch (LINEstate)
        {
            case 0:     //QRE


                break;
            case 1:     //STOP


                break;
            case 2:     //Go backward


                break;
            case 3:     //STOP after backward


                break;
            case 4:     //Go forward


                break;

        }
        
        //===========================Normal process===============================

        switch (state)
        {
        case 000:       // INIT 

            
            break;
        case 001:       // IDLE
            
            
            break;
        case 2: // Line sonzor - Left

            LEDRed.setOn();

            if (Tick_QRE.tickNumber < 1)
            {
                Move.goBackward(1.0);
            }
            else if (Tick_QRE.tickNumber < 15)
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

            if (Tick_QRE.tickNumber < 1)
            {
                Move.goBackward(1.0);
            }
            else if (Tick_QRE.tickNumber < 15)
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

            

            break;
        case 5: // Length senzor - right

            
            break;

        case 8: // Length senzor - middle

            

            break;
        case 6: // side sonzors - left

            

            break;
        case 7: // side sonzors - right

           

            break;
        }
    }
    else
    {
        Move.stop();
    }
}