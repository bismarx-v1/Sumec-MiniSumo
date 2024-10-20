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


/**
 * @brief Sumec UDP lib.
*/
class S_UDP{
private:
	uint16_t udpPortLocal;
	uint16_t udpPortRemote;
	IPAddress localIp;

public:
	S_UDP();
	S_UDP(uint16_t udpPortLocal, uint16_t udpPortRemote);

	void udpSetup(const char* ssid, const char* password);
	void udpSetup(const char* ssid, const char* password, const IPAddress localIp);

	void udpSendToMultiple(uint8_t* byteArray, uint8_t byteArrayLen);
	int8_t updGetOneNewPacket(uint8_t* rxBuffer, uint16_t rxBufferLen);
};

#endif