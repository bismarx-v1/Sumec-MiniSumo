//"LASER_" imports
#include <Wire.h>
#include <VL53L0X.h>



//"MOTORS_" defines
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

int LASER_DistLeft;
int LASER_DistRight;
int LASER_DistFront;



//defines for demo
#define Button 13
#define led 14
int Sensor1 = 0;
int Sensor2 = 0;
int Sensor3 = 0;
int SensorRange = 300;  //|sensor range setting||sensor range setting||sensor range setting||sensor range setting||sensor range setting|
int Sensor = 0;
int ButtonDown = 0;



//MOTORS_Setup
void MOTORS_Setup() {
  ledcSetup(0, 5000, 8);
  ledcSetup(1, 5000, 8);
  pinMode(MOTORS_LeftBackward, OUTPUT);
  pinMode(MOTORS_LeftForward, OUTPUT);
  pinMode(MOTORS_RightBackward, OUTPUT);
  pinMode(MOTORS_RightForward, OUTPUT);
  pinMode(MOTORS_STBY, OUTPUT);
  ledcAttachPin(MOTORS_LeftSpeed, 0);
  ledcAttachPin(MOTORS_RightSpeed, 1);
}



//LASER_Setup
void LASER_Setup() {
  #define LASER_PinLeft 25
  #define LASER_PinRight 27
  #define LASER_PinFront 26

  pinMode(LASER_PinRight, OUTPUT);
  pinMode(LASER_PinLeft, OUTPUT);
  pinMode(LASER_PinFront, OUTPUT);
  digitalWrite(LASER_PinRight, LOW);
  digitalWrite(LASER_PinLeft, LOW);
  digitalWrite(LASER_PinFront, LOW);

  delay(500);
  Wire.begin();

  digitalWrite(LASER_PinRight, HIGH);
  delay(150);
  sensorLeft.init(true);
  delay(100);
  sensorLeft.setAddress((uint8_t)01);

  digitalWrite(LASER_PinLeft, HIGH);
  delay(150);
  sensorRight.init(true);
  delay(100);
  sensorRight.setAddress((uint8_t)02);

  digitalWrite(LASER_PinFront, HIGH);
  delay(150);
  sensorFront.init(true);
  delay(100);
  sensorFront.setAddress((uint8_t)03);

  sensorLeft.startContinuous();
  sensorRight.startContinuous();
  sensorFront.startContinuous();

}



//LASER_Get
bool LASER_Get(int LASER_Sensor, int LASER_Thereshold) {
  if(LASER_Sensor==1) {
    LASER_DistLeft=sensorLeft.readRangeContinuousMillimeters();
    if(LASER_DistLeft<LASER_Thereshold) {
      return true;
    }
    else {
      return false;
    }
  }

  if(LASER_Sensor==2) {
    LASER_DistRight=sensorRight.readRangeContinuousMillimeters();
    if(LASER_DistRight<LASER_Thereshold) {
      return true;
    }
    else {
      return false;
    }
  }

  if(LASER_Sensor==3) {
    LASER_DistFront=sensorFront.readRangeContinuousMillimeters();
    if(LASER_DistFront<LASER_Thereshold) {
      return true;
    }
    else {
      return false;
    }
  }
}



//MOTORS_Brake
void MOTORS_Brake() {
  digitalWrite(MOTORS_LeftForward,LOW);
  digitalWrite(MOTORS_RightForward,LOW);
  digitalWrite(MOTORS_LeftBackward,LOW);
  digitalWrite(MOTORS_RightBackward,LOW);
  ledcWrite(0, 255);
  ledcWrite(1, 255);
  digitalWrite(MOTORS_STBY, HIGH);
}



//MOTORS_Go
void MOTORS_Go(int MOTORS_SpeedLeft, int MOTORS_SpeedRight) {//speed is from -255 to 255
  if(MOTORS_SpeedLeft < -255) {
    MOTORS_SpeedLeft = -255;
  }
  else {
    if(MOTORS_SpeedLeft > 255) {
      MOTORS_SpeedLeft = 255;
    }
    else {
      if(MOTORS_SpeedLeft < 0) {
        digitalWrite(MOTORS_LeftForward,LOW);
        digitalWrite(MOTORS_LeftBackward,HIGH);
      }
      else {
        if(MOTORS_SpeedLeft > 0) {
          digitalWrite(MOTORS_LeftForward,HIGH);
          digitalWrite(MOTORS_LeftBackward,LOW);
        }
        else {
          digitalWrite(MOTORS_LeftForward,LOW);
          digitalWrite(MOTORS_LeftBackward,LOW);
          MOTORS_SpeedLeft = 255;
        }
      }
    }
  }
  
  if(MOTORS_SpeedRight < -255) {
    MOTORS_SpeedRight = -255;
  }
  else {
    if(MOTORS_SpeedRight > 255) {
      MOTORS_SpeedRight = 255;
    }
    else {
      if(MOTORS_SpeedRight < 0) {
        digitalWrite(MOTORS_RightForward,LOW);
        digitalWrite(MOTORS_RightBackward,HIGH);
      }
      else {
        if(MOTORS_SpeedRight > 0) {
          digitalWrite(MOTORS_RightForward,HIGH);
          digitalWrite(MOTORS_RightBackward,LOW);
        }
        else {
          digitalWrite(MOTORS_RightForward,LOW);
          digitalWrite(MOTORS_RightBackward,LOW);
          MOTORS_SpeedRight = 255;
        }
      }
    }
  }
  if(MOTORS_SpeedLeft < 0) {
    MOTORS_SpeedLeft = MOTORS_SpeedLeft*-1;
  }
  
  if(MOTORS_SpeedRight < 0) {
    MOTORS_SpeedRight = MOTORS_SpeedRight*-1;
  }
  
  ledcWrite(0, MOTORS_SpeedLeft);
  ledcWrite(1, MOTORS_SpeedRight);
  digitalWrite(MOTORS_STBY, HIGH);
  return;
}



//void setup()
void setup() {
  MOTORS_Setup();
  LASER_Setup();
  pinMode(led, OUTPUT);

}



//void loop
void loop() {
  while(digitalRead(Button)!=1) { //wait for button pressed
    delay(1);
  }
  
  while(digitalRead(Button)==1) { //wait for button released
    delay(1);
  }

  digitalWrite(led, HIGH);  //led flash 1
  delay(200);
  digitalWrite(led, LOW);
  delay(800);

  digitalWrite(led, HIGH);  //led flash 2
  delay(200);
  digitalWrite(led, LOW);
  delay(800);

  digitalWrite(led, HIGH);  //led flash 3
  delay(200);
  digitalWrite(led, LOW);
  delay(800);


  Sensor1 = LASER_Get(1, SensorRange); //get all sensors
  Sensor2 = LASER_Get(2, SensorRange);
  Sensor3 = LASER_Get(3, SensorRange);
  if(Sensor1==1) {
    Sensor = 1;
  }
    
  else {
    if(Sensor2==1) {
      Sensor = 1;
    }
    
    else {
      if(Sensor3==1) {
       Sensor = 1;
      }
      
      else {
        Sensor = 0;
      }
    }
  }
  
  while(Sensor==0) { //rotate left until any sensor triggers
    MOTORS_Go(-25, 25);
    Sensor1 = LASER_Get(1, SensorRange);
    Sensor2 = LASER_Get(2, SensorRange);
    Sensor3 = LASER_Get(3, SensorRange);
    
    if(Sensor1==1) {
      Sensor = 1;
    }
    
    else {
      if(Sensor2==1) {
        Sensor = 1;
      }
      
      else {
        if(Sensor3==1) {
         Sensor = 1;
        }
        
        else {
          Sensor = 0;
        }
      }
    }
  }
  
  
  MOTORS_Brake();
  
  digitalWrite(led, HIGH);  //led flash
  delay(500);
  digitalWrite(led, LOW);
  delay(500);
  
  Sensor1 = LASER_Get(1, SensorRange);
  Sensor2 = LASER_Get(2, SensorRange);
  Sensor3 = LASER_Get(3, SensorRange);

  
  if(Sensor1==1) {  //if right sensor
    while(Sensor3==0) { //rotate right until front sensor triggers
      MOTORS_Go(15, -15);
      Sensor1 = LASER_Get(1, SensorRange);
      Sensor3 = LASER_Get(3, SensorRange);
    }
  }
  
  if(Sensor2==1) {  //if left sensor
    while(Sensor3==0) { //rotate left until front sensor triggers
      MOTORS_Go(-15, 15);
      Sensor2 = LASER_Get(2, SensorRange);
      Sensor3 = LASER_Get(3, SensorRange);
    }
  }

  //sumec is now rotated towards the target

  digitalWrite(led, HIGH);  //led flash
  delay(50);
  digitalWrite(led, LOW);
  delay(50);
  digitalWrite(led, HIGH);  //led flash
  delay(50);
  digitalWrite(led, LOW);
  delay(50);
  digitalWrite(led, HIGH);  //led flash
  delay(50);
  digitalWrite(led, LOW);
  delay(50);
  MOTORS_Brake();
  
  ButtonDown = digitalRead(Button);
  while(ButtonDown==0) {  //the main loop, stop by holding the debug button
    ButtonDown = digitalRead(Button);
    digitalWrite(led, HIGH);  //led flash
    delay(200);
    digitalWrite(led, LOW);
    delay(200);
    digitalWrite(led, HIGH);  //led flash
    delay(200);
    digitalWrite(led, LOW);
    delay(200);
    
    MOTORS_Brake();
    Sensor1 = LASER_Get(1, SensorRange);
    Sensor2 = LASER_Get(2, SensorRange);
    Sensor3 = LASER_Get(3, SensorRange);
    if(Sensor1==1) {
      Sensor=1;
      }
      
    else {
      if(Sensor2==1) {
      Sensor=1;
      }
      
      else {
        if(Sensor3==1) {
          Sensor=1;
        }
        
        else {
          Sensor=0;
        }
      }
    }
            
    if(Sensor3==1) {  //target is still centred
      MOTORS_Go(50, 50);
    }

    else {  //ok so target is not centred in front of sumec
      if(Sensor1==1) {  //so the target is a little to the right
        while(Sensor3==0) {
          MOTORS_Go(15, -25);
          Sensor3 = LASER_Get(3, SensorRange);
        }
        delay(600);
      }
      
      else {  //then the target must be a little to the left
        if(Sensor2==1) {
          while(Sensor3==0) {
            MOTORS_Go(-25, 15);
            Sensor3 = LASER_Get(3, SensorRange);
          }
          delay(600);
        }

        else {  //target is lost
          while(Sensor==0) { //rotate left until any sensor triggers
            MOTORS_Go(-25, 25);
            Sensor1 = LASER_Get(1, SensorRange);
            Sensor2 = LASER_Get(2, SensorRange);
            Sensor3 = LASER_Get(3, SensorRange);
            if(Sensor1==1) {
              Sensor=1;
              }
              
            else {
              if(Sensor2==1) {
              Sensor=1;
              }
              
              else {
                if(Sensor3==1) {
                  Sensor=1;
                }
                
                else {
                  Sensor=0;
                }
              }
            }
          }
        }
      }
    }
  }
}
