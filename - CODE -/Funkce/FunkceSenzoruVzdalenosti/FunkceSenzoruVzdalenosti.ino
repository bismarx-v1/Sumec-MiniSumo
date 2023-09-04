#include "laser.h"


void setup() {
	Serial.begin (115200);
	LASER_Setup();
}


void loop() {
	Serial.print("Right: ");
	Serial.println(LASER_Get(1, 300, 0));	//pravy senzor (1) z pohledu sumce
	Serial.print("Front: ");
	Serial.println(LASER_Get(3, 300, 0));	//prostredni senzor (3) z pohledu sumce
	Serial.print("Left: ");
	Serial.println(LASER_Get(2, 300, 0));	//levy senzor (2) z pohledu sumce
	Serial.println("-----------------");
	Serial.print("Right: ");
	Serial.println(LASER_Get(1, 0, 1));	//pravy senzor (1) z pohledu sumce
	Serial.print("Front: ");
	Serial.println(LASER_Get(3, 0, 1));	//prostredni senzor (3) z pohledu sumce
	Serial.print("Left: ");
	Serial.println(LASER_Get(2, 0, 1));	//levy senzor (2) z pohledu sumce
	Serial.println("=======================");
	delay(500);
}
