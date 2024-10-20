/**
 * A send and receive example of the Sumec UDP lib.
 *  - ms. Natani :3
*/

#include <Arduino.h>
#include "S_UDP.h"


#if 1	// Rx and tx ports can be default or custom
	S_UDP sudpObj;	// Create lib's obj. Sets both ports to 2038.
#else
	S_UDP sudpObj(2038, 2038);	// Create lib's obj. Also sets both ports to 2038, but .
#endif


#define RX_BUFFER_LEN 510	// Create an array to put the output in. Max is around 1460.
uint8_t rxBuffer[RX_BUFFER_LEN];

#define TX_BUFFER_LEN 64	// Create an array that to send. Max is 1460, rest is skipped.
uint8_t txBuffer[TX_BUFFER_LEN] = "test :3";


void setup() {
	Serial.begin(115200);
	#if 1
		sudpObj.udpSetup("ssid", "password");	// Sets up all the WiFi suff.
	#else
		udpObj.udpSetup("ssid", "password", IPAddress(192, 168, 4, 1));	// Sets up all the WiFi suff, but custom IP.
	#endif
}

void loop() {
	if(sudpObj.updGetOneNewPacket(rxBuffer, RX_BUFFER_LEN) == 1) {	// Check if recieved new packets. Print oldest one.
		#if 0
			Serial.print("Recieved: ");
			Serial.printf("%s\n", rxBuffer);
		#else
			Serial.println("Recieved:");
			Serial.println("Line\tBIN\t\tHEX\tDEC\tASCII");
			Serial.println("---------------------------------------------");
			for(uint16_t i = 0; i < RX_BUFFER_LEN; i++) {
				Serial.print("#");
				Serial.printf("%03i", i);
				Serial.print("\t0b");

				for(uint8_t i2 = 0; i2 < 8; i2++) {
					uint8_t bit = uint8_t(rxBuffer[i]) >> 7-i2;
					Serial.print(bit & 1, BIN);
				}

				Serial.print("\t0x");
				if(rxBuffer[i] <= 0xf) {
					Serial.print("0");
				}

				Serial.print(rxBuffer[i], HEX);
				Serial.print("\t");
				Serial.print(rxBuffer[i]);
				Serial.print("\t");
				Serial.printf("%c\n", rxBuffer[i]);
			}
		#endif
	}

	static uint64_t lastTrig = 0;
	if(lastTrig + 5000 <= millis()) {
		lastTrig = millis();
		sudpObj.udpSendToMultiple(txBuffer, TX_BUFFER_LEN);	// Send packet to all IPs.
	}

	vTaskDelay(100);
}
