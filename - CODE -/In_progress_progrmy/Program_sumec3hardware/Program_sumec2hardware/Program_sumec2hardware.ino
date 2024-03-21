#include <SharpIR.h>
#include <IRremote.h>
#include <Wire.h>
#include "motors.h"
#include "line.h"
#include "TfLunaEsp32S3.h"
//#include "Sharp.h"
#include "rogram_sumec2HW_promene.h"
#include "Program_sumec2_funkce.h"

//================================IR čekání -> začátek==================================


// void setup()
void setup() {

  Serial.begin(9600); //  příprava Serialu a nastavení rychlosti Serialu

  pinMode(tlacitko, INPUT);  //nastavení test tlačítka na vstup
  pinMode(LEDPin, OUTPUT);  //nastavení kontrolní LED na výstup
  MOTORS_Setup(); //stup pro motory  
  TfL_Setup();  //stup pro luny
  irrecv.enableIRIn();  //čekání na IR 
  IRstart(); //čekání na IR

  // Rybnik pravidla - otoceni k oponentovy

    MOTORS_Go(255, -255);
    delay(800);

}

//======================================setup -> konec, loop -> začátek================================================

void loop() {

  start_control = 0;
  //blink();

  // po stisknutí TEST tlačítka nastane čekání na IR
  if (digitalRead(tlacitko) >= 1) {
    LEDBlink = 0;
    MOTORS_Go(0, 0);
    IRstart();

  }

  // třídící proměná
  laser_number = 0;

  // třídění laserů pomocí proměné
  if (TfL_Get(TfL_Addr2) < Range && TfL_Get(TfL_Addr2) > 0) {  // přední laser
    laser_number = laser_number + 1;
  }

  if (TfL_Get(TfL_Addr1) < Range && TfL_Get(TfL_Addr1) > 0) {  // levý laser
    laser_number = laser_number + 3;
  }

  if (TfL_Get(TfL_Addr3) < Range && TfL_Get(TfL_Addr3) > 0) {  // pravý laser
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
      MOTORS_Go(-255 , 255);
      break;

    case 5:
      MOTORS_Go(255, -255);
      break;

    case 4:
      MOTORS_Go(255, 0);
      //delay(100);
      break;

    case 6:
      MOTORS_Go(0, 255);
      //delay(100);
      break;

    case 8:
      MOTORS_Go(255, 255);
      break;

    case 9:
      MOTORS_Go(255, 255);
      break;
      
  }

  
  // dotek bílé čáry levým senzorem
  if (LINE_Get(2, hodnota_cary, 0) == 1) {

    Serial.println("qre 1");
    MOTORS_Go(255, -255);
    if(qre_stav == 1)
    {
      delay(cas_otaceni*2);
      qre_stav = 0;    
    }
    else
    {
      delay(cas_otaceni); 
      qre_stav = 1;
      cas_dotek = millis();   
    }

    //qre_number = 1;   // rozdeleni pro operace okolo hranic ringu
    //cas_dotek = millis();
  }

  // dotek bílé čáry pravým senzorem
  if (LINE_Get(3, hodnota_cary, 0) == 1) {
    
    Serial.println("qre 2");
    MOTORS_Go(-255, 255);
    if(qre_stav == 1)
    {
      delay(cas_otaceni*2);
      qre_stav = 0;  
    }
    else
    {
      delay(cas_otaceni); 
      qre_stav = 1;
      cas_dotek = millis();
    }


    //qre_number = 2;   // rozdeleni pro operace okolo hranic ringu
    //cas_dotek = millis();
  }

  if(millis() - cas_dotek >= cas_otaceni+200)
  {
    qre_stav = 0;  
  }

  /*if(LINE_Get(3, hodnota_cary, 0) == 1 && LINE_Get(2, hodnota_cary, 0) == 1)
  {
    MOTORS_Go(-255, 255);
    delay(cas_otaceni+100);
  }*/
  


 /*
  // nove vylepseni:

  if(millis()-cas_dotek<=(1800+cas_otaceni) && qre_number!=0 && TfL_Get(TfL_Addr1) < stret_vzdalenost || qre_stav == 1)
  {
    qre_stav = 1;
    kstav = millis();

    if(millis()-kstav >= 500)

      qre_stav = 0;

      if(qre_number == 1)
      {
        MOTORS_Go(255, -255);
        delay(1000);
      }

      if(qre_number == 2)
      {
        MOTORS_Go(-255, 255);
        delay(1000);
      }
  }*/
}

