/*
* I2C Scanner
* baud rate = 115200
* 
* This code:
* 	- scans I2C addresses from 0 to 127
* 	- prints used addresses
*/

#include <Wire.h>

const int Sda = 18;
const int Scl = 17;
const int ClkSpd = 40000;

void setup() {
	Serial.begin(115200);
	Wire.begin(Sda, Scl, ClkSpd);
	
}

void loop() {
	Serial.printf("Loop start");
	for(uint8_t Addr = 0; Addr <= 127; Addr++ ) {
		uint8_t Err;
		Wire.beginTransmission(Addr);
		Err = Wire.endTransmission();
		
		if(Err==0) {
			Serial.printf("%#03x\tSuccess\n", Addr);
		}
	}
	
	Serial.printf("Loop end");
	delay(1000);
}