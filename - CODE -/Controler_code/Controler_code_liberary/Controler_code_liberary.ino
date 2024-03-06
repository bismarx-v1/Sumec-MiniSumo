#include "IRremote.h"

IRsend irsend;
#define Button_Program 6
#define Button_Start 5


void setup() {
  Serial.begin(9600);
  pinMode(Button_Program, INPUT);
  pinMode(Button_Start, INPUT);
}

void loop() {
  if(digitalRead(Button_Program) == 1 && digitalRead(Button_Start) == 0)
  {
    while(digitalRead(Button_Program) == 1)
    {

    }

    Serial.println("program");
    irsend.sendRC5(11, 10, 0, 1);  
  }

  if(digitalRead(Button_Program) == 0 && digitalRead(Button_Start) == 1)
  {
    while(digitalRead(Button_Start) == 1)
    {

    }

    Serial.println("go");
    irsend.sendRC5(7, 10);  
  }
}