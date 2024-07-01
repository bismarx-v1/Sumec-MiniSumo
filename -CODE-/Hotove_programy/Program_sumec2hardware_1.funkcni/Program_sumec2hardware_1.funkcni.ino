#include <IRremote.h>
#include <Wire.h>
#include "motors.h"
#include "line.h"
#include "TfLunaEsp32S3.h"
#include "rogram_sumec2HW_promene.h"

//================================IR čekání -> začátek==================================

void IRstart() {
  
  while (start_control == 0) {

    decode_results results;

    if (irrecv.decode(&results)) {  //čeká na příchozí signál 

      code = results.value & 0x7FF;  //z přijatého signálu vezme pouze posledních jedenást hodnot a dosadí do proměné code (BIN)
      comand_first = code & 0x3F;    //vytažení posledních 6 hodnot (Dohayo ID)
      comand = comand_first / 0b10;  //vyjmutí poslední hodnoty 
      adres = code / 0b1000000;      //z přijatého signálu vezme prvních 5 hodnot (Adresa) 

      //vypsání všsch hodnot z IR, nejdřívě BIN potom DEC  

      /*Serial.println("");
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
      Serial.println("==========");*/


      //fáze program
      if (adres == ADDR_PROGRAM) {
        DohaioID = comand;
        Serial.print("DohaioID: ");
        Serial.println(DohaioID);
        Serial.println(" ");
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

void CodeForTask1(void * parameter) {	/*Code for core 0*/
	//Serial.print("Core ["); Serial.print(xPortGetCoreID()); Serial.println("] started");	//print this core
	
	for(;;) {	//void loop()
		switch(LEDBlink) {
			case 0:
				if(LedBlinkState != 0) {
					//LedBlinkState = 0;
					digitalWrite(LEDPin, 0);
					break;
				}
				
				else {
					break;
				}
			
			case 1:
				if(LedBlinkState != 1) {
					//LedBlinkState = 1;
					digitalWrite(LEDPin, 1);
					delay(100);
					digitalWrite(LEDPin, 0);
					delay(100);
					break;
				}
				
				else {
					break;
				}
			
			case 2:
				if(LedBlinkState != 2) {
					LedBlinkState = 2;
					digitalWrite(LEDPin, 1);
					delay(500);
					digitalWrite(LEDPin, 0);
					delay(200);
					digitalWrite(LEDPin, 1);
					delay(200);
					digitalWrite(LEDPin, 0);
					delay(200);
					break;
				}
				
				else {
					break;
				}
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
  
  //TF_luna setup a nastavení adres                                               LUNY
  //TfL_Setup();  
  //SetAddrLabel:  
  //TfL_SetAddrs();                         

  /*if(TfL_IsSet()!=1) {	//zkontroluj jestli se luny pripojily                   LUNY
		digitalWrite(15, HIGH);
		delay(500);
		digitalWrite(15, LOW);
		delay(500);
		digitalWrite(15, HIGH);
		delay(500);
		digitalWrite(15, LOW);
		delay(500);
		goto SetAddrLabel;
	}*/

  //čekání na IR 
  irrecv.enableIRIn();
  IRstart();


  xTaskCreatePinnedToCore(CodeForTask1, "Task_1", 3500, NULL, 0, &Task1, 0); /*Core*/
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

