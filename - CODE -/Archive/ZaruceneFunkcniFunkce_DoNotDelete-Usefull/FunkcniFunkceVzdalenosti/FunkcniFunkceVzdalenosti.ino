#include "laser.h"

void setup() {
	Serial.begin(9600);
	LASER_Setup();
	while (!Serial) {
		delay(10); // wait for serial port to connect. Needed for native USB
	}
}


void loop() {	/*LASER_Get([Senzor], [Max Vzdalenost Pro Bool Mod], [Mod]);*/		/*LINE_Get([Sensor], [Max Range For Bool Mode], [Mode]);*/
	Serial.println("=======================");
	/*Bool mod*/	/*Bool mode*/
	/*Porovna vystup senzoru s max vzdalenosti*/	/*Compares sensor output with max range*/
	Serial.println(LASER_Get(1, 150, 0));	/*pravy,		bool mod*/		/*right,	bool mode*/
	Serial.println(LASER_Get(2, 150, 0));	/*levy,			bool mod*/		/*left,		bool mode*/
	Serial.println(LASER_Get(3, 150, 0));	/*prostredni,	bool mod*/		/*front,	bool mode*/
	
	
	/*Int mod*/		/*Int mode*/
	/*Na max vzdalenosti nezalezi, return je rovnou vzdalenost ze senzoru*/	/*Max range can be anything, just outputs range from sensor*/
	Serial.println(LASER_Get(1, 0, 1));		/*pravy,		int mod*/		/*right,	int mode*/
	Serial.println(LASER_Get(2, 0, 1));		/*levy,			int mod*/		/*left,		int mode*/
	Serial.println(LASER_Get(3, 0, 1));		/*prostredni,	int mod*/		/*front,	int mode*/
	
	Serial.println("=======================");
	delay(100);

}