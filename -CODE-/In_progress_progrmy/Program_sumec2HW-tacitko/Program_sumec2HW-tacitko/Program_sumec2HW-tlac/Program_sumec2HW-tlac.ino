#include <IRremote.h>
#include <Wire.h>
#include "motors.h"
#include "line.h"
#include "TfLunaEsp32S3.h"
#include "rogram_sumec2HW_promene.h"


//LED blikání
void CodeForTask1(void* parameter) { /*Code for core 0*/
  for (;;) {  //void loop()
    switch (LEDBlink) {
      case 0:
        digitalWrite(LEDPin, 0);
        break;
      case 1:
        digitalWrite(LEDPin, 1);
        delay(100);
        digitalWrite(LEDPin, 0);
        delay(100);
        break;
    }
  }
}
//LED

void blikani()
{
  if(millis() % 200 == 0)
  {
    digitalWrite(LEDPin, 1);
  }

  if(millis() % 200 == 99)
  {
    digitalWrite(LEDPin, 0);
  }
}




// void setup()
void setup() {

  Serial.begin(9600); //  příprava Serialu a nastavení rychlosti Serialu

  pinMode(tlacitko, INPUT);  //nastavení test tlačítka na vstup
  pinMode(led, OUTPUT);  //nastavení kontrolní LED na výstup
  
  MOTORS_Setup(); //stup pro motory
  
  //TF_luna setup a nastavení adres
  //TfL_Setup();
  //TfL_SetAddrs();


  xTaskCreatePinnedToCore(CodeForTask1, "Task_1", 3500, NULL, 0, &Task1, 0); /*Core*/

  while (digitalRead(tlacitko) == 0) 
  {
    delay(10);
  }
  
  LEDBlink = 1;
  delay(250);
  LEDBlink = 0;

  delay(5000-250);
  //Olomouc - Pravidla - otoceni min o 90 stupnu 
  MOTORS_Go(255, -255);
  delay(250);
}

void loop() {

  LEDBlink = 1;

// v případě že chcete zastavovat a rozjiždět Sumce pomocí tlačítka, odkomentujte. !Upozornění, nefunguje úplně perfeektně!+

  /*Serial.println(digitalRead(tlacitko));
  if (digitalRead(tlacitko) == HIGH) {
    LEDBlink = 0;
    MOTORS_Go(0, 0);
    Serial.println("OK");

    while(digitalRead(tlacitko) == HIGH)
    {
      Serial.println("jedna");
    }

    while(digitalRead(tlacitko) == LOW)
    {
      Serial.println("nula");
    }

    while(digitalRead(tlacitko) == HIGH)
    {
      Serial.println("jedna");
    }
  }*/

  // třídící proměná
  laser_number = 0;

  // třídění laserů pomocí proměné
  if (TfL_Get(0x12) < Range && TfL_Get(0x12) > 0) {  // přední laser
    laser_number = laser_number + 1;
  }

  if (TfL_Get(0x11) < Range && TfL_Get(0x11) > 0) {  // levý laser
    laser_number = laser_number + 3;
  }

  if (TfL_Get(0x13) < Range && TfL_Get(0x13) > 0) {  // pravý laser
    laser_number = laser_number + 5;
  }


  // rozpohybování Sumce pomocí proměné "laser_number" vzniklé po třídění
  switch (laser_number) {

    case 0:
      MOTORS_Go(255, 255);
      //Serial.println("dopředu");
      break;

    case 1:
      MOTORS_Go(255, 255);
      break;

    case 3:
      MOTORS_Go(-255 / 2, 255 / 2);
      break;

    case 5:
      MOTORS_Go(255 / 2, -255 / 2);
      break;

    case 4:
      MOTORS_Go(255, 150);
      delay(100);
      break;

    case 6:
      MOTORS_Go(150, 255);
      delay(100);
      break;

    case 9:
      MOTORS_Go(255, 255);
      break;
      
  }

  // dotek bílé čáry levým senzorem
  if (LINE_Get(1, hodnota_cary, 0) == 1) {
    MOTORS_Go(255 / 2, -255 / 2);
    delay(500);
  }

  // dotek bílé čáry pravým senzorem
  if (LINE_Get(2, hodnota_cary, 0) == 1) {
    MOTORS_Go(-255 / 2, 255 / 2);
    delay(500);
  }
}

