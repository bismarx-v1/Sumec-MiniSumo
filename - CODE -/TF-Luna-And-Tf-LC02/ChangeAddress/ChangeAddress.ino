#include <Wire.h>        // Instantiate the Wire library
#include <TFLI2C.h>      // TFLuna-I2C Library v.0.1.1

TFLI2C tflI2C;

//int16_t  tfAddr = TFL_DEF_ADR;  // Use this default I2C address or
int16_t  tfAddr = 0x10;
                                // set variable to your own value
int16_t  tfNewAddress = 0x1E;
int16_t  tfAddr1 = 0x1A;
int16_t tfDist;


void setup()
{
    Serial.begin( 115200);  // Initalize serial port
    Wire.begin(11,10,400000);           // Initalize Wire library
	delay(1000);
	
	//Serial.println(tflI2C.Set_I2C_Addr(tfNewAddress, tfAddr));
	//Serial.println(tflI2C.Set_I2C_Addr(tfAddr1, tfAddr));
	//Serial.println(tflI2C.Set_I2C_Addr(tfAddr1, tfNewAddress));
	//delay(5000);
	//Serial.println(tflI2C.Soft_Reset(tfAddr));
	//delay(1000);
	
	
}

void loop()
{
	tflI2C.getData( tfDist, tfNewAddress);
	Serial.println(tfDist);
	tfDist = 0;
	
	tflI2C.getData( tfDist, tfAddr);
	Serial.println(tfDist);
	tfDist = 0;
	
	
	tflI2C.getData( tfDist, tfAddr1);
	Serial.println(tfDist);
	tfDist = 0;
	
	tflI2C.printStatus();
	Serial.println("\n============");
	delay(100);
}