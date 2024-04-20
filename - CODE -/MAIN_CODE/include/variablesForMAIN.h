#include <Arduino.h>

//============================= PROGRAM VARIABLES ===============================


//Logic variables
int Range = 50;   // revrite to 1      //Luna range for 0 or 1
uint8_t state;          //variable who decides, what is in progress

bool sharpON_OFF = 1;       //rafinering parameter for sharp
bool lunaON_OFF = 1;        //rafinering parameter for luna


// sensors
uint8_t QREleft;
uint8_t QREright;
uint8_t QREback;

int end = 0;

int LUNAleft;
int LUNAright;
int LUNAmiddle;

bool SHARPleft;
bool SHARPright;


//============================= PROGRAM VARIABLES ===============================



struct TICK
{
    int tickTime;
    uint32_t tickNumber = 100;
    uint32_t lastTick = 0;
};

//function for tick number
uint32_t Tick_managing(int time, uint32_t value, uint32_t last)
{
    if(millis() - last >= time)
    {
        value++;
    }

    return value;
}

//function for last tick
uint32_t Tick_lastManaging(int time, uint32_t value, uint32_t last)
{
    if(millis() - last >= time)
    {
        last = millis();
    }
    
    return last;
}



//using tics

TICK Tick_QRE;
TICK Tick_Sharp;