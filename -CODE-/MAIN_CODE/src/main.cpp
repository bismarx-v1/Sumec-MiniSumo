
/*
*   Project Name: Sumec
*   Name: MAIN_CODE
*   Last change: 6.9.2024
*/

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
Sharp sharpLeft('R');
Sharp sharpRight('L');

//=================== DECLARING OBJECTs ===================

void setup()
{

    // logic settings:
    Tick_QRE.tickTime = 10;         //this replaces delay
    Tick_Sharp.tickTime = 10;       //this replaces delay

    // hardware settings (Setup's):
    TfL_Setup();
    pinMode(button, INPUT);
    Serial.begin(115200);
    LEDRed.blink(1000);
    UDP_Setup();
}

void loop()
{
 
    LEDRed.update();            //updates the red led
    LEDOrange.update();         //updates the orange led
    Remote.update();

    if(Remote.isStopped()) 
    {
        state = 0;
        Move.stop();
        LEDRed.blink(1000);
    }


    //=========================Writeing value from sensors to variables=============

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




    //==========================Out of line Process==============================


    switch (LINEstate)
    {
        case 0:     //QRE

            if((QREleft || QREright || QREback) && state != 0 && state != 2)
            {
                UDP_SendUdpToAll("QRE", 1);
                saveState = state;   //saved last state
                state = 001;
                LINEstate++;

                Tick_QRE.lastTick = millis();
                Tick_QRE.tickNumber = 0;
            }

            break;
        case 1:     //STOP

            Move.stop();

            if(QREleft || QREright)
            {
                LINEstate++;
            }
            else if(QREback)
            {
                LINEstate = 4;
            }

            break;
        case 2:     //Go backward

            if(Tick_QRE.tickNumber < 10)
            {
                Move.goBackward(1.0);
            }
            else
            {
                LINEstate = 3;
            }

            break;
        case 3:     //STOP after backward

            Move.stop();

            state = saveState;
            LINEstate = 0;

            break;
        case 4:     //Go forward

            if(Tick_QRE.tickNumber < 10)
            {
                Move.goForward(1.0);
            }
            else
            {
                LINEstate = 3;
            }

            UDP_SendUdpToAll("QRE_END", 1);
            break;

    }

    

    //===========================Normal process===============================

    switch (state)
    {
    case 000:       // INIT 

        if (Remote.hasDohyoID() && !Remote.isStarted())
        {
            
            LEDRed.blink(500, 100);
            Tick_Sharp.lastTick = millis();
            Tick_Sharp.tickNumber = 0;
        }

        // after start comand, main code will start running
        if (Remote.isStarted())
        {
            UDP_SendUdpToAll("======================", 1);
            state = 002;
            Tick_Start.tickNumber = 0;
            LINEstate = 0;
            UDP_SendUdpToAll("Start", 1);
        }

        LINEstate = 0;
        
        break;
    case 001:       // IDLE
        
        //nothing - program is stopped

        break;
    case 002:                                                                // Starting

        if(Start(QREleft, QREright, QREback, &Move)) state = 230;
        UDP_SendUdpToAll("state_002->Start_function", 1);        
        break;
    case 230:                                                                // Turn Right 

        Move.turnRight(1.0);
        
        if(LUNAleft < Range)
        {
            UDP_SendUdpToAll("state_260", 1);
            state = 260;
        }
        if(LUNAmiddle < Range)
        {
            UDP_SendUdpToAll("state_290", 1);
            state = 290;
        }

        if(SHARPleft || SHARPright)
        {
            UDP_SendUdpToAll("state_300", 1);
            state = 300;
        }

        break;
    case 260: // Turn Left

        Move.turnLeft(1.0);

        if(LUNAleft > Range) 
        {   
            UDP_SendUdpToAll("state_230", 1);
            state = 230;
        }

        if(LUNAmiddle < Range)
        {
            UDP_SendUdpToAll("state_290", 1);
            state = 290;
        }
        
        break;
    case 290: // Go Forward

        Move.goForward(1.0);

        if(LUNAmiddle > Range)    
        {
            UDP_SendUdpToAll("state_230", 1);
            state = 230;
        }

        break;
    case 300: // Sharp 

        Tick_Sharp.lastTick = millis();
        Tick_Sharp.tickNumber = 0;

        if(SHARPleft)
        {
            UDP_SendUdpToAll("state_330", 1);
            state = 330;
        }
        else if(SHARPright)
        {
            UDP_SendUdpToAll("state_360", 1);
            state = 360;
        }
        break;
    case 330: // Turn Right diagonaly and Turn Right 

        if (Tick_Sharp.tickNumber < 20)
        {
            Move.turnRight(0.7, 0.55);
        }
        else if (Tick_Sharp.tickNumber < 50)
        {
            Move.turnRight(0.7, 0.55);
        }
        else if (LUNAmiddle > Range && LUNAright > Range && LUNAleft > Range)
        {
            Move.turnRight(1.0);
        }
        else
        {
            UDP_SendUdpToAll("state_230", 1);
            state = 230; // Sharp - End
        }

        break;
    case 360: // Turn Left diagonaly and Turn Left 

        if (Tick_Sharp.tickNumber < 20)
        {
            Move.turnLeft(0.7, 0.55);
        }
        else if (Tick_Sharp.tickNumber < 50)
        {
            Move.turnLeft(0.7, 0.55);
        }
        else if (LUNAmiddle > Range && LUNAright > Range && LUNAleft > Range)
        {
            Move.turnLeft(1.0);
        }
        else
        {
            UDP_SendUdpToAll("state_230", 1);
            state = 230; // Sharp - End
        }
        
        break;
    }    
}