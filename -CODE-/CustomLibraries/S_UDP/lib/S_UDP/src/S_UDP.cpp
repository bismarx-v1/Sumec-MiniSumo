#include <Arduino.h>

#include "S_UDP.h"


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
*/
void S_UDP::udpSetup(const char* ssid, const char* password) {
	const IPAddress localIp = {192, 168, 1, 1};	// IP of the ESP.
	const IPAddress gateway = {192,186,1,1};	// Networking stuff.
	const IPAddress subnet = {255,255,255,0};	// Networking stuff.

	WiFi.softAPConfig(localIp, gateway, subnet);	// Setup the AP.
	WiFi.softAP(ssid, password);	// Begin the AP.
	WiFi.onEvent(updateConnectedIps, ARDUINO_EVENT_WIFI_AP_STACONNECTED);		// Attach a callback to wifi event.
	WiFi.onEvent(updateConnectedIps, ARDUINO_EVENT_WIFI_AP_STADISCONNECTED);	// Here too.

	udpObj.begin(udpPortLocal);
}


/**
 * @brief Advanced setup for the lib. Creates an AP on the ESP with custom IP.
 * @param ssid Name of the new AP.
 * @param password Password for the new AP.
 * @param localIp IP of the ESP.
*/
void S_UDP::udpSetup(const char* ssid, const char* password, const IPAddress localIp) {
	const IPAddress gateway = {192,186,1,1};
	const IPAddress subnet = {255,255,255,0};

	WiFi.softAPConfig(localIp, gateway, subnet);	// Setup the AP.
	WiFi.softAP(ssid, password);	// Begin the AP.
	WiFi.onEvent(updateConnectedIps, ARDUINO_EVENT_WIFI_AP_STACONNECTED);		// Attach a callback to wifi event.
	WiFi.onEvent(updateConnectedIps, ARDUINO_EVENT_WIFI_AP_STADISCONNECTED);	// Here too.

	udpObj.begin(udpPortLocal);
}


/**
 * @brief Callback triggered when a station connects or disconnects. Updates the connectedIps array.
*/
void S_UDP::updateConnectedIps(WiFiEvent_t event, WiFiEventInfo_t info) {
	wifi_sta_list_t wifi_sta_list;	// Magic.
	memset(&wifi_sta_list, 0, sizeof(wifi_sta_list));	// Clear it.

	tcpip_adapter_sta_list_t adapter_sta_list;	// More magic.
	memset(&adapter_sta_list, 0, sizeof(adapter_sta_list));	// Clear that too.

	for(uint8_t i = 0; i < MAX_STATIONS; i++) {	// Clear
		for(uint8_t i2 = 0; i2 < 4; i2++) {		// connected
			S_UDP::connectedIps[i][i2] = 0;			// IPs.
		}
	}

	esp_wifi_ap_get_sta_list(&wifi_sta_list);	// Evil magic.
	tcpip_adapter_get_sta_list(&wifi_sta_list, &adapter_sta_list);	// Evil-er more magic thing.

	for(uint8_t i = 0; i < adapter_sta_list.num && i < MAX_STATIONS; i++) {	// Itterate through connected stations.
		esp_netif_sta_info_t station = adapter_sta_list.sta[i];	// Set station to this itterations station.
		uint32_t stationIp = esp_ip4_addr(station.ip).addr;	// Get this stations IP.

		if(stationIp == 0) {	// Station connected too early and no ip was assigned.
			// Fix #1 - Kick the offending device. It kicks it but it doesn't let it reconnect (kicks it every time because the IP is 0.0.0.0 again. Seems like some Array with the IPs doesn't clear).
			/*
			uint16_t stationAid;


			if(esp_wifi_ap_get_sta_aid(station.mac, &stationAid) != 0) {	// Get stations aid(authorization id). Return if error.
				#if S_UDP_DEBUG
					Serial.println("S_UDP> Get station aid failed");
				#endif
				return;
			}

			if(esp_wifi_deauth_sta(stationAid) != 0) {	// Deauth station by aid
				#if S_UDP_DEBUG
					Serial.println("S_UDP> Deauth station failed");
				#endif
				return;
			}

			continue;
			*/

			// Fix #2 - Print a debug message to serial.
			#if S_UDP_DEBUG
				Serial.print("S_UDP> DHCP server is not set up yet. Reconnect device '");
				for(uint8_t i = 0; i < 5; i++) {
					if(station.mac[i] < 0x10) {
						Serial.print("0");
					}

					Serial.print(station.mac[i], HEX);
					Serial.print(":");
				}

				if(station.mac[5] < 0x10) {
					Serial.print("0");
				}

				Serial.print(station.mac[5], HEX);
				Serial.println("' please, nya :3");
			#endif

			// Fix #3 - Push through. TODO: Test if this works.
			#if 0
			stationIp = 0x104A8C0;	// Set the ip to 192.168.4.1 because that apparently should fix it (source: https://github.com/espressif/esp-idf/issues/1665)
			#endif
		}
		
		// Add IP to the IP array.	Station ip is a 32bit number 0b(4th octet)(3rd octet)(2nd octet)(1st octet)
		S_UDP::connectedIps[i] = {uint8_t(stationIp & 0xFF), 
							uint8_t(stationIp >> 1*8 & 0xFF), 
							uint8_t(stationIp >> 2*8 & 0xFF), 
							uint8_t(stationIp >> 3*8 & 0xFF)
		};
	}

	#if S_UDP_DEBUG	// Debug print about what happened. Most likely the IP array got updated.
		if(event == ARDUINO_EVENT_WIFI_AP_STACONNECTED) {
			Serial.println("Station connected");
		} else if(event == ARDUINO_EVENT_WIFI_AP_STADISCONNECTED) {
			Serial.println("Station disconnected");
		} else {
			Serial.println("Station did something, QwQ");	// This will never occur, because it's filtered when attaching this callback.
		}

		for(uint8_t i = 0; i < MAX_STATIONS; i++) {	// Print IPs.
			for(uint8_t i2 = 0; i2 < 3; i2++) {
				Serial.print(connectedIps[i][i2]);
				Serial.print(".");
			}

			Serial.println(connectedIps[i][3]);
		}

		Serial.print("@ ");	// Print time.
		Serial.print(millis());
		Serial.println("millis");
	#endif
}


/**
 * @brief Sends a packet to multiple IPs at once.
 * @param ipArray Array of IPs to send to.
 * @param ipArrayLen Length of the IP array.
 * @param remotePort Port to send to.
 * @param byteArray Array of bytes that will be sent.
 * @param byteArrayLen Length of the byta array. Max length is 1460bytes, rest is cut.
*/
void S_UDP::udpSendToMultiple(IPAddress* ipArray, uint8_t ipArrayLen, uint8_t* byteArray, uint8_t byteArrayLen) {
	for(uint8_t i = 0; i < ipArrayLen; i++) {	// Go through all IPs.
		if(ipArray[i] == IPAddress({0, 0, 0, 0})) {	// Empty IP, skip it.
			continue;
		}

		udpObj.beginPacket(ipArray[i], this->udpPortRemote);	// Start a packet.
		for(uint8_t i2 = 0; i2 < byteArrayLen && i2 < 1460; i2++) {	// Fill the packet from the byte array.
			udpObj.write(byteArray[i2]);
		}
		
		udpObj.endPacket();	// Send it.
	}
}


/**
 * @brief Check for any new packets. Puts the oldest one into the buffer.
 * @param rxBuffer Buffer to put the packet to.
 * @param rxBufferLen Size of the buffer.
 * @returns 0 if there are no new packets, 1 if there are new packets.
*/
int8_t S_UDP::updGetOneNewPacket(uint8_t* rxBuffer, uint16_t rxBufferLen) {
	uint32_t newPacketSize = udpObj.parsePacket();	// Get length of the new packet.
	if(newPacketSize == 0) {	// There is no new packet.
		return(0);
	}

	//memset(rxBuffer, 0, rxBufferLen);
	uint16_t rxPacketLen = udpObj.read(rxBuffer, rxBufferLen);	// Read the packet.	TODO: Test diff between "rxPacketLen" and "newPacketSize"/
	if(rxPacketLen > 0) {	// Clear the last char. TODO: Test if it's needed.
		rxBuffer[rxPacketLen] = 0;
	}

	return(1);
}
