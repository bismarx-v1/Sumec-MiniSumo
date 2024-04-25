#include <Arduino.h>

//============================= PROGRAM VARIABLES ===============================

// Logic variables:
int Range = 50;     // Length senzor range for decision, is enybodey there?
uint8_t state = 0;      // variable who decides, what is in progress
float rotate_coeficient = 0;    // wariable for rotating, how much is having rotating 
//bool start = 0;     // this variable determines if the start is in progress 
bool isStarted = 0;     // variable for starting with button
bool sharpON_OFF = 1;      // rafinering parameter for side sonzors, Is side sonzor on or off
bool lunaON_OFF = 1;       // rafinering parameter for Length senzor, Is Length senzor on or off
bool QRE_left_started = 0;


// sensors:

// Value of line sonzors
uint8_t QREleft;
uint8_t QREright;
uint8_t QREback;

// Value of length sonzors
int LUNAleft;
int LUNAright;
int LUNAmiddle;

// Value of side sonzors
bool SHARPleft;
bool SHARPright;

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