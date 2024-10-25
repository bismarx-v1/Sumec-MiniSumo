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



/*bool Start(bool QRE_L, bool QRE_R, bool QRE_B, Motion *MotorsStart)
{
    //variables for start function
    bool returningValue;
    Tick_Start.tickTime = 10;
    LINEstate = 0;

    Tick_managing(Tick_Start.tickTime, Tick_Start.tickNumber, Tick_Start.lastTick, &Tick_Start.lastTick, &Tick_Start.tickNumber);


    if(back_on_line)                                                                //protect in back on line start
    {
        QRE_L = 0;
        QRE_R = 0;
    }

    if(startState == 0) startState = QRE_L*1 + QRE_R*3 + back_on_line*5;            //setting startState only in one time
    


    switch (startState)
    {
    case 1:                                                                         //Sumec's left side starting on the line

        if(Tick_Start.tickNumber < 30)
        {
            MotorsStart->turnRight(1.0);
            returningValue = 0;
        }
        else if(Tick_Start.tickNumber < 55)
        {
            MotorsStart->goForward(1.0);
            returningValue = 0;
        }
        else
        {
            returningValue = 1;   
        }
        break;

    case 3:                                                                         //Sumec's right side starting on the line

        if(Tick_Start.tickNumber < 25)
        {
            MotorsStart->turnLeft(1.0);
            returningValue = 0;
        }
        else if(Tick_Start.tickNumber < 45)
        {
            MotorsStart->goForward(1.0);
            returningValue = 0;
        }
        else
        {
            returningValue = 1;   
        }
        break;

    case 5:                                                                         //Sumec's back side starting on the line

        if(Tick_Start.tickNumber < 40)
        {
            MotorsStart->goForward(1.0);
            returningValue = 0;
        }
        else
        {
           returningValue = 1;
        }
        break;

    case 4:                                                                         //Sumec's front side starting on the line

        if(Tick_Start.tickNumber < 20)
        {
            MotorsStart->goBackward(1.0);
            returningValue = 0;
        }
        else
        {
            returningValue = 1;
        }

    default:                                                                         //Sumec starting inside the ring

        returningValue = 1;   
        break;
    }

    return returningValue;          
}*/