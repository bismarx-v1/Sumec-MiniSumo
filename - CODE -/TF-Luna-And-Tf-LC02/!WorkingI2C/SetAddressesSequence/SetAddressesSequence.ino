#include <Wire.h>        // Instantiate the Wire library
#include <TFLI2C.h>      // TFLuna-I2C Library v.0.1.1

TFLI2C tflI2C;

int16_t  tfAddr = 0x10;			//defaultní adresa
int16_t  tfNewAddress1 = 0x11;	//Range = <0x08; 0x77>
int16_t  tfNewAddress2 = 0x12;
int16_t  tfNewAddress3 = 0x13;
int TfL_Succ = 0;


void setup() {
	pinMode(40, OUTPUT);
	pinMode(41, OUTPUT);
	pinMode(42, OUTPUT);
	digitalWrite(40, LOW);
	digitalWrite(41, LOW);
	digitalWrite(42, LOW);
	
	pinMode(15, OUTPUT);
	
    Serial.begin(9600);  // Initalize serial port
    Wire.begin(18,17,400000);           // Initalize Wire library
	delay(1000);	//serial lib is slow
	
	digitalWrite(15, HIGH);
	delay(100);
	digitalWrite(15, LOW);
	delay(100);
	
	while(TfL_Succ==0) {
		TfL_Succ = tflI2C.Set_I2C_Addr(tfNewAddress1, tfAddr);	//only left sensor should be connected
		Serial.println(TfL_Succ);
		delay(1000);
	}
	Serial.println("0x11?");
	TfL_Succ = 0;
	
	digitalWrite(15, HIGH);
	delay(100);
	digitalWrite(15, LOW);
	delay(100);
	digitalWrite(15, HIGH);
	delay(100);
	digitalWrite(15, LOW);
	delay(100);
	
	while(TfL_Succ==0) {
		TfL_Succ = tflI2C.Set_I2C_Addr(tfNewAddress2, tfAddr);	//only left and mid sensors should be connected
		Serial.println(TfL_Succ);
		delay(1000);
	}
	Serial.println("0x12?");
	TfL_Succ = 0;
	
	digitalWrite(15, HIGH);
	delay(100);
	digitalWrite(15, LOW);
	delay(100);
	digitalWrite(15, HIGH);
	delay(100);
	digitalWrite(15, LOW);
	delay(100);
	
	while(TfL_Succ==0) {
		TfL_Succ = tflI2C.Set_I2C_Addr(tfNewAddress3, tfAddr);	//all sensors should be connected
		Serial.println(TfL_Succ);
		delay(1000);
	}
	Serial.println("0x13?");
	TfL_Succ = 0;
	
	digitalWrite(15, HIGH);
	delay(100);
	digitalWrite(15, LOW);
	delay(100);
	digitalWrite(15, HIGH);
	delay(100);
	digitalWrite(15, LOW);
	delay(100);
	digitalWrite(15, HIGH);
	delay(100);
	digitalWrite(15, LOW);
	delay(100);
	
	
	/*
	delay(5000);
	Serial.println(tflI2C.Set_I2C_Addr(tfNewAddress1, tfAddr));	//only left sensor should be connected
	delay(1000);
	Serial.println(tflI2C.Save_Settings(tfAddr));
	delay(1000);
	Serial.println(tflI2C.Soft_Reset(tfAddr));
	
	Serial.print("Add 2nd sensor");	//only left and mid sensors should be connected
	delay(5000);
	Serial.println(tflI2C.Set_I2C_Addr(tfNewAddress2, tfAddr));
	delay(1000);
	Serial.println(tflI2C.Save_Settings(tfAddr));
	delay(1000);
	Serial.println(tflI2C.Soft_Reset(tfAddr));
	
	Serial.print("Add 3rd sensor");	//all sensors should be connected
	delay(5000);
	Serial.println(tflI2C.Set_I2C_Addr(tfNewAddress3, tfAddr));
	delay(1000);
	Serial.println(tflI2C.Save_Settings(tfAddr));
	delay(1000);
	Serial.println(tflI2C.Soft_Reset(tfAddr));
	
	Serial.print("Add 1sr sensor");
	delay(5000);
	Serial.println(tflI2C.Set_I2C_Addr(tfNewAddress1, tfAddr));
	delay(1000);
	Serial.println(tflI2C.Save_Settings(tfAddr));
	delay(1000);
	Serial.println(tflI2C.Soft_Reset(tfAddr));*/
	
	delay(1000);
	
}

void loop() {		//zkopírovaný funkční i2c scanner
	byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error==4) 
    {
      Serial.print("Unknown error at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(5000);
}