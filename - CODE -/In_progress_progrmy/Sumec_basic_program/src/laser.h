#include <Wire.h>
#include <VL53L0X.h>



VL53L0X sensorLeft;
VL53L0X sensorRight;
VL53L0X sensorFront;

int LASER_DistLeft;
int LASER_DistRight;
int LASER_DistFront;





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
