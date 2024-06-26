/**
 * this has the potential to work but i can't test it right now (it's 2am and i want to sleep (wierd, i know))
 * testing this should be easy. just flash the code, connect to the AP, open any udp send/recieve app,
 * fill out the fields with the data below and send a message.you should also recieve a "Test1 message every 5sec(s)".
 * check serial for the sent data and the udp app for the periodic message
*/
#define UDP_DEBUG 1 //DEBUG

#include "UDP.h"

#define AP_NAME "SUDPRCP_U#1"							// This one is important for connecting to Sumec/the AP
#define AP_PASSWORD "018f34a5-6daa-7729-8ed0-884b8a7c6c45"	// This one's also importan for connecting to Sumec/the AP
															// Does not have to be this strong
#define AP_IP_ADDRESS IPAddress(192,168,1,22)		// This one is important for (the udp scanner app)/(the python script(not included(yet)))
#define UDP_PORT 1984							// Also quite important for the UDP connection
#define UDP_PACKET_BUFFER_LENGTH 32		// This is just the max length of our udp messages
										// First 6 bytes are already taken by internal stuff so use like at least 10(depends on how long our messages will be)


void setup() {
	Serial.begin(115200);
	delay(2000);
	Serial.println("SERIAL LOADED");

	UDPSetup(AP_NAME, AP_PASSWORD, AP_IP_ADDRESS, UDP_PORT, UDP_PACKET_BUFFER_LENGTH);

}

uint8_t ReturnSize;						// DEBUG/testing var
char ReturnMessage[32];					// DEBUG/testing var
IPAddress ReturnIp;						// DEBUG/testing var
#define TimePeriodSend  5000			// DEBUG/testing var
uint64_t TimeLastSend = 0;				// DEBUG/testing var

void loop() {/*
	CheckIfRecieved(&ReturnSize, ReturnMessage, &ReturnIp);
	if(ReturnSize > 0) {
		Serial.print("UDP recieved: ");
		Serial.print(ReturnMessage);
		Serial.print("\tfrom: ");
		Serial.println(ReturnIp);
	}*/
	
	if(millis()-TimePeriodSend >= TimeLastSend) {
		TimeLastSend = millis();
		SendUdpToAll("Test1", 5);
	}
	
	delay(100);
}