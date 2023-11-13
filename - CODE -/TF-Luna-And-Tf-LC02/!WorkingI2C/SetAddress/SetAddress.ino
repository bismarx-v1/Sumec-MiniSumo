#include <Wire.h>        // Instantiate the Wire library
#include <TFLI2C.h>      // TFLuna-I2C Library v.0.1.1

TFLI2C tflI2C;

int16_t  tfAddr = 0x10;
int16_t  tfNewAddress = 0x11;


void setup() {
	pinMode(40, OUTPUT);
	pinMode(41, OUTPUT);
	pinMode(42, OUTPUT);
	digitalWrite(40, LOW);
	digitalWrite(41, LOW);
	digitalWrite(42, LOW);
	
	digitalWrite(41, HIGH);
	digitalWrite(42, HIGH);
	
    Serial.begin(115200);  // Initalize serial port
    Wire.begin(18,17,400000);           // Initalize Wire library
	delay(1000);
	
	
	
	tflI2C.printStatus();
	delay(1000);
	
	Serial.println(tflI2C.Set_I2C_Addr(tfNewAddress, tfAddr));
	tflI2C.printStatus();
	delay(10000);
	tflI2C.printStatus();
	Serial.println(tflI2C.Save_Settings(tfAddr));
	tflI2C.printStatus();
	delay(10000);
	tflI2C.printStatus();
	Serial.println(tflI2C.Soft_Reset(tfAddr));
	tflI2C.printStatus();
	delay(10000);
	
}

void loop() {
	tflI2C.printStatus();
	Serial.println("\n============");
	delay(1000);
}