#include <Arduino.h>
#include "VL53L0X.h"
#include "line.h"
#include "laser.h"
#include "motors.h"
#include "IR.h"

#define led 14


class minisumo_robot{
  public:
    minisumo_robot();
    void utok();
    void basic_utok();
    void kalibrace();
  
  private:
    int hodnota_cary = 1000;
    int laser_number;
    int Range = 300;
    int cas_zaznam = 0;
    int IRzaznam = 0;
    int stop = 1;


};

minisumo_robot::minisumo_robot(){
   MOTORS_Setup();
  LASER_Setup();
  pinMode(led, OUTPUT);
  Serial.begin(9600);


  if(IRzaznam == 0){
    while(analogRead(IR_IRPin)!=0){
      MOTORS_Go(0, 0);
      Serial.println(millis());
      IRzaznam++;
    } 
  }
  
  for(int i=0; i++; i==2000){
    MOTORS_Go(-255/2*-1, 255/2*-1);
    delay(1);
  }

}

void minisumo_robot::utok(){

}

void minisumo_robot::basic_utok(){
  if(LINE_Get(1, hodnota_cary, 0) == 0 && LINE_Get(2, hodnota_cary, 0) == 0){
      
      //třídící proměná
      laser_number = 0;
      
      //třídění laserů pomocí proměné

      if(cas_zaznam == 0){
        if(LASER_Get(3, Range, 0) == 1 ){   // přední laser
          laser_number = laser_number + 1;
          //Serial.println(laser_number);
          digitalWrite(led, HIGH);
        }


        if(LASER_Get(2, Range, 0) == 1 ){   // levý laser
          laser_number = laser_number + 3;
          //Serial.println(laser_number);
          digitalWrite(led, HIGH);
        }

        
        if(LASER_Get(1, Range, 0) == 1 ){   // pravý laser
          laser_number = laser_number + 5;
          //Serial.println(laser_number);
          digitalWrite(led, HIGH);
        }

        if(laser_number == 0 ){
          digitalWrite(led, LOW);
        }
      }

      //Serial.println(laser_number);

      // rozpohybování Sumce pomocí proměné "laser_number" vzniklé po třídění  
      switch(laser_number){

        case 0:
          MOTORS_Go(255*-1, 255*-1);
          Serial.println("dopředu");
        case 1:
          MOTORS_Go(255*-1, 255*-1);
          Serial.println("dopředu"); 
        break;

        case 3:
          while(LASER_Get(3, Range, 0) == 0){
            MOTORS_Go(-255/2*-1, 255/2*-1);
            Serial.println("strana1");
          }
        break;

        case 5:
          while(LASER_Get(3, Range, 0) == 0){
            MOTORS_Go(255/2*-1, -255/2*-1);
            Serial.println("strana2");
          }
        break;

        case 4:
          MOTORS_Go(255*-1, 200*-1);
          Serial.println("šikmo1");
          delay(100);
        break;

        case 6:
          MOTORS_Go(200*-1, 255*-1);
          Serial.println("šikmo2");
          delay(100);
        break;

        case 9:
          MOTORS_Go(255*-1, 255*-1);
          Serial.println("dopředu");
        break;
      }
      
      // možnost zastavení programu pomocí stop proměné
      while(stop == 0){
        MOTORS_Go(0, 0);
        
      }

      if(cas_zaznam > 0){
      delay(1);
      cas_zaznam = cas_zaznam - 1;
      }


    }


    //dotek bílé čáry levím senzorem
    if(LINE_Get(1, hodnota_cary, 0) == 1){
      MOTORS_Go(255/2*-1, -255/2*-1);
      delay(500);
      cas_zaznam = 10;   
    }
    //dotek bílé čáry pravým senzorem
    if(LINE_Get(2, hodnota_cary, 0) == 1){
      MOTORS_Go(-255/2*-1, 255/2*-1);
      delay(500);
      cas_zaznam = 10;   
    }

}

void minisumo_robot::kalibrace(){
  hodnota_cary = LINE_Get(2, hodnota_cary, 0);
  while(hodnota_cary - LINE_Get(2, hodnota_cary, 0) == 240){
    MOTORS_Go(255*-1, 255*-1);
  }

  hodnota_cary == LINE_Get(2, hodnota_cary, 0);
}


minisumo_robot sumec;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  sumec.basic_utok();
}

