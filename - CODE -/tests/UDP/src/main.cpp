#include <Arduino.h>
#include "UDPStuff.h"

char ReturnMessage[bufferLen];
IPAddress ReturnIp;
uint8_t ReturnSize;
const uint64_t TimePeriodSend = 5000;
uint64_t TimeLastSend = 0;

void setup() {
	Serial.begin(115200);

	AP.InitAP("SUDPRCP_U#1", "018f34a5-6daa-7729-8ed0-884b8a7c6c45", IPAddress(192,168,1,22));	// 192.168.1.22

	udp.begin(UdpPort);

	WiFi.onEvent(StationConnectedToAP, ARDUINO_EVENT_WIFI_AP_STACONNECTED);			// add callback to "station connected to ap" event
	WiFi.onEvent(StationDisconnectedFromAP, ARDUINO_EVENT_WIFI_AP_STADISCONNECTED);	// add the same callback to "station disconected from ap" event

	delay(5000);
}

void loop() {
	
	CheckIfRecieved(&ReturnSize, ReturnMessage, &ReturnIp);
	if(ReturnSize > 0) {
		Serial.print("UDP recieved: ");
		Serial.print(ReturnMessage);
		Serial.print("\tfrom: ");
		Serial.println(ReturnIp);
	}
	
	if(millis()-TimePeriodSend >= TimeLastSend) {
		TimeLastSend = millis();
		SendUdpToAll("Test1", 5);
	}

	delay(100);
}