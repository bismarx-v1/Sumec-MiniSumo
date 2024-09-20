#ifndef _UDP_Stuff
#define _UDP_Stuff

#include <Arduino.h>
#include <WiFiUdp.h>
#include <esp_wifi.h>
#include "WiFiAPStuff.cpp"

#define _UDP_DEBUG 0

WiFiAPStuff AP;	// create my AP lib object
WiFiUDP udp;	// create the udp lib object

char udpAddressList[10][IP4ADDR_STRLEN_MAX];	// array for storing connected ips. built for the esp32 max of 10 devices, default max is 4 devices though

const uint8_t bufferLen = 32;	// the max length of the packets in bytes. first 6 bytes are for inefficient packet num shenanigans (sends numbers as chars)
char buffer[bufferLen];
uint8_t bufferUint8[bufferLen];

uint16_t PacketNum = 0;	// packet counter. range = <0; 65535> (5 digits)

wifi_sta_list_t wifi_sta_list;
tcpip_adapter_sta_list_t adapter_sta_list;

uint16_t UdpPort = 1984;	// set the udp port, savva picked 1984 and i don't expect much trafic on there form our ips

uint8_t IsIP0000 = 0;

void GetIps() {	// sets the array of char*(s) udpAddressList to connected ip(s)
	for(uint8_t i = 0; i < 10; i++) {
		memset(udpAddressList[i], 0, 16);	// clear the char* array
	}

	memset(&wifi_sta_list, 0, sizeof(wifi_sta_list));
	memset(&adapter_sta_list, 0, sizeof(adapter_sta_list));
	esp_wifi_ap_get_sta_list(&wifi_sta_list);
	tcpip_adapter_get_sta_list(&wifi_sta_list, &adapter_sta_list);
	for(uint8_t i = 0; i < adapter_sta_list.num; i++) {	// get num of cennected stations
		tcpip_adapter_sta_info_t station = adapter_sta_list.sta[i];
		char ip[IP4ADDR_STRLEN_MAX];
		esp_ip4addr_ntoa(&station.ip, ip, IP4ADDR_STRLEN_MAX);

		IsIP0000 = 1;	// reset is 0.0.0.0 flag
		for(uint8_t i2 = 0; i2 < IP4ADDR_STRLEN_MAX; i2++) {
			udpAddressList[i][i2] = ip[i2];
			
			if(IsIP0000 == 1) {	// if the address still could be 0.0.0.0
				if(i2 < 8) {	// check if in range
					if(udpAddressList[i][i2] != "0.0.0.0"[i2]) {	// check if is not part of 0.0.0.0
						IsIP0000 = 0;
					}
				}
			}
		}

		if(IsIP0000 == 1) {
			#if _UDP_DEBUG
			Serial.println("Station connected too soon. Reconnect it.");
			#endif
			memset(udpAddressList[i], 0, 16);	// delete 0.0.0.0
			udpAddressList[i][0] = '#';
		}
	}
}

void StationConnectedToAP(WiFiEvent_t event, WiFiEventInfo_t info) {
	vTaskDelay(100);
	GetIps();
	
}

void StationDisconnectedFromAP(WiFiEvent_t event, WiFiEventInfo_t info) {
	vTaskDelay(100);
	GetIps();
}

/**
 * @brief
 * @param UdpTxPort port to send data to
 * @param UdpRxPort port on which you expect to recieve data
 * @param
 * @returns
 */
void UDP_Setup() {
	AP.InitAP("SUDPRCP_U#1", "018f34a5-6daa-7729-8ed0-884b8a7c6c45", IPAddress(192,168,1,22));	// 192.168.1.22
	udp.begin(UdpPort);
	WiFi.onEvent(StationConnectedToAP, ARDUINO_EVENT_WIFI_AP_STACONNECTED);			// add callback to "station connected to ap" event
	WiFi.onEvent(StationDisconnectedFromAP, ARDUINO_EVENT_WIFI_AP_STADISCONNECTED);	// add the same callback to "station disconected from ap" event
}

/**
 * @brief
 * @param
 * @returns
 */
void UDP_SendUdpToAll(String Message, uint8_t SendNTimes) {
	memset(bufferUint8, 0, bufferLen);	// clear buffer
	for(uint8_t i = 0; i < String(PacketNum).length(); i++) {	// set packets num
		bufferUint8[i] = String(PacketNum)[i];
	}

	bufferUint8[String(PacketNum).length()] = '#';	// add dividing char '#'

	for(uint8_t i = 0; i < String(Message).length()+1; i++) {	// add the message
		bufferUint8[i+1+String(PacketNum).length()] = Message[i];
	}
	
	for(uint8_t i2 = 0; i2 < SendNTimes; i2++) {	// send to each ip 5 times
		for(uint8_t i = 0; i < adapter_sta_list.num; i++) {	// send to all connected ips
			if(udpAddressList[i][0] != '#') {
				udp.beginPacket(udpAddressList[i], UdpPort);
				udp.write(bufferUint8, bufferLen);
				udp.endPacket();
			}
		}
	}

	if(PacketNum == 65535) {
		PacketNum = 0;
	} else {
		PacketNum++;
	}

	#if _UDP_DEBUG
	Serial.print(millis());
	Serial.print("\tSent: \t");
	for(uint8_t i = 0; i < bufferLen; i++) {
		Serial.printf("%c", bufferUint8[i]);
	}

	Serial.print("\n");
	#endif
}

/**
 * @brief
 * @param
 * @returns
 */
void UDP_CheckIfRecieved(uint8_t* ReturnSize, char* ReturnMessage, IPAddress* ReturnIp) {
	//processing incoming packet, must be called before reading the buffer
	ReturnSize[0] = udp.parsePacket();
	if(ReturnSize[0] > 0) {
		memset(buffer, 0, bufferLen);
		udp.read(buffer, bufferLen);
		for(uint8_t i = 0; i < bufferLen; i++) {
			ReturnMessage[i] = (char)(buffer[i]);
		}
		
		ReturnIp[0] = udp.remoteIP();
	} else {
		memset(ReturnMessage, 0, bufferLen);
		ReturnIp[0] = IPAddress(0,0,0,0);
	}
}

#endif