#include "DRV8874PWPR.h"
#include "QRE1113.h"







class Hbridge_MANAGER
{
  public:
    Hbridge_MANAGER();
    void manageHbridge();
    void addHbridge(DRV8874PWPR *newHbridge);
 
  
  private:
    DRV8874PWPR *hbridgeArray[5];  
    int numberOfObjects = 0; 
    int numberOfObject = 0; 
    int numberOfPriorytyObjects = 0;

};

Hbridge_MANAGER::Hbridge_MANAGER()
{

}


void Hbridge_MANAGER::addHbridge(DRV8874PWPR *newHbridge)
{

  hbridgeArray[numberOfObject] = newHbridge;
  numberOfObject++;

}


void Hbridge_MANAGER::manageHbridge()
{
  int max_prioryty = hbridgeArray[0]->prioryty_left; 

  for(int i=1; i<numberOfObject; i++)
  {
    if(hbridgeArray[i]->prioryty_left > max_prioryty)
    {
      numberOfPriorytyObjects = i;
    }
  }

  hbridgeArray[numberOfPriorytyObjects]->acceptLeft = 1;

  for(int i=1; i<numberOfObject; i++)
  {
    if(numberOfPriorytyObjects != i)
    {
      hbridgeArray[i]->acceptLeft = 0;
    }
  }

}






DRV8874PWPR MotorA(5000, 8);
DRV8874PWPR MotorB(5000, 8);

Hbridge_MANAGER Hmanager;



void setup() 
{
	MotorA.LedcChannelLeft = 0;	// Add a ledc channel 
	MotorB.LedcChannelRight = 1;
  Serial.begin(9600);
}


void loop() 
{

  MotorA.left(255, 2);
  MotorA.right(255, 3);
  Hmanager.addHbridge(&MotorA);
  
  MotorB.left(100, 3);
  MotorB.right(100, 2);
  Hmanager.addHbridge(&MotorB);

  Hmanager.manageHbridge();

}
