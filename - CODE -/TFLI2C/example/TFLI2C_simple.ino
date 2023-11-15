/* File Name: TFLI2C_simple.ino
 * Developer: Bud Ryerson
 * Date:      10 JUL 2021
 * Version:   0.1.1
 * Described: Simplified Arduino example sketch for the Benewake
 *            TF-Luna Lidar sensor configured for the I2C interface
 */
 
#include <Arduino.h>     // Every sketch needs this
#include <Wire.h>        // Instantiate the Wire library
#include <TFLI2C.h>      // TFLuna-I2C Library v.0.1.1

TFLI2C tflI2C;

int16_t  tfDist;    // distance in centimeters
int16_t  tfAddr = TFL_DEF_ADR;  // Use this default I2C address or
                                // set variable to your own value

void setup()
{
    Serial.begin( 115200);  // Initalize serial port
    Wire.begin();           // Initalize Wire library
    Serial.println( "TFLI2C example code simplified"); // Say "Hello!"
    Serial.println( "10 JUL 2021");                    // and add the date.
}

void loop()
{
    if( tflI2C.getData( tfDist, tfAddr)) // If read okay...
    {
        Serial.print("Dist: ");
        Serial.println(tfDist);          // print the data...
    }
    else tflI2C.printStatus();           // else, print error.

    delay( 50);
}
