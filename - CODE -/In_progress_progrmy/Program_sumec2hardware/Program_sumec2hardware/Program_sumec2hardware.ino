#include <IRremote.h>
#include <Wire.h>
#include "motors.h"
#include "line.h"
#include "TfLunaEsp32S3.h"
#include "rogram_sumec2HW_promene.h"
#include "Program_sumec2_funkce.h"

//================================IR čekání -> začátek==================================


// void setup()
void setup() {

  Serial.begin(9600); //  příprava Serialu a nastavení rychlosti Serialu

  pinMode(tlacitko, INPUT);  //nastavení test tlačítka na vstup
  pinMode(led, OUTPUT);  //nastavení kontrolní LED na výstup
  
  MOTORS_Setup(); //stup pro motory  
  TfL_Setup();  //stup pro luny
  irrecv.enableIRIn();  //čekání na IR 
  IRstart(); //čekání na IR 

  xTaskCreatePinnedToCore(CodeForTask1, "Task_m", 3500, NULL, 0, &Task1, 0); /*1, 2, 7, 6*/
}

//======================================setup -> konec, loop -> začátek================================================

void loop() {

  delay(10);
  start_control = 0;

  // po stisknutí TEST tlačítka nastane čekání na IR
  if (digitalRead(tlacitko) >= 1) {
    LEDBlink = 0;
    MOTORS_Go(0, 0);
    IRstart();

  }

  LEDBlink = 1;

  // třídící proměná
  laser_number = 0;

  // třídění laserů pomocí proměné
  if (TfL_Get(TfL_Addr2) < Range && TfL_Get(0x12) > 0) {  // přední laser
    //laser_number = laser_number + 1;
  }

  if (TfL_Get(TfL_Addr1) < Range && TfL_Get(0x11) > 0) {  // levý laser
    laser_number = laser_number + 3;
  }

  if (TfL_Get(TfL_Addr3) < Range && TfL_Get(0x13) > 0) {  // pravý laser
    laser_number = laser_number + 5;
  }


  // rozpohybování Sumce pomocí proměné "laser_number" vzniklé po třídění
  switch (laser_number) {

    case 0:
      MOTORS_Go(255, 255);
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

    case 8:
      MOTORS_Go(255, 255);
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

