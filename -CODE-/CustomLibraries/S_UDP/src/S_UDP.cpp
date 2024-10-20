#include <Arduino.h>

#include "S_UDP.h"

WiFiUDP WiFiObj;


/**
 * @brief Lib constructor. Sets ports to 2038.
*/
S_UDP::S_UDP() {
	this->udpPortLocal = 2038;
	this->udpPortRemote = 2038;
}


/**
 * @brief Advanced lib constructor. Set ports manually.
 * @param udpPortLocal Port on which the ESP recieves UDP packets.
 * @param udpPortRemote Port that the ESP sends the UDP packets to.
*/
S_UDP::S_UDP(uint16_t udpPortLocal, uint16_t udpPortRemote) {
	this->udpPortLocal = udpPortLocal;
	this->udpPortRemote = udpPortRemote;
}


/**
 * @brief Setup for the lib. Creates an AP on the ESP.
 * @param ssid Name of the new AP.
 * @param password Password for the new AP.
 * @note Default IP is 192.168.4.1
*/
void S_UDP::udpSetup(const char* ssid, const char* password) {
	const IPAddress localIp = {192, 168, 4, 1};	// IP of the ESP.
	const IPAddress gateway = {192, 168, 4, 1};	// Networking stuff.
	const IPAddress subnet = {255, 255, 255, 0};	// Networking stuff.
	this->localIp = localIp;

	WiFi.softAPConfig(localIp, gateway, subnet);	// Setup the AP.
	WiFi.softAP(ssid, password);	// Begin the AP.

	WiFiObj.begin(udpPortLocal);
}


/**
 * @brief Advanced setup for the lib. Creates an AP on the ESP with custom IP.
 * @param ssid Name of the new AP.
 * @param password Password for the new AP.
 * @param localIp IP of the ESP.
*/
void S_UDP::udpSetup(const char* ssid, const char* password, const IPAddress localIp) {
	const IPAddress gateway = localIp;	// TODO: Check if correct.
	const IPAddress subnet = {255, 255, 255, 0};
	this->localIp = localIp;

	WiFi.softAPConfig(localIp, gateway, subnet);	// Setup the AP.
	WiFi.softAP(ssid, password);	// Begin the AP.

	WiFiObj.begin(udpPortLocal);
}


/**
 * @brief Sends a packet to multiple IPs at once.
 * @param byteArray Array of bytes that will be sent. Max length is 1460bytes, rest is cut.
 * @param byteArrayLen Length of the byta array.
*/
void S_UDP::udpSendToMultiple(uint8_t* byteArray, uint8_t byteArrayLen) {
	WiFiObj.beginPacket(IPAddress(localIp[0], localIp[1], localIp[2], 255), udpPortRemote);	// Start a packet.
	for(uint8_t i2 = 0; i2 < byteArrayLen && i2 < 1460; i2++) {	// Fill the packet from the byte array.
		WiFiObj.write(byteArray[i2]);
	}
	
	WiFiObj.endPacket();	// Send it.
}


/**
 * @brief Check for any new packets. Puts the oldest one into the buffer.
 * @param rxBuffer Buffer to put the packet to. Max length is around 1460bytes,.
 * @param rxBufferLen Size of the buffer.
 * @returns 0 if there are no new packets, 1 if there are new packets.
*/
int8_t S_UDP::updGetOneNewPacket(uint8_t* rxBuffer, uint16_t rxBufferLen) {
	uint16_t newPacketSize = WiFiObj.parsePacket();	// Get length of the new packet.
	if(newPacketSize == 0) {	// There is no new packet.
		return(0);
	}

	//memset(rxBuffer, 0, rxBufferLen);
	uint16_t rxPacketLen = WiFiObj.read(rxBuffer, rxBufferLen);	// Read the packet.	TODO: Test diff between "rxPacketLen" and "newPacketSize"/
	if(rxPacketLen > 0) {	// Clear the last char. TODO: Test if it's needed.
		rxBuffer[rxPacketLen] = 0;
	}

	return(1);
}
