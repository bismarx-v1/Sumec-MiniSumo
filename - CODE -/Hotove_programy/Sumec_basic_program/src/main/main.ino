#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h>
#include "motors.h"
#include "line.h"
#include "laser.h"
#include "IR.h"

// defines for demo
#define Button 13
#define led 14
int Sensor1 = 0;
int Sensor2 = 0;
int Sensor3 = 0;
int SensorRange = 300; //|sensor range setting||sensor range setting||sensor range setting||sensor range setting||sensor range setting|
int Sensor = 0;
int ButtonDown = 0;

int Range = 150;
int cas_zaznam = 0;
int IRzaznam = 0;

int stop = 1;

// void setup()
void setup()
{
  MOTORS_Setup();
  LASER_Setup();
  pinMode(led, OUTPUT);
  Serial.begin(9600);

  if (IRzaznam == 0)
  {
    while (analogRead(IR_IRPin) != 0)
    {
      MOTORS_Go(0, 0);
      Serial.println(millis());
      IRzaznam++;
    }
  }

  for (int i = 0; i++; i == 2000)
  {
    MOTORS_Go(-255 / 2 * -1, 255 / 2 * -1);
    delay(1);
  }

  // Serial.println(analogRead(39));
}

int laser_number;
// promněná určující mód programu
int Global_ModeSelectvar = 0;
// určuje zdali je barva spíš bílá nebo černá
int hodnota_cary = 1000;
// hodnoty pro kalibraci
int hodnota_cerne_kalibrace;
int hodnota_bile_kalibrace;
int kontrolni_hodnota_kalibrace;
int tolerance_mereni = 100; // tolerance mčření slouží k vyvážení nepřesnosti sensorů
// void loop
void loop()
{

  if (digitalRead(Button) == 1)
  {
    Global_ModeSelectvar = 1;
  }

  else
  {
    Global_ModeSelectvar = 0;
  }

  Serial.println("global:");
  Serial.println(Global_ModeSelectvar);

  switch (Global_ModeSelectvar)
  {

  case 0:
    if (LINE_Get(1, hodnota_cary, 0) == 0 && LINE_Get(2, hodnota_cary, 0) == 0)
    {

      // třídící proměná
      laser_number = 0;

      // třídění laserů pomocí proměné

      if (cas_zaznam == 0)
      {
        if (LASER_Get(3, Range, 0) == 1)
        { // přední laser
          laser_number = laser_number + 1;
          digitalWrite(led, HIGH);
        }

        if (LASER_Get(2, Range, 0) == 1)
        { // levý laser
          laser_number = laser_number + 3;
          digitalWrite(led, HIGH);
        }

        if (LASER_Get(1, Range, 0) == 1)
        { // pravý laser
          laser_number = laser_number + 5;
          digitalWrite(led, HIGH);
        }

        if (laser_number == 0)
        {
          digitalWrite(led, LOW);
        }
      }

      // Serial.println(laser_number);

      // rozpohybování Sumce pomocí proměné "laser_number" vzniklé po třídění
      switch (laser_number)
      {

      case 0:
        MOTORS_Go(255 * -1, 255 * -1);
        Serial.println("dopředu");
        break;
      case 1:
        MOTORS_Go(255 * -1, 255 * -1);
        Serial.println("dopředu2");
        break;

      case 3:
        MOTORS_Go(-255 / 2 * -1, 255 / 2 * -1);
        Serial.println("strana1");
        break;

      case 5:
        MOTORS_Go(255 / 2 * -1, -255 / 2 * -1);
        Serial.println("strana2");
        break;

      case 4:
        MOTORS_Go(255 * -1, 200 * -1);
        Serial.println("šikmo1");
        delay(100);
        break;

      case 6:
        MOTORS_Go(200 * -1, 255 * -1);
        Serial.println("šikmo2");
        delay(100);
        break;

      case 9:
        MOTORS_Go(255 * -1, 255 * -1);
        Serial.println("dopředu");
        break;
      }

      // možnost zastavení programu pomocí stop proměné
      while (stop == 0)
      {
        MOTORS_Go(0, 0);
      }

      if (cas_zaznam > 0)
      {
        delay(1);
        cas_zaznam = cas_zaznam - 1;
      }
    }

    // dotek bílé čáry levím senzorem
    if (LINE_Get(1, hodnota_cary, 0) == 1)
    {
      MOTORS_Go(255 / 2 * -1, -255 / 2 * -1);
      delay(500);
      cas_zaznam = 10;
    }
    // dotek bílé čáry pravým senzorem
    if (LINE_Get(2, hodnota_cary, 0) == 1)
    {
      MOTORS_Go(-255 / 2 * -1, 255 / 2 * -1);
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

    while (hodnota_cerne_kalibrace - LINE_Get(2, hodnota_cary, 1) <= hodnota_cerne_kalibrace - tolerance_mereni)
    {
      Serial.println(LINE_Get(2, hodnota_cary, 1));
      MOTORS_Go(255 * -1, 255 * -1);
    }
    hodnota_bile_kalibrace = LINE_Get(2, hodnota_cary, 1);

    kontrolni_hodnota_kalibrace = hodnota_cary;
    hodnota_cary = hodnota_cerne_kalibrace / 2;

    if (hodnota_bile_kalibrace > hodnota_cary) // pokud bude hraniční hodnota moc vysoká změní se hraniční hodnota na původní hodnotu
    {
      hodnota_cary = kontrolni_hodnota_kalibrace; // změna na původní hodnotu
      MOTORS_Go(0, 0);
      Serial.println("kalibrace nevysla");
      for (int i = 0; i == 10; i++)
      {
        digitalWrite(led, 1);
        delay(1000);
        digitalWrite(led, 0);
        delay(1000);
      }
    }

    else
    {
      MOTORS_Go(255, 255);
      Serial.print("Kalibrace úspěšně provedena, aktuální hraniční hodnota:");
      Serial.println(hodnota_cary);

      delay(250);
    }

    Serial.println("konec");
		while (analogRead(IR_IRPin) != 0)
    {
      MOTORS_Go(0, 0);
      Serial.println(millis());
      IRzaznam++;
    }
    Global_ModeSelectvar = 0;
    break;
  }
}