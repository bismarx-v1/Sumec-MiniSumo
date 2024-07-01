#include <Arduino.h>
#include "Wire.h"
#include <VL53L0X.h>
#include "motors.h"
#include "line.h"
#include "laser.h"


//defines for demo
#define Button 13
#define led 14
int Sensor1 = 0;
int Sensor2 = 0;
int Sensor3 = 0;
int Sensor = 0;
int ButtonDown = 0;


int hodnota_cary = 1000;
int Range = 150;
int cas_zaznam = 0;

int stop = 1;

//void setup()
void setup() {
	MOTORS_Setup();
	LASER_Setup();
	pinMode(led, OUTPUT);
	Serial.begin(9600);

	while(LASER_Get(1, Range, 0) == 0 && LASER_Get(2, Range, 0) == 0 && LASER_Get(3, Range, 0) == 0){
		MOTORS_Go(-255/2*-1, 255/2*-1);

		//if(millis() - cas_zaznam == 2000){
			//cas_zaznam = millis();
			//Range = Range + 100;
		//}

		while(stop == 0){
			MOTORS_Go(0, 0);
		}
	}

}

int laser_number;
// promněná určující mód programu
int Global_ModeSelectvar;
// určuje zdali je barva spíš bílá nebo černá
//void loop
void loop() {

	switch(Global_ModeSelectvar){

	case 0:
		if(LINE_Get(1, hodnota_cary, 0) == 0 && LINE_Get(2, hodnota_cary, 0) == 0){
			
			//třídící proměná
			laser_number = 0;
			
			//třídění laserů pomocí proměné

			Serial.println(LASER_Get(1, Range, 0));

			if(cas_zaznam == 0){
				if(LASER_Get(3, Range, 0) == 1 ){	 // přední laser
					laser_number = laser_number + 1;
					//Serial.println(laser_number);
					digitalWrite(led, HIGH);
				}


				if(LASER_Get(2, Range, 0) == 1 ){	 // levý laser
					laser_number = laser_number + 3;
					//Serial.println(laser_number);
					digitalWrite(led, HIGH);
				}

				
				if(LASER_Get(1, Range, 0) == 1 ){	 // pravý laser
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
				case 1:
					MOTORS_Go(255*-1, 255*-1);
					delay(30); 
				break;

				case 3:
					MOTORS_Go(-255/2*-1, 255/2*-1);
				break;

				case 5:
					MOTORS_Go(255/2*-1, -255/2*-1);
				break;

				case 4:
					MOTORS_Go(255*-1, 100*-1);
				break;

				case 6:
					MOTORS_Go(100*-1, 255*-1);
				break;

				case 9:
					MOTORS_Go(255*-1, 255*-1);
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
		break;
	}

}