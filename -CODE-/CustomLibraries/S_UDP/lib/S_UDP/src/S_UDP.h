/**
 * Lib made for sending and receiving UDP packets on the Sumec robot.
 * 
 * Yell at ms. Natani using email simacma22@sps-prosek.cz or ms.natani.sim@gmail.com
 *  - ms. Natani
*/

#ifndef S_DUP_h
#define S_DUP_h

#include <Arduino.h>

#include <WiFi.h>
#include <WiFiUdp.h>
#include <esp_wifi.h>


//#define S_UDP_DEBUG 1	// Enable debug mode. Needs serial.	// TODO: remove.

#define MAX_STATIONS 4	// How many stations can be connected to the esp. Normally max 4, apparently can be increased to max 10.
WiFiUDP udpObj;


/**
 * @brief Sumec UDP lib. Define "S_UDP_DEBUG 1" for debug serial prints.
*/
class S_UDP{
private:
	uint16_t udpPortLocal;
	uint16_t udpPortRemote;
	
	void updateConnectedIps(WiFiEvent_t event, WiFiEventInfo_t info);

public:
	IPAddress connectedIps[MAX_STATIONS];	// Array of connected ips.

	S_UDP();
	S_UDP(uint16_t udpPortLocal, uint16_t udpPortRemote);

	void udpSetup(const char* ssid, const char* password);
	void udpSetup(const char* ssid, const char* password, const IPAddress localIp);

	void udpSendToMultiple(IPAddress* ipArray, uint8_t ipArrayLen, uint8_t* byteArray, uint8_t byteArrayLen);
	int8_t updGetOneNewPacket(uint8_t* rxBuffer, uint16_t rxBufferLen);
};

#endif