#include <Motion.h>
#include <Arduino.h>

//============================= PROGRAM VARIABLES ===============================

// Logic variables:
#define back_on_line 0          //0 = normal state, 1 = Sumec's back starting on line 
#define tipe_of_strategy 231 


int Range = 30;                 // Length senzor range[cm] for decision, is enybodey there?

uint16_t state = 0;             // variable who decides, what is in progress
uint16_t LINEstate = 0;
uint8_t startState;
uint16_t saveState;

float rotate_coeficient = 0;    // wariable for rotating, how much is having rotating 
bool isStarted = 0;             // variable for starting with button
bool sharpON_OFF = 1;           // rafinering parameter for side sonzors, Is side sonzor on or off
bool lunaON_OFF = 1;            // rafinering parameter for Length senzor, Is Length senzor on or off
bool QRE_left_started = 0;


// sensors:

// Value of line sonzors
uint8_t QREleft;
uint8_t QREright;
uint8_t QREback;

// Value of length sonzors
uint16_t Lunas[3];
int LUNAleft;
int LUNAright;
int LUNAmiddle;

// Value of side sonzors
bool SHARPleft;
bool SHARPright;

// Start time
int StartTime;

//============================= PROGRAM VARIABLES ===============================

// structure tick, who have all tick variables 
struct TICK
{
    int tickTime;
    uint32_t tickNumber = 100;
    uint32_t lastNumberTick = 0;
    uint32_t lastTick = 0;
};

// function for updateing tick's
void Tick_managing(int time, uint32_t value, uint32_t last, uint32_t *return_last, uint32_t *return_value)
{
    if (millis() - last >= time)
    {
        value++;
        last = millis();
    }

    *return_last = last;
    *return_value = value;
}

// using tics

TICK Tick_QRE;
TICK Tick_Sharp;
TICK Tick_Start;
TICK Tick_free;


// distance changing variables
#define mesureArrayNumber 6
#define timeMesuring 20
#define dividingValue 2


uint16_t measuredValues[mesureArrayNumber];



bool Mesuring(int LunaN)
{
    static int risingValues;
    static long disMe = Tick_free.tickNumber;
    static int Amesure = 1;

    if(((Tick_free.tickNumber - disMe) > Amesure*timeMesuring) && Amesure <= mesureArrayNumber)
    {
        measuredValues[Amesure-1] = Lunas[LunaN];
        Amesure++;
    }


    for(int i = 0; i < (mesureArrayNumber-1); i++)
    {
        if(measuredValues[i] < measuredValues[i+1]) risingValues++;
    }


    if((mesureArrayNumber/dividingValue) < risingValues) return 1;
    else return 0;
}