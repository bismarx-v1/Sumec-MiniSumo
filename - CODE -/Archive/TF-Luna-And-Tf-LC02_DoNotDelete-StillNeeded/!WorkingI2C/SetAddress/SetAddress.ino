#include <Wire.h>        // Instantiate the Wire library
#include <TFLI2C.h>      // TFLuna-I2C Library v.0.1.1

TFLI2C tflI2C;

int16_t  tfAddr = 0x10;
int16_t  tfNewAddress = 0x12;


void setup() {
	pinMode(40, OUTPUT);
	pinMode(41, OUTPUT);
	pinMode(42, OUTPUT);
	digitalWrite(40, LOW);
	digitalWrite(41, LOW);
	digitalWrite(42, LOW);
	
    Serial.begin(9600);  // Initalize serial port
    Wire.begin(18,17,400000);           // Initalize Wire library
	delay(1000);
	
	
	
	tflI2C.printStatus();
	delay(1000);
	
	Serial.println(tflI2C.Set_I2C_Addr(tfNewAddress, tfAddr));
	tflI2C.printStatus();
	delay(1000);
	tflI2C.printStatus();
	Serial.println(tflI2C.Save_Settings(tfAddr));
	tflI2C.printStatus();
	delay(1000);
	tflI2C.printStatus();
	Serial.println(tflI2C.Soft_Reset(tfAddr));
	tflI2C.printStatus();
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