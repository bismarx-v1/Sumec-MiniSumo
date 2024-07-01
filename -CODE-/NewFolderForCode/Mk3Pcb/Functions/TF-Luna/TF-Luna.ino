#include "TF-Luna.h"	// This also includes Wire.h

TF_Luna TF_Luna_Obj(18,	17);	// Sda, Scl

uint8_t OldAddress = 0x10;	// Luna's address - specific for set address
uint8_t Address = 0x11;	// Luna's address
uint8_t NewAddress = 0x11;	// Luna's new address - for "SetAddressFunc"

void SetAddressFunc(uint8_t SAF_Addr, uint8_t SAF_NewAddr) {
	Serial.printf("Error: %i\n", TF_Luna_Obj.writeAddress(SAF_Addr, SAF_NewAddr));
	Serial.printf("Error: %i\n", TF_Luna_Obj.save(SAF_Addr));
	Serial.printf("Error: %i\n", TF_Luna_Obj.reboot(SAF_Addr));
	delay(2000);
	Serial.printf("Done\n");
}

void FactoryResetFunc(uint8_t FRF_Addr) {
	Serial.printf("Error: %i\n", TF_Luna_Obj.factoryReset(FRF_Addr));
	delay(2000);
	Serial.printf("Done\n");
}

void setup() {
	Serial.begin(115200);
	TF_Luna_Obj.DebugMode = 1;	// Enables serial prints from this lib
	
	/*
	SetAddressFunc(OldAddress, NewAddress);	// Change the i2c address of the specific tf-luna
	*/
	
	/*
	FactoryResetFunc(Address);	// Factory reset a tf-luna by i2c address
	*/
	
	/*
	uint16_t* Data;
	Data = new uint16_t[5];
	TF_Luna_Obj.readData(Address, Data);	// Get all data from a specific tf-luna; output is: {[Distance], [Amplitude], [Temp], [Ticks], [Error]}
	*/
	
	/*
	uint16_t Distance;
	Distance = TF_Luna_Obj.readOnlyDist(Address);
	*/
	
}

void loop() {
	
}