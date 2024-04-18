#include <Arduino.h>

//============================= PROGRAM VARIABLES ===============================

// using variables

int Range = 30;

uint8_t state;

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



//using tics

TICK Tick_A;
TICK Tick_Sharp;