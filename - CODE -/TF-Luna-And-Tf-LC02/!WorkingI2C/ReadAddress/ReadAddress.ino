#include <Wire.h>        // Instantiate the Wire library
#include <TFLI2C.h>      // TFLuna-I2C Library v.0.1.1

TFLI2C tflI2C;

int16_t tfAddr1 = 0x11;
int16_t tfAddr2 = 0x12;
int16_t tfAddr3 = 0x13;
int16_t tfDist;


void setup() {
	pinMode(40, OUTPUT);
	pinMode(41, OUTPUT);
	pinMode(42, OUTPUT);
	digitalWrite(40, LOW);
	digitalWrite(41, LOW);
	digitalWrite(42, LOW);
	
    Serial.begin(9600);
    Wire.begin(18,17,400000);
	delay(1000);
	
	tflI2C.printStatus();
	delay(1000);
	
}

void loop() {
	tflI2C.getData( tfDist, 0x10);
	Serial.println(tfDist);
	tfDist = 0;
	delay(100);
	
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