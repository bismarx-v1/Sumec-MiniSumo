#include <IRremote.h>
#include <Wire.h>
#include "motors.h"
#include "line.h"
#include "TfLunaEsp32S3.h"
#include "rogram_sumec2HW_promene.h"


void start() 
{
  
  //čekání
  while (start_control == 0) 
  {
    if(digitalRead(tlacitko) == 1)
    {
      start_control = 1;
    }  

  }
}

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




// void setup()
void setup() {

  Serial.begin(9600); //  příprava Serialu a nastavení rychlosti Serialu

  pinMode(tlacitko, INPUT);  //nastavení test tlačítka na vstup
  pinMode(led, OUTPUT);  //nastavení kontrolní LED na výstup
  
  MOTORS_Setup(); //stup pro motory
  
  //TF_luna setup a nastavení adres
  TfL_Setup();
  TfL_SetAddrs();

  //čekání 
  start();

  xTaskCreatePinnedToCore(CodeForTask1, "Task_1", 3500, NULL, 0, &Task1, 0); /*Core*/
}

void loop() {

  LEDBlink = 1;

  // třídící proměná
  laser_number = 0;

  // třídění laserů pomocí proměné
  if (TfL_Get(0x12) < Range && TfL_Get(0x12) > 0) {  // přední laser
    laser_number = laser_number + 1;
  }

  if (TfL_Get(0x11) < Range && TfL_Get(0x11) > 0) {  // levý laser
    laser_number = laser_number + 3;
    KL_hodnota = 3;
  }

  if (TfL_Get(0x13) < Range && TfL_Get(0x13) > 0) {  // pravý laser
    laser_number = laser_number + 5;
    KL_hodnota = 5;
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

  //Klinč taktika
  if(millis() % 4000 < 15)
  {
    if(TfL_Get(0x12) < 10)
    {
      if(KL_hodnota == 3)
      {
        MOTORS_Go(-45, -255);
        Serial.println("klinc, otacim");
        delay(600);
        MOTORS_Go(-255, -255);
        delay(300);
      }

      if(KL_hodnota == 5)
      {
        MOTORS_Go(-255, -45);
        Serial.println("klinc, otacim");
        delay(600);
        MOTORS_Go(-255, -255);
        delay(300);
      }
    }
  }
}