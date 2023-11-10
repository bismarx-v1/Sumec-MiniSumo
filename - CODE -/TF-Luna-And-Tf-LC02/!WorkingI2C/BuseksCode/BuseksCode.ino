#include <Wire.h>

void setup() {
	pinMode(40, OUTPUT);
	pinMode(41, OUTPUT);
	pinMode(42, OUTPUT);
	digitalWrite(40, LOW);
	digitalWrite(41, LOW);
	digitalWrite(42, LOW);

Wire.begin(18,17,400000);
Wire.beginTransmission(0x10);
Wire.write(0x5A);
Wire.write(0x05);
Wire.write(0x0B);
Wire.write(0x1E); // I2C address
Wire.write(0x00);
Wire.endTransmission(0);
delay(100);
// Save the address
Wire.beginTransmission(0x10);
Wire.write(0x5A);
Wire.write(0x04);
Wire.write(0x11);
Wire.write(0x6F);	//was 0x6F
Wire.endTransmission(0);

}

void loop() {
}