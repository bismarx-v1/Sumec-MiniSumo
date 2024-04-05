#include <Arduino.h>
#include "pinsAndVariables.h"
#include "QRE1113.h"            //befor update
#include "DRV8874PWPR.h"        //befor update



// Objects

//motors objects
H_bridge Motors(5000,8);

//qre objects
QRE qreLeft('L');
QRE qreRight('R');
QRE qreBack('B');


//TICKs 

TICK Tick_A;



void setup() 
{
    //Serial.begin(115200);
    Tick_A.tickTime = 10; 
     
}


void loop()
{
    //=========================Writeing value in sensors to variables=============

    QREleft = qreLeft.get();
    QREright = qreRight.get();
    QREback = qreBack.get();

    //Writeing value to TICK

    Tick_A.tickNumber = Tick_managing(Tick_A.tickTime, Tick_A.tickNumber, Tick_A.lastTick);
    Tick_A.lastTick = Tick_lastManaging(Tick_A.tickTime, Tick_A.tickNumber, Tick_A.lastTick);

    //==========================Rafinering inputs==============================


    if(Tick_A.tickNumber < 20 && state != 1 && state != 2)
    {
        state = state;
    }
    else if(Tick_A.tickNumber < 20 && state == 3)
    {

    }
    else if(Tick_A.tickNumber == 40)
    {
        state = 0;
        lastQRE = 0;
    }
    else
    {
        if(QREleft == 1 && state != 2)
        {

            state = 3;
            lastQRE = 1;
            

            Tick_A.lastTick = millis();
            Tick_A.tickNumber = 0;
        }
        else if(QREright == 1 && state != 1)
        {
    
            state = 3;
            lastQRE = 2;
 

            Tick_A.lastTick = millis();
            Tick_A.tickNumber = 0;
        }
        else if(lastQRE == 1)
        {
            state = 1;
        }
        else if(lastQRE == 2)
        {
            state = 2;
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

    switch(state)
    {
        case 0:
            Motors.left(255);
            Motors.right(255);
            break;
        case 1:
            Motors.left(255);
            Motors.right(-255);
            break;
        case 2:
            Motors.left(-255);
            Motors.right(255);
            break;
        case 3:
            Motors.left(-255);
            Motors.right(-255);
            break;
    }

    
}
