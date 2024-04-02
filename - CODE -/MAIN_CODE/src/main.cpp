#include <Arduino.h>
#include "pinsAndVariables.h"
#include "QRE1113.h"            //befor update
#include "DRV8874PWPR.h"        //befor update



H_bridge Motors(5000, 8);

void setup() 
{
    pinMode(48, OUTPUT);
    Serial.begin(9600);
}

void loop()
{

    delay(400);
    Serial.println("huh");
    digitalWrite(48, HIGH);
}
