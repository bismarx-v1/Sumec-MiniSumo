#include "motorsEsp32S3.h"

const int LEDPin = 15;
TaskHandle_t Task1;

void CodeForTask1(void * parameter) {	/*Code for core 0*/
	Serial.print("Core ["); Serial.print(xPortGetCoreID()); Serial.println("] started");	//print this core
	
	for(;;) {	//void loop()
		digitalWrite(LEDPin, 1);
		delay(200);
		digitalWrite(LEDPin, 0);
		delay(400);
	}
}



//normalni void setup() s funkci MOTORS_Setup()
void setup() {
  MOTORS_Setup();
  pinMode(LEDPin, OUTPUT);
  
  
  xTaskCreatePinnedToCore(	/*This command should be at the end of void setup()*/
		CodeForTask1, 	/*Task Function*/
		"Task_1", 		/*Name*/
		3500, 			/*Stack size*/
		NULL, 			/*Parameter*/
		0, 				/*Priority*/
		&Task1, 		/*Task handle*/
		0);				/*Core*/
}


//normalni void loop()
void loop() {
  /*MOTORS_Go(255/2, -255/2);
  delay(2000);
  
  MOTORS_Go(255/2, 255/2);
  delay(3000);
  
  MOTORS_Go(0, 0);
  delay(2000);*/
}
