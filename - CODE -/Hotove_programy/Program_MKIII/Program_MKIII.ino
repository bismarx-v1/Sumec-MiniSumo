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

  bailout:

  IRstart(); //čekání na IR

  // Rybnik pravidla - otoceni k oponentovy`

    MOTORS_Go(255/BATERRY_MODE, -255/BATERRY_MODE);
    delay(600);

}

//======================================setup -> konec, loop -> začátek================================================

void IRkonec()
{
  decode_results results;

    if (irrecv.decode(&results)) {  //čeká na příchozí signál 

      code = results.value & 0x7FF;  //z přijatého signálu vezme pouze posledních jedenást hodnot a dosadí do proměné code (BIN)
      comand_first = code & 0x3F;    //vytažení posledních 6 hodnot (Dohayo ID)
      comand = comand_first / 0b10;  //vyjmutí poslední hodnoty 
      adres = code / 0b1000000;      //z přijatého signálu vezme prvních 5 hodnot (Adresa) 

      //vypsání všsch hodnot z IR, nejdřívě BIN potom DEC  

      
      Serial.println("");
      Serial.print("recieved signal: ");
      Serial.print(results.value, BIN);
      Serial.print("    DEC: ");
      Serial.println(results.value);
      Serial.print("code: ");
      Serial.print(code, BIN);
      Serial.print("    DEC: ");
      Serial.println(code);
      Serial.print("adresa: ");
      Serial.print(adres, BIN);
      Serial.print("    DEC: ");
      Serial.println(adres);
      Serial.print("comand_first: ");
      Serial.print(comand_first, BIN);
      Serial.print("    DEC: ");
      Serial.println(comand_first);
      Serial.print("comand: ");
      Serial.print(comand, BIN);
      Serial.print("    DEC: ");
      Serial.println(comand);
      Serial.println("");
      Serial.println("==========");


      //fáze konceni
      if (adres == ADDR_START) {
        if (comand == DohaioID) {
          Serial.println("jedeme");
          start_control = 1;
          LEDBlink = 1;

          if(konec == 1)
          {
            //konec = 0;
            goto bailout;
          }

        } else {
          Serial.println("špatný code");
        }
      }

      irrecv.resume();
    }
  }

void loop() {

  start_control = 0;
  IRkonec();

  // po stisknutí TEST tlačítka nastane čekání na IR
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
      break;

    case 1:
      MOTORS_Go(255, 255);  
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

  }

  if(millis() - cas_dotek >= cas_otaceni+200)    //po uplinutí času se změní stav při detekování QRE
  {
    qre_stav = 0;  
  }
}

