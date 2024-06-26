#include <Arduino.h>
#include "WiFiAPStuff.h"

WiFiAPStuff APObject;	// Create the object

void setup() {
	Serial.begin(115200);
	Serial.println(APObject.ConnAP("SSID", "Pass"));	// Connect to an AP
}

void loop() {
	delay(10);
}