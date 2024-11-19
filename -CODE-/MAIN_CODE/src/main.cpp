
/*
*   Project Name: Sumec
*   Name: MAIN_CODE
*   Last change: 22.10.2024
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
    Tick_Start.tickTime = 10;       //this replaces delay
    Tick_free.tickTime = 1;       //this replaces delay

    // hardware settings (Setup's):
    TfL_Setup();
    pinMode(button, INPUT);
    Serial.begin(115200);
    //UDP_Setup();
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

    // Button
    bootonOld = digitalRead(button);

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
    Tick_managing(Tick_Start.tickTime, Tick_Start.tickNumber, Tick_Start.lastTick, &Tick_Start.lastTick, &Tick_Start.tickNumber);
    Tick_managing(Tick_free.tickTime, Tick_free.tickNumber, Tick_free.lastTick, &Tick_free.lastTick, &Tick_free.tickNumber);



    //==========================Out of line Process==============================


    switch (LINEstate)
    {
        case 0:     //QRE

            if((QREleft || QREright || QREback) && state != 0 && state != 2)
            {
                //UDP_SendUdpToAll("QRE", 1);
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

            //UDP_SendUdpToAll("QRE_END", 1);
            break;

    }

    

    //===========================Normal process===============================

    Serial.print(LUNAleft);
    Serial.print(" ");
    Serial.print(LUNAmiddle);
    Serial.print(" ");
    Serial.println(LUNAright);
    
    switch (state)
    {
    case 000:       // INIT

        if(bootonOld < digitalRead(button)) count++;

        if(count%2 == 0)
        {
            LEDRed.blink(1000);
            LEDOrange.setOff();
            tipe_of_strategy = 230;
        }
        else
        {
            LEDOrange.blink(1000);
            LEDRed.setOff();
            tipe_of_strategy = 231;
        }

        if (Remote.hasDohyoID() && !Remote.isStarted())
        {
            if(count%2 == 0) LEDRed.blink(500, 100);
            else LEDOrange.blink(500, 100);

            Tick_Sharp.lastTick = millis();
            Tick_Sharp.tickNumber = 0;
        }

        // after start comand, main code will start running
        if (Remote.isStarted())
        {
            //UDP_SendUdpToAll("======================", 1);
            state = 002;
            Tick_Start.tickNumber = 0;
            LINEstate = 0;
            //UDP_SendUdpToAll("Start", 1);
        }

        LINEstate = 0;
        
        break;
    case 001:       // IDLE
        
        //nothing - program is stopped

        break;

    /*=============BEGIN OF START FUNCTION=============*/

    case 002:

        //UDP_SendUdpToAll("state_002->Start_function", 1);
        LINEstate = 0;                                                                  //Out of line disabled

        if(back_on_line)                                                                //protect in back on line start
        {
            QREleft = 0;
            QREright = 0;
        }

        if(startState == 0) startState = QREleft*1 + QREright*3 + back_on_line*5;       //setting startState only in one time
        


        switch (startState)
        {
        case 1:                                                                         //Sumec's left side starting on the line

            if(Tick_Start.tickNumber < 30)
            {
                Move.turnRight(1.0);
            }
            else if(Tick_Start.tickNumber < 55)
            {
                Move.goForward(1.0);
            }
            else
            {
                state = tipe_of_strategy;   
            }
            break;

        case 3:                                                                         //Sumec's right side starting on the line

            if(Tick_Start.tickNumber < 25)
            {
                Move.turnLeft(1.0);
            }
            else if(Tick_Start.tickNumber < 45)
            {
                Move.goForward(1.0);
            }
            else
            {
                state = tipe_of_strategy;
            }
            break;

        case 5:                                                                         //Sumec's back side starting on the line

            if(Tick_Start.tickNumber < 40)
            {
                Move.goForward(1.0);
            }
            else
            {
                state = tipe_of_strategy;
            }
            break;

        case 4:                                                                         //Sumec's front side starting on the line

            if(Tick_Start.tickNumber < 20)
            {
                Move.goBackward(1.0);
            }
            else
            {
                state = tipe_of_strategy;
            }

        default:                                                                         //Sumec starting inside the ring

            state = tipe_of_strategy;   
            break;
        }      
        break;

    /*=============END OF START FUNCTION=============*/

    case 230:                                                                           // Turn Right 

        Move.turnRight(1.0);
        
        if(LUNAleft < Range)
        {
            //UDP_SendUdpToAll("state_260", 1);
            state = 260;
        }
        if(LUNAmiddle < Range)
        {
            //UDP_SendUdpToAll("state_290", 1);
            state = 290;
        }

        if(SHARPleft || SHARPright)
        {
            //UDP_SendUdpToAll("state_300", 1);
            state = 300;
        }

        break;
    case 260:                                                                           // Turn Left

        Move.turnLeft(1.0);

        if(LUNAleft > Range) 
        {   
            //UDP_SendUdpToAll("state_230", 1);
            state = 230;
        }

        if(LUNAmiddle < Range)
        {
            //UDP_SendUdpToAll("state_290", 1);
            state = 290;
        }
        
        break;
    case 290:                                                                           // Go Forward

        Move.goForward(1.0);

        if(LUNAmiddle > Range)    
        {
            //UDP_SendUdpToAll("state_230", 1);
            state = 230;
        }

        break;
    /*=============Begin of pasive strategy=============*/
    case 231:

        //UDP_SendUdpToAll("tocimDoprava", 1);

        if(LUNAmiddle < PasivRange)
        {
            //UDP_SendUdpToAll("vidim->jduDo-292", 1);
            state = 292;
            Move.stop();
            Tick_free.tickNumber = 0;
        }
        /*else if(LUNAmiddle < largeRange)
        {
            state = 293;
            Move.stop();
        }*/
        else
        {
            Move.turnRight(0.8);
        }

        break;
    case 292:


        if(Tick_free.tickNumber < 100)
        {
            //UDP_SendUdpToAll("jeduDozadu", 1);
            Move.stop();
        }
        else if((LUNAmiddle > middleRange && LUNAright > middleRange && LUNAleft > middleRange) || Tick_free.tickNumber > 200) state = 293;
        else Move.goBackward(1.0);

        break;
    case 293:

        //Serial.println(Mesuring(1));

        if(LUNAmiddle < PasivRange || Mesuring(LUNAmiddle) == 1) state = 294;        //try change 12 to Range
        else if((LUNAleft < largeRange && LUNAmiddle > largeRange)) state = 261;
        else if((LUNAright < largeRange && LUNAmiddle > largeRange)) state = 232;

        if(SHARPleft) state = 301;
        if(SHARPright) state = 302;

        Move.stop();

        break;
    case 294:


        if((LUNAmiddle > PasivRange) && Mesuring(LUNAmiddle) != 1) state = 293;        //try change 12 to Range
        else if((LUNAleft < Range && LUNAmiddle > Range)) state = 261;
        else if((LUNAright < Range && LUNAmiddle > Range)) state = 232;

        Move.goForward(1.0);

        break;
    case 261:

        if(LUNAmiddle > 6) state = 293;
        else if(LUNAmiddle < 6) state = 294;

        Move.turnLeft(1.0);

        break;
    case 301:                       //left

        if(LUNAmiddle < Range) state = 294;

        Move.turnRight(1.0);

        break;
    case 302:                       //right

        if(LUNAmiddle < Range) state = 294;

        Move.turnLeft(1.0);

        break;

    case 232:

        if(LUNAmiddle > 6) state = 293;
        else if(LUNAmiddle < 6) state = 294;

        Move.turnRight(1.0);

        break;
    /*=============End of pasive strategy=============*/
    case 300:                                                                           // Sharp 

        Tick_Sharp.lastTick = millis();
        Tick_Sharp.tickNumber = 0;

        if(SHARPleft)
        {
            //UDP_SendUdpToAll("state_330", 1);
            state = 330;
        }
        else if(SHARPright)
        {
            //UDP_SendUdpToAll("state_360", 1);
            state = 360;
        }
        break;
    case 330:                                                                           // Turn Right diagonaly and Turn Right 

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
            //UDP_SendUdpToAll("state_230", 1);
            state = 230; // Sharp - End
        }

        break;
    case 360:                                                                           // Turn Left diagonaly and Turn Left 

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
            //UDP_SendUdpToAll("state_230", 1);
            state = 230; // Sharp - End
        }
        
        break;
    }    
}