#include <Arduino.h>
#include "UDPStuff.h"

const uint64_t TimePeriodSend = 5000;
uint64_t TimeLastSend = 0;

void setup() {
	Serial.begin(115200);

	UDP_Setup();
}

void loop() {
	if(millis()-TimePeriodSend >= TimeLastSend) {
		TimeLastSend = millis();
		UDP_SendUdpToAll("Test1", 5);	// sends string "Test1" 5 times to all connected devices
	}

	delay(100);
}