#include <IRremote.h>
#include <Wire.h>
#include "motors.h"
#include "line.h"
#include "TfLunaEsp32S3.h"
#include "rogram_sumec2HW_promene.h"

/*================================IR čekání -> začátek==================================
  !!!!!!!!!!!!!!!! zapíná se pomocí levého horního červeného tlačítka !!!!!!!!!!!!!!!!!!!!
*/
void IRstart() {
  
  //IR čekání
  while (start_control == 0) {
  
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

      //fáze program
      if (adres == ADDR_PROGRAM) {
        DohaioID = comand;
        Serial.print("DohaioID: ");
        Serial.println(DohaioID);
        Serial.println(" ");
        digitalWrite(led, HIGH);
        delay(100);
        digitalWrite(led, LOW);
        delay(100);
        digitalWrite(led, HIGH);
        delay(100);
        digitalWrite(led, LOW);
        delay(100);
        start_control = 1;
      }

      //fáze startováni
      if (adres == ADDR_START) {
        if (comand == DohaioID) {
          Serial.println("jedeme");
          start_control = 1;
        } else {
          Serial.println("špatný code");
        }
      }

      irrecv.resume();
    }
  }
}
//================================IR čekání -> konec==================================

//================================LED blikání -> začátek================================
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
//================================LED blikání -> konec================================




// void setup()
void setup() {

  Serial.begin(9600); //  příprava Serialu a nastavení rychlosti Serialu

  pinMode(tlacitko, INPUT);  //nastavení test tlačítka na vstup
  pinMode(led, OUTPUT);  //nastavení kontrolní LED na výstup
  
  MOTORS_Setup(); //stup pro motory
  
  //TF_luna setup a nastavení adres
  //TfL_Setup();
  //TfL_SetAddrs();

  //čekání na IR 
  irrecv.enableIRIn();
  IRstart();

  // identifikace správného zpuštění
  LEDBlink = 1;
  delay(250);
  LEDBlink = 0;

  // čekání na odstoupení majitelů robotů na odstoupení z ringu -> Olomouc
  delay(5000-200);
  //Olomouc - Pravidla - otoceni min o 90 stupnu 
  MOTORS_Go(255, -255);
  delay(250);


  xTaskCreatePinnedToCore(CodeForTask1, "Task_1", 3500, NULL, 0, &Task1, 0); /*Core*/
}

//======================================setup -> konec, loop -> začátek================================================

void loop() {

  LEDBlink = 1;
  start_control = 0;

  // po stisknutí TEST tlačítka nastane čekání na IR
  if (digitalRead(tlacitko) == HIGH) {
    LEDBlink = 0;
    MOTORS_Go(0, 0);
    IRstart();

    // identifikace správného zpuštění
    LEDBlink = 1;
    delay(250);
    LEDBlink = 0;

    // čekání na odstoupení majitelů robotů na odstoupení z ringu -> Olomouc
    delay(5000-250);
    //Olomouc - Pravidla - otoceni min o 90 stupnu 
    MOTORS_Go(255, -255);
    delay(250);
  }

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

