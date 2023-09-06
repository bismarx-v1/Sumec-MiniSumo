#include <Arduino.h>
#include "Wire.h"
#include <VL53L0X.h>
#include "line.h"
#include "laser.h"
#include "motors.h"

#define MOTORS_LeftSpeed 5
#define MOTORS_LeftBackward 18
#define MOTORS_LeftForward 19
#define MOTORS_RightSpeed 15
#define MOTORS_RightBackward 2
#define MOTORS_RightForward 4
#define MOTORS_STBY 23



//"LASER_" defines
VL53L0X sensorLeft;
VL53L0X sensorRight;
VL53L0X sensorFront;







int Range = 150;
int cas_zaznam = millis();

int stop = 1;

//void setup()
void setup() {
  MOTORS_Setup();
  LASER_Setup();
  Serial.begin(9600);

  while(LASER_Get(1, Range, 0) == 0 && LASER_Get(2, Range, 0) == 0 && LASER_Get(3, Range, 0) == 0){
    MOTORS_Go(-255/2*-1, 255/2*-1);

    //if(millis() - cas_zaznam == 2000){
      //cas_zaznam = millis();
      //Range = Range + 100;
    //}

    //while(stop == 0){
      //MOTORS_Go(0, 0);
    //}
 }

}




//void loop
void loop() {
  if(LINE_Get(1, 1000, 0) == 0 && LINE_Get(2, 1000, 0) == 0){
    
    if(LASER_Get(3, Range, 0) == 0 && LASER_Get(2, Range, 0) == 0 && LASER_Get(1, Range, 0) == 1){
      Serial.println("vpravo");
      MOTORS_Go(255/2*-1, -255/2*-1);
    }

    if(LASER_Get(3, Range, 0) == 0 && LASER_Get(2, Range, 0) == 1 && LASER_Get(1, Range, 0) == 0){
      Serial.println("vlevo");
      MOTORS_Go(-255/2*-1, 255/2*-1);
    }

    if(LASER_Get(3, Range, 0) == 1 && LASER_Get(2, Range, 0) == 0 && LASER_Get(1, Range, 0) == 0){
      Serial.println("ok");
      MOTORS_Go(255*-1, 255*-1);
      delay(100);
    }

    if(LASER_Get(3, Range, 0) == 0 && LASER_Get(2, Range, 0) == 0 && LASER_Get(1, Range, 0) == 0){
      Serial.println("stop");
      MOTORS_Go(255*-1, 255*-1);
    }

    if(LASER_Get(3, Range, 0) == 1 && LASER_Get(2, Range, 0) == 0 && LASER_Get(1, Range, 0) == 1){
      MOTORS_Go(100*-1, 255*-1);
    }

    if(LASER_Get(3, Range, 0) == 1 && LASER_Get(2, Range, 0) == 1 && LASER_Get(1, Range, 0) == 0){
      MOTORS_Go(255*-1, 100*-1);
    }

    if(LASER_Get(3, Range, 0) == 1 && LASER_Get(2, Range, 0) == 1 && LASER_Get(1, Range, 0) == 1){
      MOTORS_Go(255*-1, 255*-1);
    }
  }

  else{
    MOTORS_Go(255/2*-1, -255/2*-1);
    delay(600);
    
  }

  while(stop == 0){
    MOTORS_Go(0, 0);
  }
}

