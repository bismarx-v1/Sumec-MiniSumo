#include <Wire.h>        // Instantiate the Wire library
#include <TFLI2C.h>      // TFLuna-I2C Library v.0.1.1

TFLI2C tflI2C;	//0x10; 0x1E; 0x1A


int16_t  tfAddr = 0x1A;


void setup() {
    Serial.begin(115200);  // Initalize serial port
    Wire.begin(18,17,400000);           // Initalize Wire library
	delay(1000);
	
	
	tflI2C.printStatus();
	delay(1000);
	Serial.println(tflI2C.Hard_Reset(tfAddr));
	delay(1000);
	
	
}

void loop() {
	tflI2C.printStatus();
	Serial.println("\n============");
	delay(1000);
}