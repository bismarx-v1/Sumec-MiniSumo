#include "TF-Luna.h"	// This also includes Wire.h

TF_Luna TF_Luna_Obj(18,	17);	// Sda, Scl

uint8_t Address = 0x11;	// Luna's address

void setup() {
	Serial.begin(115200);
	TF_Luna_Obj.DebugMode = 1;	// Enables serial prints from this lib
	
	uint8_t NewAddress = 0x13
	Serial.printf("Error: %i\n", TF_Luna_Obj.writeAddress(Address, NewAddress));
	
	//Serial.printf("Error: %i\n", TF_Luna_Obj.factoryReset(Address));
	
	Serial.printf("Error: %i\n", TF_Luna_Obj.save(Address));
	Serial.printf("Error: %i\n", TF_Luna_Obj.reboot(Address));
	delay(2000);
	Serial.printf("Done\n");
}

void loop() {
	
}