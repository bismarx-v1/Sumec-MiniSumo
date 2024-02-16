#include "motorsEsp32S3.h"

const int LEDPin = 15;
TaskHandle_t Task1;
int LEDBlink = 0;
int LedBlinkState = 0;

void CodeForTask1(void * parameter) {	/*Code for core 0*/
	Serial.print("Core ["); Serial.print(xPortGetCoreID()); Serial.println("] started");	//print this core
	
	for(;;) {	//void loop()
		switch(LEDBlink) {
			case 0:
				if(LedBlinkState != 0) {
					LedBlinkState = 0;
					digitalWrite(LEDPin, 0);
					break;
				}
				
				else {
					break;
				}
			
			case 1:
				if(LedBlinkState != 1) {
					LedBlinkState = 1;
					digitalWrite(LEDPin, 1);
					delay(200);
					digitalWrite(LEDPin, 0);
					delay(400);
					break;
				}
				
				else {
					break;
				}
			
			case 2:
				if(LedBlinkState != 2) {
					LedBlinkState = 2;
					digitalWrite(LEDPin, 1);
					delay(500);
					digitalWrite(LEDPin, 0);
					delay(200);
					digitalWrite(LEDPin, 1);
					delay(200);
					digitalWrite(LEDPin, 0);
					delay(200);
					break;
				}
				
				else {
					break;
				}
		}
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
		
	LEDBlink = 1;
	
	
	MOTORS_Go(255/2, 255/2);
}


//normalni void loop()
void loop() {
}
