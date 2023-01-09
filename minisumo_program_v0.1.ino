#include <VL53L0X.h>

#define M1 2
#define M2 3

int cara;
VL53L0X sensor;

void setup() {

  sensor.setTimeout(10);
  
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);

}
// "zjistovani vzdalenosti"
 int distance = sensor.readRangeContinuousMillimeters();

void pohyb(){
  while(cara == 0){
    digitalWrite(M1, HIGH);
    digitalWrite(M2, HIGH);
  }
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
}

void loop() {
  

}
