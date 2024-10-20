/**
 * 
*/

#include <Arduino.h>
#include "S_UDP.h"

S_UDP sudpObj(2038, 2038);


#define RX_BUFFER_LEN 255
uint8_t testRxBuffer[RX_BUFFER_LEN];

void setup() {
	Serial.begin(115200);
	sudpObj.udpSetup("ssid", "password", IPAddress(192, 168, 4, 1));
}

void loop() {
	#define packetTestSize 64
	uint8_t packetTest[packetTestSize] = "test :3";

	sudpObj.udpSendToMultiple(packetTest, packetTestSize);	// Send packet to all IPs.
	vTaskDelay(5000);

	if(sudpObj.updGetOneNewPacket(testRxBuffer, RX_BUFFER_LEN) == 1) {	// Check if recieved new packets. Print oldest one.
		Serial.print("Recieved: ");
		Serial.printf("%s\n", testRxBuffer);
	}
}
