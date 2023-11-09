#include <Wire.h>

void setup() {
	Wire.begin(11,10,400000);
	Serial.begin(115200);
	while (!Serial) {delay(10);}
	delay(5000);
	Serial.print("START");
	Wire.beginTransmission(0x10); //Address of sensor. default is 0x10
	Wire.write(0x5A);	//head
	Wire.write(0x05);	//len
	Wire.write(0x0B);	//id
	Wire.write(0x1E); 	//payload		//Address goes here. hex number (0x##) min 0x08 max 0x77
	Wire.write(0x00);	//checksum
	Wire.endTransmission(0);
	delay(100);
	// Save the address
	Wire.beginTransmission(0x10);
	Wire.write(0x5A);
	Wire.write(0x04);
	Wire.write(0x11);
	Wire.write(0x6F);
	Wire.endTransmission(0);
	Serial.print("END");

}

void loop() {
}