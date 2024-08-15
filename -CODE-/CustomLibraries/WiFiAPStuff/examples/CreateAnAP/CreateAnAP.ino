#include <Arduino.h>
#include "WiFiAPStuff.h"

WiFiAPStuff APObject;	// Create the object

void setup() {
	APObject.InitAP("SUDPRCP_U#1", "018f34a5-6daa-7729-8ed0-884b8a7c6c45", (192,168,1,22));	// Create the AP
}

void loop() {
	delay(10);
}