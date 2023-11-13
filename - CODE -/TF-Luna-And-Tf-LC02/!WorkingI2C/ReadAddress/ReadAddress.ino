#include <Wire.h>        // Instantiate the Wire library
#include <TFLI2C.h>      // TFLuna-I2C Library v.0.1.1

TFLI2C tflI2C;

int16_t tfAddr1 = 0x1E;
int16_t tfAddr2 = 0x1A;
int16_t tfAddr3 = 0x10;
int16_t tfDist;


void setup() {
    Serial.begin( 115200);
    Wire.begin(11,10,400000);
	delay(1000);
	
	tflI2C.printStatus();
	delay(1000);
	
}

void loop() {
	tflI2C.getData( tfDist, tfAddr1);
	Serial.println(tfDist);
	tfDist = 0;
	delay(100);
	
	tflI2C.getData( tfDist, tfAddr2);
	Serial.println(tfDist);
	tfDist = 0;
	delay(100);
	
	
	tflI2C.getData( tfDist, tfAddr3);
	Serial.println(tfDist);
	tfDist = 0;
	delay(100);
	
	
	tflI2C.printStatus();
	Serial.println("\n============");
	delay(100);
}