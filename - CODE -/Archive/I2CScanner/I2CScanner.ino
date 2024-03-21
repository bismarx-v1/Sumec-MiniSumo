//I2C Scanner
#include <Wire.h>

const int Sda = 18;
const int Scl = 17;//*/		//Esp32 and mk3
/*const int Sda = 18;
const int Scl = 17;//*/		//Esp32S3

void setup() {
	Serial.begin(115200);
	delay(2000);
	Wire.begin(Sda, Scl, 400000);
	delay(100);
	Serial.println("I2C Scanner Started ^w^");
}


void loop() {
	byte error, address;
	int nDevices;

	Serial.print("STARTed @ ");
	Serial.println(millis());

	nDevices = 0;
	for(address = 0; address < 127; address++ ) {
		Wire.beginTransmission(address);
		error = Wire.endTransmission();
		
		switch(error) {
			case 0:
				nDevices++;
				Serial.print(error);
				Serial.print("\tSuccess @ 0x");
				if (address<16) {Serial.print("0");}
				Serial.println(address,HEX);
				break;
			
			case 1:
				Serial.print(error);
				Serial.print("\tTooLong @ 0x");
				if (address<16) {Serial.print("0");}
				Serial.println(address,HEX);
				break;
				
			case 2:
				Serial.print(error);
				Serial.print("\tAddressErr @ 0x");
				if (address<16) {Serial.print("0");}
				Serial.println(address,HEX);
				break;
				
			case 3:
				Serial.print(error);
				Serial.print("\tDataErr @ 0x");
				if (address<16) {Serial.print("0");}
				Serial.println(address,HEX);
				break;
				
			case 4:
				Serial.print(error);
				Serial.print("\tOtherErr @ 0x");
				if (address<16) {Serial.print("0");}
				Serial.println(address,HEX);
				break;
				
			case 5:
				Serial.print(error);
				Serial.print("\tTimeout @ 0x");
				if (address<16) {Serial.print("0");}
				Serial.println(address,HEX);
				break;
		}		
	}
	
	Serial.print("\n");
	if(nDevices == 0) {
		Serial.println("No I2C devices found\n");
	} else {
		Serial.println("done\n");
	}
	
	Serial.print("ENDed @ ");
	Serial.println(millis());
	
	delay(100);
}