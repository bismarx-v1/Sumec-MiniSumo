//"knihovny"
#include <BH1750.h>
#include <VL53L0X.h>
#include "pole_vzdalenosti.h"
//"motory dopredu"
//"piny pouze prozatimni"
#define M1 2
#define M2 3
//"motory dozadu"
#define M1p 4
#define M2p 5

float svetlo;
float vzdalenost;

//"vytvoreni senzoru"
VL53L0X sensorvz;
BH1750 intenzita_svetla;

void setup() {
  
  //"nastaveni senzoru"
  sensorvz.setTimeout(1);
  intenzita_svetla.begin();
  
  //"nastaveni vsech motoru na vystup"
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(M1p, OUTPUT);
  pinMode(M2p, OUTPUT);

}
void zjistovani_svetla(){
  svetlo = intenzita_svetla.readLightLevel();
}
  
//"jed dokud neuvidis tmu"
void pohyb(){
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  
  while(svetlo>500){
    zjistovani_svetla(); 
  }
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
}

void loop() {
  pohyb();

  digitalWrite(M1p, HIGH);
  digitalWrite(M2, HIGH);
  while(vzdalenost > 770){
    vzdalenost = sensorvz.readRangeContinuousMillimeters();
  }
  zjistovani_svetla(); 
  if(svetlo < 500){
    
  }
  else{
    int i=0;
    while(vzdalenost < 770){
      pole_vzdalenosti [i] = vzdalenost;
      i++;
    }
  }





  
}
