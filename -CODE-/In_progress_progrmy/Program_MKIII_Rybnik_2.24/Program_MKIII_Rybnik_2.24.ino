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

  pinMode(scharp_L, INPUT);
  pinMode(scharp_P, INPUT);

  MOTORS_Setup(); //stup pro motory  
  TfL_Setup();  //stup pro luny
  irrecv.enableIRIn();  //čekání na IR 
  IRstart(); //čekání na IR

  // Rybnik pravidla - otoceni k oponentovy

    /*MOTORS_Go(255/BATERRY_MODE, -255/BATERRY_MODE);     !Nezapomenout odkomentovat
    delay(600);*/

}

//======================================setup -> konec, loop -> začátek================================================

void loop() {

  start_control = 0;
  //blink();

  // po stisknutí TEST tlačítka nastane čekání na IR - zakomentovano kvuly nahodnemu zastavovani
  /*if (digitalRead(tlacitko) >= 1) {
    LEDBlink = 0;
    MOTORS_Go(0, 0);
    IRstart();

  }*/

  // třídící proměná
  laser_number = 0;

  // třídění laserů pomocí proměné
  if (TfL_Get(TfL_Addr2) < Range && TfL_Get(TfL_Addr2) > 0) {  // přední laser
    laser_number = laser_number + 1;
    //primar_luna = 1;
  }

  if (TfL_Get(TfL_Addr1) < Range && TfL_Get(TfL_Addr1) > 0) {  // levý laser
    laser_number = laser_number + 3;
  }

  if (TfL_Get(TfL_Addr3) < Range && TfL_Get(TfL_Addr3) > 0) {  // pravý laser
    laser_number = laser_number + 5;
  }

  /*if(TfL_Get(TfL_Addr2) < Range)
  {
    primar_luna = 0;
  }*/

  // rozpohybování Sumce pomocí proměné "laser_number" vzniklé po třídění
  switch (laser_number) {

    case 0:
      MOTORS_Go(255/BATERRY_MODE, 255/BATERRY_MODE);
      //tactic_stop = 0;
      break;

    case 1:
      //MOTORS_Go(255, 255);
      if(tactic_stop == 0)
      {
        if(posledni_qre == 2)
        {

          MOTORS_Go(255/BATERRY_MODE , -50/BATERRY_MODE);
          delay(300);

          while(digitalRead(scharp_L) == 1)
          {
            MOTORS_Go(255/BATERRY_MODE , 255/BATERRY_MODE);  
          }
          delay(200);

          for(int i=0; i<400; i++)
          {
            
            delay(1);
            MOTORS_Go(-50/BATERRY_MODE , 255/BATERRY_MODE);

            if(TfL_Get(TfL_Addr1) < Range && TfL_Get(TfL_Addr1) > 0)
            {
              i = 400;
            }
          }

          tactic_stop = 1;

        }

        if(posledni_qre == 1)
        {
          MOTORS_Go(-50/BATERRY_MODE , 255/BATERRY_MODE);
          delay(300);

          while(digitalRead(scharp_P) == 1)
          {
            MOTORS_Go(255/BATERRY_MODE , 255/BATERRY_MODE);  
          }
          delay(200);

          for(int i=0; i<400; i++)
          {
            delay(1);
            MOTORS_Go(255/BATERRY_MODE , -50/BATERRY_MODE);

            if(TfL_Get(TfL_Addr1) < Range && TfL_Get(TfL_Addr1) > 0)
            {
              i = 400;
            }
          }

          tactic_stop = 1;
        }
      }

      break;

    case 3:
      MOTORS_Go(-255 , 255);
      break;

    case 5:
      MOTORS_Go(255/BATERRY_MODE , -255/BATERRY_MODE);
      break;

    case 4:
      MOTORS_Go(0, 255);
      delay(100);
      break;

    case 6:
      MOTORS_Go(255, 0);
      delay(100);
      break;

    case 8:
      MOTORS_Go(255/BATERRY_MODE, 255/BATERRY_MODE);
      break;

    case 9:
      MOTORS_Go(255/BATERRY_MODE, 255/BATERRY_MODE);
      break;
      
  }
 
  // dotek bílé čáry levým senzorem
  if (LINE_Get(2, hodnota_cary, 0) == 1) {

    Serial.println("qre 1");
    MOTORS_Go(255/BATERRY_MODE, -255/BATERRY_MODE);

    if(qre_stav == 1)                            //pokud pred kratkou dobou bylo zpozorováno jiné QRE
    {
      delay((cas_otaceni*2)-100);
      qre_stav = 0;    
    }
    else
    {
      delay(cas_otaceni); 
      qre_stav = 1;
      cas_dotek = millis();   
    }

    posledni_qre = 2;

  }

  // dotek bílé čáry pravým senzorem
  if (LINE_Get(3, hodnota_cary, 0) == 1) {
    
    Serial.println("qre 2");
    MOTORS_Go(-255/BATERRY_MODE, 255/BATERRY_MODE);

    if(qre_stav == 1)                            //pokud pred kratkou dobou bylo zpozorováno jiné QRE
    {
      delay((cas_otaceni*2)-100);
      qre_stav = 0;  
    }
    else
    {
      delay(cas_otaceni); 
      qre_stav = 1;
      cas_dotek = millis();
    }

    posledni_qre = 1;

  }

  if(millis() - cas_dotek >= cas_otaceni+200)    //po uplinutí času se změní stav při detekování QRE
  {
    qre_stav = 0;  
  }
}

