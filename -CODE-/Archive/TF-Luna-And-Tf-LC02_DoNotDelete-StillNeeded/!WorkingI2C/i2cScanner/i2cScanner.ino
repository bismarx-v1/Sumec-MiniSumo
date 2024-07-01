// --------------------------------------
// i2c_scanner
//
// Modified from https://playground.arduino.cc/Main/I2cScanner/
// --------------------------------------

#include <Wire.h>

// Set I2C bus to use: Wire, Wire1, etc.
#define WIRE Wire
int OddEven = 0;

void setup() {

  pinMode(40, OUTPUT);

	/*pinMode(40, OUTPUT);
	pinMode(41, OUTPUT);
	pinMode(42, OUTPUT);
	digitalWrite(40, LOW);
	digitalWrite(41, LOW);
	digitalWrite(42, LOW);*/
	//WIRE.begin(18,17,400000);
	WIRE.begin(21,22,400000);
	pinMode(32, OUTPUT);
	digitalWrite(32, HIGH);
	pinMode(33, OUTPUT);
	digitalWrite(33, HIGH);

  Serial.begin(115200);
  delay(1000);
  Serial.println("\nI2C Scanner");
}


void loop() {
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");
  Serial.println(millis());

  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    WIRE.beginTransmission(address);
    error = WIRE.endTransmission();

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

	if(OddEven==1) {
		OddEven=0;
		Serial.println("LOW");
	} else {
		OddEven=1;
		Serial.println("HIGH");
	}
	digitalWrite(32, OddEven);
	digitalWrite(33, OddEven);

  delay(5000);           // wait 5 seconds for next scan
}