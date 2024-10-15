#include <Arduino.h>
//#include "S_UDP.h"
#include "..\lib\S_UDP\src\S_UDP.h"

S_UDP sudpObj(2038, 2038);


#define RX_BUFFER_LEN 255
uint8_t testRxBuffer[RX_BUFFER_LEN];

void setup() {
	Serial.begin(115200);
	sudpObj.udpSetup("ssid", "password");
}

void loop() {
	#define packetTestSize 5
	uint8_t packetTest[packetTestSize] = "test";

	sudpObj.udpSendToMultiple(sudpObj.connectedIps, MAX_STATIONS, packetTest, packetTestSize);
	vTaskDelay(5000);

	if(sudpObj.updGetOneNewPacket(testRxBuffer, RX_BUFFER_LEN) == 1) {
		Serial.print("Recieved: ");
		Serial.printf("%s\n", testRxBuffer);
	}
}
