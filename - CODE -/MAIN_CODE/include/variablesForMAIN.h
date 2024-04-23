#include <Arduino.h>

//============================= PROGRAM VARIABLES ===============================


//Logic variables
int Range = 50;   // revrite to 1      //Luna range for 0 or 1
uint8_t state = 0;          //variable who decides, what is in progress
float rotate_coeficient = 0;
bool sharp_control = 1;
bool start = 1;

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
    uint32_t lastNumberTick = 0;
};

//function for updateing tick's
void Tick_managing(int time, uint32_t value, uint32_t last, uint32_t *return_last, uint32_t *return_value)
{
    if(millis() - last >= time)
    {
        value++;
        last = millis();
    }

    *return_last =  last;
    *return_value = value;

}

//using tics

TICK Tick_QRE;
TICK Tick_Sharp;