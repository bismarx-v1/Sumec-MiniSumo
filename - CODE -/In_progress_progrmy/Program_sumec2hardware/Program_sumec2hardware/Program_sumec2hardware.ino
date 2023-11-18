#include <IRremote.h>
#include <Wire.h>
#include "motors.h"
#include "line.h"
#include "IRstart.h"
#include "TfLunaEsp32S3.h"

#define tlacitko 2
#define led 15
//#define RC5 0

#if defined (RC5)
    #define ADDR_PROGRAM  11
    #define ADDR_START    7
#else
    #define ADDR_PROGRAM  0
    #define ADDR_START    3
#endif

// defines for demo
#define Button 13
int Sensor1 = 0;
int Sensor2 = 0;
int Sensor3 = 0;
int Range = 40;  //|sensor range setting||sensor range setting||sensor range setting||sensor range setting||sensor range setting|
int Sensor = 0;
int ButtonDown = 0;

// časovo ledkové proměné
int led_control = 0;
int cas_zaznam = 0;
int zapvyp = 1;

int stop = 1;
// promněná určující mód programu
int Global_ModeSelectvar = 0;
int rady = 0;
const int LEDPin = 15;
TaskHandle_t Task1;
int LEDBlink = 0;

//IR

int code;
int adres;
int comand_first;
int comand;
int DohaioID;
int start_control = 0;

void IRstart() {
  while (start_control == 0) {
    //IR čekání
    decode_results results;

    if (irrecv.decode(&results)) {

      code = results.value & 0x7FF;
      comand_first = code & 0x3F;
      comand = comand_first / 0b10;
      adres = code / 0b1000000;

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
      }

      if (adres == ADDR_START) {
        if (comand == DohaioID) {
          Serial.println("jedeme");
          start_control = 1;
        } else {
          Serial.println("špatný code");
        }
      }

      // resume IR reception
      irrecv.resume();
    }
  }
}

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

  Serial.begin(9600);
  pinMode(tlacitko, INPUT);
  pinMode(led, OUTPUT);
  
  MOTORS_Setup();
  
  TfL_Setup();
  TfL_SetAddrs();

  irrecv.enableIRIn();
  IRstart();

  xTaskCreatePinnedToCore(CodeForTask1, "Task_1", 3500, NULL, 0, &Task1, 0); /*Core*/
}

int laser_number;
// určuje zdali je barva spíš bílá nebo černá
int hodnota_cary = 1000;
// hodnoty pro kalibraci
int hodnota_cerne_kalibrace;
int hodnota_bile_kalibrace;
int kontrolni_hodnota_kalibrace;
int tolerance_mereni = 100;  // tolerance mčření slouží k vyvážení nepřesnosti sensorů

void loop() {

  LEDBlink = 1;
  start_control = 0;

  if (digitalRead(tlacitko) == HIGH) {
    LEDBlink = 0;
    MOTORS_Go(0, 0);
    Serial.println("OK");
    IRstart();
  }

  switch (Global_ModeSelectvar) {

    case 0:
      //if (LINE_Get(1, hodnota_cary, 0) == 0 && LINE_Get(2, hodnota_cary, 0) == 0)
      //{

      // třídící proměná
      laser_number = 0;



      // třídění laserů pomocí proměné

      if (cas_zaznam == 0) {
        if (TfL_Get(0x12) < Range && TfL_Get(0x12) > 0) {  // přední laser
          laser_number = laser_number + 1;
        }

        if (TfL_Get(0x11) < Range && TfL_Get(0x11) > 0) {  // levý laser
          laser_number = laser_number + 3;
        }

        if (TfL_Get(0x13) < Range && TfL_Get(0x13) > 0) {  // pravý laser
          laser_number = laser_number + 5;
        }
      }

      // Serial.println(laser_number);

      // rozpohybování Sumce pomocí proměné "laser_number" vzniklé po třídění
      switch (laser_number) {

        case 0:
          MOTORS_Go(255, 255);
          //Serial.println("dopředu");
          break;
        case 1:
          MOTORS_Go(255, 255);
          //Serial.println("dopředu2");
          break;

        case 3:
          MOTORS_Go(-255 / 2, 255 / 2);
          //Serial.println("strana1");
          break;

        case 5:
          MOTORS_Go(255 / 2, -255 / 2);
          //Serial.println("strana2");
          break;

        case 4:
          MOTORS_Go(255, 150);
          //Serial.println("šikmo1");
          delay(100);
          break;

        case 6:
          MOTORS_Go(150, 255);
          //Serial.println("šikmo2");
          delay(100);
          break;

        case 9:
          MOTORS_Go(255, 255);
          //Serial.println("dopředu");
          break;
      }

      // možnost zastavení programu pomocí stop proměné
      while (stop == 0) {
        MOTORS_Go(0, 0);
      }

      if (cas_zaznam > 0) {
        delay(1);
        cas_zaznam = cas_zaznam - 1;
      }
      //}

      // dotek bílé čáry levím senzorem
      if (LINE_Get(1, hodnota_cary, 0) == 1) {
        MOTORS_Go(255 / 2, -255 / 2);
        delay(500);
        cas_zaznam = 10;
      }
      // dotek bílé čáry pravým senzorem
      if (LINE_Get(2, hodnota_cary, 0) == 1) {
        MOTORS_Go(-255 / 2, 255 / 2);
        delay(500);
        cas_zaznam = 10;
      }
      break;

    case 1:
      Serial.println("v kalibraci");

      MOTORS_Go(0, 0);
      delay(2000);

      hodnota_cerne_kalibrace = LINE_Get(2, hodnota_cary, 1);
      Serial.println(hodnota_cerne_kalibrace);
      delay(100);

      while (hodnota_cerne_kalibrace - LINE_Get(2, hodnota_cary, 1) <= hodnota_cerne_kalibrace - tolerance_mereni) {
        Serial.println(LINE_Get(2, hodnota_cary, 1));
        MOTORS_Go(255, 255);
      }
      hodnota_bile_kalibrace = LINE_Get(2, hodnota_cary, 1);

      kontrolni_hodnota_kalibrace = hodnota_cary;
      hodnota_cary = hodnota_cerne_kalibrace / 2;

      if (hodnota_bile_kalibrace > hodnota_cary)  // pokud bude hraniční hodnota moc vysoká změní se hraniční hodnota na původní hodnotu
      {
        hodnota_cary = kontrolni_hodnota_kalibrace;  // změna na původní hodnotu
        MOTORS_Go(0, 0);
        Serial.println("kalibrace nevysla");
      }

      else {
        MOTORS_Go(255, 255);
        Serial.print("Kalibrace úspěšně provedena, aktuální hraniční hodnota:");
        Serial.println(hodnota_cary);

        delay(250);
      }


      Global_ModeSelectvar = 0;
      break;
  }
}