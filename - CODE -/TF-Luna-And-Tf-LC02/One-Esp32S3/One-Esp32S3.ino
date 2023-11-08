#include <Wire.h>        // Instantiate the Wire library
#include <TFLI2C.h>      // TFLuna-I2C Library v.0.1.1

TFLI2C tflI2C;

int16_t  tfDist;    // distance in centimeters
//int16_t  tfAddr = TFL_DEF_ADR;  // Use this default I2C address or
int16_t  tfAddr = 0x10;
                                // set variable to your own value
int16_t  tfFlux;
int16_t  tfTemp;

void setup()
{
    Serial.begin( 115200);  // Initalize serial port
    Wire.begin(11,10,400000);           // Initalize Wire library
    Serial.println( "TFLI2C example code simplified"); // Say "Hello!"
    Serial.println( "10 JUL 2021");                    // and add the date.
}

void loop()
{
    tflI2C.getData( tfDist, tfFlux, tfTemp, tfAddr); 
    
        Serial.print("Dist:\t");
        Serial.print(tfDist);          // print the data...
		
		Serial.print("\tFlux:\t");
		Serial.print(tfFlux);
		
		Serial.print("\tTemp:\t");
		Serial.print(tfTemp);
		
		Serial.print("\tAddr:\t");
		Serial.println(tfAddr, HEX);
        delay(100);    
}