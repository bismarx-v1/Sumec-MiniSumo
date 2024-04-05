
// motors pins:

#define Nsleep 11
#define Left_EN 14
#define Left_PH 12
#define Right_EN 21
#define Right_PH 13

// QRE pins:

#define QRE_left 10
#define QRE_right 9
#define QRE_rear 8

// sharp pins:

#define sharp_left 35
#define sharp_right 16

// leds pins:

#define IRled 38
#define Led_red 47
#define Led_orange 48



//============================= PROGRAM VARIABLES ===============================

uint8_t state;

struct TICK
{
    int tickTime;
    uint32_t tickNumber = 50;
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

int lastQRE = 0;

int LUNAleft;
int LUNAright;
int LUNAmiddle;

bool SHARPleft;
bool SHARPright;


//Motors

int16_t motorLeft;
int16_t motorRight;

