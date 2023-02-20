
#include "Adafruit_VL53L0X.h"

#define m1 3
#define m2 4

#define intenzita1 5
#define intenzita2 6
#define intenzita3 7
#define intenzita4 8

#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31
#define LOX3_ADDRESS 0x32

#define SHT_LOX1 6
#define SHT_LOX2 7
#define SHT_LOX3 8

#define prumer_ryngu 2000

Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();

VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;
VL53L0X_RangingMeasurementData_t measure3;

void setID() {
  
  digitalWrite(SHT_LOX1, LOW);    
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);
  delay(10);
  
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, HIGH);
  digitalWrite(SHT_LOX3, HIGH);
  delay(10);

  // activating LOX1 and reseting LOX2
  digitalWrite(SHT_LOX1, HIGH);
  digitalWrite(SHT_LOX2, LOW);
  digitalWrite(SHT_LOX3, LOW);

  // initing LOX1
  if(!lox1.begin(LOX1_ADDRESS)) {
    Serial.println(F("Failed to boot first VL53L0X"));
    while(1);
  }
  delay(10);

  // activating LOX2
  digitalWrite(SHT_LOX2, HIGH);
  delay(10);

  //initing LOX2
  if(!lox2.begin(LOX2_ADDRESS)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    while(1);
  }
  delay(10);

  digitalWrite(SHT_LOX3, HIGH);
  delay(10);

  if(!lox3.begin(LOX3_ADDRESS)) {
    Serial.println(F("Failed to boot third VL53L0X"));
    while(1);
  }  
}


void setup() {
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);

  pinMode(intenzita1, INPUT);
  pinMode(intenzita2, INPUT);
  pinMode(intenzita3, INPUT);
  pinMode(intenzita4, INPUT);

  Serial.begin(9600);
  setID();
}

int detekce_cary(){
  int vysledek;
  vysledek = digitalRead(intenzita1)+digitalRead(intenzita2)+digitalRead(intenzita3)+digitalRead(intenzita4);
  return(vysledek);
}
int detekce_protivnika(){
  int vysledek_1;
  int vysledek_2;
  int vysledek_3;
  
  if(measure1.RangeMilliMeter <= prumer_ryngu){
     vysledek_1 = 1;
  }
  if(measure2.RangeMilliMeter <= prumer_ryngu){
     vysledek_2 = 2;
  } 
  if(measure3.RangeMilliMeter <= prumer_ryngu){
     vysledek_3 = 3;
  }
  return(vysledek_1+vysledek_2+vysledek_3);
}

void loop() {
  int i = 0;
  
  while(detekce_cary()==0){
    digitalWrite(m1, HIGH);
    digitalWrite(m2, HIGH);
  }
  
  
  while(detekce_cary()>0||i>=1000){
    digitalWrite(m1, HIGH); 
    digitalWrite(m2, LOW);
    if(detekce_cary()>0){
      delay(1);
      i=1;
    }
  }
}
