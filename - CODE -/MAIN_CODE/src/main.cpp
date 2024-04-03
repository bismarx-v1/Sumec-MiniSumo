#include <Arduino.h>
#include "pinsAndVariables.h"
#include "QRE1113.h"            //befor update
#include "DRV8874PWPR.h"        //befor update


void setup() 
{
    pinMode(47, OUTPUT);
    Serial.begin(115200);
}

void loop()
{

    digitalWrite(47, HIGH);
    delay(1000);
    digitalWrite(47, 0);
    delay(1000);
}
