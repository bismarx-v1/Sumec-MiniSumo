#include <Wire.h>

const int clkSpeed = 40000;					//I^2C speed

const int AddrFrom = 0x10;				//default luna address
const int regAddrAddr = 0x22;				//register of new address
const int regAddrSave = 0x20;				//register of save
const int regDataCommit = 0x01;				//data for commit
const int regAddrReboot = 0x21;				//register of
const int regDataReboot = 0x02;				//data for reboot

//...////////////////////
//..//    SETTINGS    //
//.////////////////////
const int AddrTo = 0x13;				//new address somewhere from 0x08 to 0x77
const int I2cSda = 18;						//sda pin
const int I2cScl = 17;						//sdc pin

void setup() {
	Serial.begin(115200);
	delay(5000);
	Serial.println("STARTING");
	Wire.begin(I2cSda, I2cScl, clkSpeed);
	delay(2000);
	
	Wire.beginTransmission(AddrFrom);	//set address
	Wire.write(regAddrAddr);
	Wire.write(AddrTo);
	Wire.endTransmission();
	
	delay(100);
	
	Wire.beginTransmission(AddrTo);	//save
	Wire.write(regAddrSave);
	Wire.write(regDataCommit);
	Wire.endTransmission();
	
	delay(100);
	
	Wire.beginTransmission(AddrTo);	//reboot
	Wire.write(regAddrReboot);
	Wire.write(regDataReboot);
	Wire.endTransmission();
	
	Serial.println("done, pls wait 2s");
	delay(2000);
	Serial.println("done");
}

void loop() {
	digitalWrite(2, 1);	//blink led
	delay(500);
	digitalWrite(2, 0);
	delay(500);
}