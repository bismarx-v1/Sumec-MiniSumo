#if 0
/**
 * This is a sincere apology to any reader
 * this code is definetly not optimalised
 * my attempts at converting to a class failed, problems were with the WiFi.onEvent funcs
 * i think there are multiple formating styles used, because of how bad i am. it took me too long to create and my style just changed a bit over time
 * the uint16_t PacketNum part thaes up 6 bytes instead of the needed 2, because it's sent as string of nums to binary and not numbers to binary
 * good luck :3
 * 
 * job security is my passion, i am irreplaceable
*/
#ifndef UDP_DEBUG
#define UDP_DEBUG 0	// this activates something. needs serial
#endif

#ifndef _UDP_SR_
#define _UDP_SR_

#include <Arduino.h>
#include "WiFiAPStuff.h"
#include <WiFiUdp.h>
#include <esp_wifi.h>

WiFiAPStuff APObject;
WiFiUDP udp;	// create the udp lib object

char udpAddressList[10][IP4ADDR_STRLEN_MAX];	// array for storing connected ips. built for the esp32 max of 10 devices, default max is 4 devices though
uint16_t PacketNum = 0;	// packet counter. range = <0; 65535> (5 digits)
wifi_sta_list_t wifi_sta_list;
tcpip_adapter_sta_list_t adapter_sta_list;
uint8_t IsIP0000 = 0;
uint16_t UdpPort = 0;	//THIS
uint8_t* bufferUint8Pointer = 0;	//THIS
char* bufferPointer = 0;	//THIS
uint16_t bufferLen = 0;	//THIS

/**
 *	@brief Sets the array of char*(s) udpAddressList to connected ip(s) 
*/
void GetIps() {
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
			#if UDP_DEBUG	// DEBUG?
			Serial.println("[Error - SUDPRCP] Station connected too soon. Reconnect it.");
			#endif
			memset(udpAddressList[i], 0, 16);	// delete 0.0.0.0
			udpAddressList[i][0] = '#';
		}
	}
}

/**
 * @brief Callback for when a station connects
 * same as the disconnect one
*/
void StationConnectedToAP(WiFiEvent_t event, WiFiEventInfo_t info) {
	vTaskDelay(100);
	GetIps();	
}

/**
 * @brief Callback for when a station disconnects
 * same as the connect one
*/
void StationDisconnectedFromAP(WiFiEvent_t event, WiFiEventInfo_t info) {
	vTaskDelay(100);
	GetIps();
}

/**
 * @brief This function sets up the AP and callbacks for searching for devices to send packets to
 * @param APName Name of the created access point
 * @param APPass Pass for the created access point
 * @param APIp Ip of the ESP itself
 * @param LUdpPort Port to send the packets to - ex. 1984 (savva picked)
 * @param LBufferLen Max length of the packets in bytes. first 6 bytes are for inefficient packet num shenanigans (sends numbers as chars) - ex. 32
*/
void UDPSetup(char* APName, char* APPass, IPAddress APIp, const uint16_t LUdpPort, uint16_t LBufferLen) {
	uint8_t bufferUint8[LBufferLen];
	char buffer[LBufferLen];

	bufferUint8Pointer = bufferUint8;
	bufferPointer = buffer;
	bufferLen = LBufferLen;
	UdpPort = LUdpPort;

	memset(bufferUint8Pointer, 0, bufferLen);

	// APObject.InitAP("SUDPRCP_U#1", "018f34a5-6daa-7729-8ed0-884b8a7c6c45", IPAddress(192,168,1,22));	// 192.168.1.22 works fine
	// ^That is an example of how it should look like
	// Passwords in plaintext for decreased security
	APObject.InitAP(APName, APPass, APIp);

	udp.begin(UdpPort);
	// on the two lines below can be seen the use of the onEvent function. It can't find the onEvent method
	WiFi.onEvent(StationConnectedToAP, ARDUINO_EVENT_WIFI_AP_STACONNECTED);			// add callback to "station connected to ap" event
	WiFi.onEvent(StationDisconnectedFromAP, ARDUINO_EVENT_WIFI_AP_STADISCONNECTED);	// add the same callback to "station disconected from ap" event
}


/**
 * @brief Sends a type string message to all AP connected clients. some will even catch it
 * @param Message Message to send all listening devices (ex. "it's working!")
 * @param SendNTimes Number of repeats for each device. they might not catch it the first time, i didn't have any problems with it though
*/
void SendUdpToAll(String Message, uint8_t SendNTimes) {
	//memset(bufferUint8Pointer, 0, bufferLen);	// clear buffer
	for(uint8_t i = 0; i < String(PacketNum).length(); i++) {	// set packets num
		//bufferUint8Pointer[i] = String(PacketNum)[i];
	}

	bufferUint8Pointer[String(PacketNum).length()] = '#';	// add dividing char '#'

	for(uint8_t i = 0; i < String(Message).length()+1; i++) {	// add the message
		bufferUint8Pointer[i+1+String(PacketNum).length()] = Message[i];
	}
	
	for(uint8_t i2 = 0; i2 < SendNTimes; i2++) {	// send to each ip 5 times
		/*for(uint8_t i = 0; i < adapter_sta_list.num; i++) {	// send to all connected ips
			if(udpAddressList[i][0] != '#') {
				udp.beginPacket(udpAddressList[i], UdpPort);
				udp.write(bufferUint8Pointer, bufferLen);
				udp.endPacket();
			}
		}*/
	}

	if(PacketNum == 65535) {	// owerflow protection? frickin overbuild
		PacketNum = 0;
	} else {
		PacketNum++;
	}

	#if UDP_DEBUG	// DEBUG?
	Serial.print(millis());
	Serial.print(":\n\tSent:\t");
	for(uint8_t i = 0; i < bufferLen; i++) {
		//Serial.printf("%c", bufferUint8Pointer[i]);
	}

	Serial.print("\n\tto:\n");
	for(uint8_t i = 0; i < adapter_sta_list.num; i++) {
		Serial.print("\t");
		Serial.println(udpAddressList[i][0]);
	}

	Serial.print("\n");
	#endif
}

/**
 * @brief Sets a few variable to the recieved data. if none was recieved, return 0s
 * @param ReturnSize Sets to the number of bytes that were recieved. just for checking if there is something
 * @param ReturnMessage Sets to the rhe recieved message
 * @param ReturnIp Sets to the IP that send the message
*/
void CheckIfRecieved(uint8_t* ReturnSize, char* ReturnMessage, IPAddress* ReturnIp) {
	//processing incoming packet, must be called before reading the buffer
	ReturnSize[0] = udp.parsePacket();
	if(ReturnSize[0] > 0) {
		memset(bufferPointer, 0, bufferLen);
		udp.read(bufferPointer, bufferLen);
		for(uint8_t i = 0; i < bufferLen; i++) {
			ReturnMessage[i] = (char)(bufferPointer[i]);
		}
		
		ReturnIp[0] = udp.remoteIP();
	} else {
		memset(ReturnMessage, 0, bufferLen);
		ReturnIp[0] = IPAddress(0,0,0,0);
	}
}

#endif
#endif