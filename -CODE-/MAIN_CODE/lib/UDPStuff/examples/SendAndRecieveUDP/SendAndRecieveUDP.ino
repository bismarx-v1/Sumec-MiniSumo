#include <Arduino.h>
#include "UDPStuff.h"

uint8_t ReturnSize;	// munber of bytes recieved
char ReturnMessage[bufferLen];	// recieved message
IPAddress ReturnIp;	// ip of the sender

const uint64_t TimePeriodSend = 5000;
uint64_t TimeLastSend = 0;

void setup() {
	Serial.begin(115200);

	UDP_Setup();
}

void loop() {
	UDP_CheckIfRecieved(&ReturnSize, ReturnMessage, &ReturnIp);	// use this to check for new messages
	if(ReturnSize > 0) {
		Serial.print("UDP recieved: ");
		Serial.print(ReturnMessage);
		Serial.print("\tfrom: ");
		Serial.println(ReturnIp);
	}
	
	if(millis()-TimePeriodSend >= TimeLastSend) {
		TimeLastSend = millis();
		UDP_SendUdpToAll("Test1", 5);	// sends string "Test1" 5 times to all connected devices
	}

	delay(100);
}