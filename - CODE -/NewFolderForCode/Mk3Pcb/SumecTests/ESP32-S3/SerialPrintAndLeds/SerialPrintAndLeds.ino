/*
* ESP32-S3 basic functions test
* baud rate = 115200
* 
* This code: 
* 	- prints millis() every 200ms
* 	- flashes both LEDs every 200ms for 100ms
*/

void setup() {
	Serial.begin(115200);
	pinMode(47, OUTPUT);	// pin 47 - D1
	pinMode(48, OUTPUT);	// pin 48 - D2
	
}

void loop() {
	Serial.printf("%i\n", millis());	// prints millis()
	digitalWrite(47, 1);
	digitalWrite(48, 0);
	delay(100);
	digitalWrite(47, 0);
	digitalWrite(48, 1);
	delay(100);
	
}