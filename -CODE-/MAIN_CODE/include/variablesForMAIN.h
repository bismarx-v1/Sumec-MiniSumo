#include <Motion.h>
#include <Arduino.h>

//============================= PROGRAM VARIABLES ===============================

// Logic variables:
#define back_on_line 0          //0 = normal state, 1 = Sumec's back starting on line  


int Range = 20;                 // Length senzor range[cm] for decision, is enybodey there?
int PasivRange = 12;

int tipe_of_strategy = 230;
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
int LUNAleft;
int LUNAright;
int LUNAmiddle;

// Value of side sonzors
bool SHARPleft;
bool SHARPright;

// Start time
bool bootonOld;
int count;

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
#define mesureArrayNumber 5
#define timeMesuring 30
#define dividingValue 2
#define deviation 1 //[cm]

long measuredValues[mesureArrayNumber];
unsigned long disMe = millis();
int Amesure = 1;
int risingValues;


bool Mesuring(int distanc)
{


    if(((millis() - disMe) > timeMesuring) && (Amesure % (mesureArrayNumber + 1)) <= mesureArrayNumber)
    {
        //Serial.print(millis());
        //Serial.print(" ");

        measuredValues[(Amesure % mesureArrayNumber)-1] = distanc;
        Amesure++;
      	disMe = millis();
      	
    }
    
    if((Amesure % (mesureArrayNumber + 1)) > (mesureArrayNumber - 1))             //must be edited
    {
        for(int i = 0; i < (mesureArrayNumber - 2); i++)
        {
            if((measuredValues[i] + deviation) < (measuredValues[i+1])) risingValues++;
            //Serial.print(measuredValues[i]);
            //Serial.print(" ");
        }
      	Serial.print((Amesure % (mesureArrayNumber + 1)));
        Serial.print(" ");

        if(risingValues > mesureArrayNumber) risingValues = 0;
        
        Amesure = 0;
    }

    
    if((mesureArrayNumber/dividingValue) <= risingValues) return 1;
    else
    {
        risingValues = 0;
        return 0;
    } 
}
