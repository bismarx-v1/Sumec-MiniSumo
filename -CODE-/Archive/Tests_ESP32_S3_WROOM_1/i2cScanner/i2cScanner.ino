 // --------------------------------------
// i2c_scanner
//
// Version 1
//		This program (or code that looks like it)
//		can be found in many places.
//		For example on the Arduino.cc forum.
//		The original author is not know.
// Version 2, Juni 2012, Using Arduino 1.0.1
//		 Adapted to be as simple as possible by Arduino.cc user Krodal
// Version 3, Feb 26	2013
//		V3 by louarnold
// Version 4, March 3, 2013, Using Arduino 1.0.3
//		by Arduino.cc user Krodal.
//		Changes by louarnold removed.
//		Scanning addresses changed from 0...127 to 1...119,
//		according to the i2c scanner by Nick Gammon
//		https://www.gammon.com.au/forum/?id=10896
// Version 5, March 28, 2013
//		As version 4, but address scans now to 127.
//		A sensor seems to use address 120.
// Version 6, November 27, 2015.
//		Added waiting for the Leonardo serial communication.
// 
//
// This sketch tests the standard 7-bit addresses
// Devices with higher bit address might not be seen properly.
//

#include <Wire.h>

int EndData[5];

void setup()
	{
		Wire.begin();

		Serial.begin(9600);
		while (!Serial);						 // Leonardo: wait for serial monitor
		delay(3000);
		Serial.println("START");
		delay(100);
		Serial.println("START2");
		delay(100);
		Serial.println("\nI2C Scanner");
		delay(100);
	}


void loop()
{
	byte error, address;
	int nDevices;

	Serial.println("Scanning..."); delay(100);
	Serial.println("Scanning...2"); delay(100);

	nDevices = 0;
	
	EndData[0]=0;
	EndData[1]=0;
	EndData[2]=0;
	EndData[3]=0;
	EndData[4]=0;
	EndData[5]=0;

	for(address = 0; address <= 127; address++ ) 
	{
		// The i2c_scanner uses the return value of
		// the Write.endTransmisstion to see if
		// a device did acknowledge to the address.
		Wire.beginTransmission(address);
		error = Wire.endTransmission();
	switch(error) {
		case 0:
			Serial.print(address); delay(100);
			Serial.println("\tSuccess"); delay(100);
			EndData[0]=EndData[0]+1;
			break;
		case 1:
			Serial.print(address); delay(100);
			Serial.println("\t1"); delay(100);
			EndData[1]=EndData[1]+1;
			break;
		case 2:
			Serial.print(address); delay(100);
			Serial.println("\t2="); delay(100);
			EndData[2]=EndData[2]+1;
			break;
		case 3:
			Serial.print(address); delay(100);
			Serial.println("\t3=="); delay(100);
			EndData[3]=EndData[3]+1;
			break;
		case 4:
			Serial.print(address); delay(100);
			Serial.println("\t4==="); delay(100);
			EndData[4]=EndData[4]+1;
			break;
		case 5:
			Serial.print(address); delay(100);
			Serial.println("\t5===="); delay(100);
			EndData[5]=EndData[5]+1;
			break;
		default:
			Serial.print(address); delay(100);
			Serial.println("\tdef"); delay(100);
			break;
		
		
		}

		if (error == 0)
		{
			Serial.print("I2C device found at address 0x"); delay(100);
			if (address<16) 
				Serial.print("0"); delay(100);
			Serial.print(address,HEX); delay(100);
			Serial.println("	!"); delay(100);

			nDevices++;
		}
		else if (error==4) 
		{
			Serial.print("Unknown error at address 0x"); delay(100);
			if (address<16) 
				Serial.print("0"); delay(100);
			Serial.println(address,HEX); delay(100);
		}		
	}
	if (nDevices == 0) {
		Serial.println("No I2C devices found\n"); delay(100);
	}
	else {
		Serial.println("done\n"); delay(100);
	}

	Serial.println("========================="); delay(100);
	Serial.print("Success\t> "); delay(100);
	Serial.println(EndData[0]); delay(100);
	Serial.print("Data too long\t> "); delay(100);
	Serial.println(EndData[1]); delay(100);
	Serial.print("NACK (address)\t> "); delay(100);
	Serial.println(EndData[2]); delay(100);
	Serial.print("NACK (data)\t> "); delay(100);
	Serial.println(EndData[3]); delay(100);
	Serial.print("other error\t> "); delay(100);
	Serial.println(EndData[4]); delay(100);
	Serial.print("Timeout\t> "); delay(100);
	Serial.println(EndData[5]); delay(100);
	Serial.println("========================="); delay(100);

	delay(5000);					 // wait 5 seconds for next scan
}