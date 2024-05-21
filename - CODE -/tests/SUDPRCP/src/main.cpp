#if 0
// Check lines with "DEBUG" brfore release

#include <Arduino.h>
#include "WiFiAPStuff.h"
#include <WiFiUdp.h>

WiFiAPStuff AP;
WiFiUDP udp;

const uint16_t UdpPort = 1984;
char* udpAddress = "192.168.0.106";

const uint8_t bufferLen = 32;
const uint8_t TempBufferLen = 32;

char buffer[bufferLen];
char TempBuffer[TempBufferLen];
uint32_t PacketNum = 0;
String BufferStr;
uint32_t TempNum = 0;
char temp;

void SwapElements(char &a, char &b) {
    temp = a;
    a = b;
    b = temp;
}


void PacketNumToTempBuffer() {
	memset(TempBuffer, 0, bufferLen);	// clear out var
	TempNum = PacketNum;	// set working var
	uint8_t i = 0;
	while(TempNum > 0) {
		TempBuffer[TempBufferLen-i] = TempNum%10;
		TempNum = uint(TempNum/10);
	}
}

void SendPacket5x(const char* udpAddress, uint16_t UdpPort, String BufferStr) {
	for (uint8_t i = 0; i < 5; i++) {
		memset(buffer, 0, bufferLen);
		PacketNumToTempBuffer();




		//BufferStr.toCharArray(TempBuffer, BufferStr.length());


		for(uint i = 0; i < bufferLen; i++) {
			Serial.print(TempBuffer[i]);
		}

		Serial.print("\n");
		
		for(uint i = 0; i < bufferLen; i++) {
			Serial.println(buffer[i]);
		}

		Serial.print("\n");
		

		/*
		udp.beginPacket(udpAddress, UdpPort);
		udp.write(buffer, bufferLen);
		udp.endPacket();
		*/
	}

	PacketNum++;
}

void setup() {
	Serial.begin(115200);
	#if	0
		AP.InitAP("SUDPRCP_U#1", "018f34a5-6daa-7729-8ed0-884b8a7c6c45", IPAddress(192,168,1,22));
	#else
		Serial.print(AP.ConnAP("[SSID]", "[Pass]"));	// DEBUG
	#endif

	udp.begin(UdpPort);

	SendPacket5x(udpAddress, UdpPort, "Test1");
}

void loop() {
	/*
	//processing incoming packet, must be called before reading the buffer
	udp.parsePacket();
	//receive response from server, it will be HELLO WORLD
	if(udp.read(buffer, bufferLen) > 0) {
		Serial.print("Server to client: ");
		Serial.println((char *)buffer);
	}
	*/

	vTaskDelay(10);
}

#endif
//====================================================================
#if 0	// main
// Check lines with "DEBUG" brfore release

#include <Arduino.h>
#include "WiFiAPStuff.h"
#include <WiFiUdp.h>
#include "esp_wifi.h"

WiFiAPStuff AP;
WiFiUDP udp;

const uint16_t UdpPort = 1984;
char* udpAddress = "192.168.0.106";


const uint8_t bufferLen = 32;

char buffer[bufferLen];
uint32_t PacketNum = 0;

void SwapElements(char &a, char &b) {
	char temp = a;
	a = b;
	b = temp;
}

void StationConnectedToAP(WiFiEvent_t event, WiFiEventInfo_t info) {
	Serial.print("Connected\n");
	
}

void StationDisconnectedFromAP(WiFiEvent_t event, WiFiEventInfo_t info) {
	Serial.print("Disconnected\n");
}



void setup() {
	Serial.begin(115200);

	AP.InitAP("SUDPRCP_U#1", "018f34a5-6daa-7729-8ed0-884b8a7c6c45", IPAddress(192,168,1,22));

	udp.begin(UdpPort);

	//WiFi.onEvent(StationConnectedToAP, SYSTEM_EVENT_AP_STACONNECTED);
	//WiFi.onEvent(StationDisconnectedFromAP, SYSTEM_EVENT_AP_STADISCONNECTED);

	WiFi.onEvent(StationConnectedToAP, ARDUINO_EVENT_WIFI_AP_STACONNECTED);
	WiFi.onEvent(StationDisconnectedFromAP, ARDUINO_EVENT_WIFI_AP_STADISCONNECTED);

	/*
	ARDUINO_EVENT_WIFI_AP_STACONNECTED
	ARDUINO_EVENT_WIFI_AP_STADISCONNECTED
	*/
	

}

void loop() {
	/*
	//processing incoming packet, must be called before reading the buffer
	udp.parsePacket();
	//receive response from server, it will be HELLO WORLD
	if(udp.read(buffer, bufferLen) > 0) {
		Serial.print("Server to client: ");
		Serial.println((char *)buffer);
	}
	*/

	vTaskDelay(10);
}

#endif

#if 0	// get all ips
#include <WiFi.h>
#include "esp_wifi.h"

void setup() { 
	Serial.begin(115200);
	WiFi.softAP("MyESP32AP");
}

void loop() {
	wifi_sta_list_t wifi_sta_list;  tcpip_adapter_sta_list_t adapter_sta_list;
	memset(&wifi_sta_list, 0, sizeof(wifi_sta_list));
	memset(&adapter_sta_list, 0, sizeof(adapter_sta_list));
	esp_wifi_ap_get_sta_list(&wifi_sta_list);
	tcpip_adapter_get_sta_list(&wifi_sta_list, &adapter_sta_list);
	for (int i = 0; i < adapter_sta_list.num; i++) {
		tcpip_adapter_sta_info_t station = adapter_sta_list.sta[i];
		Serial.print("station nr ");
		Serial.println(i);
		Serial.print("MAC: ");
		for(int i = 0; i< 6; i++) {
			Serial.printf("%02X", station.mac[i]);
			if(i<5) {
				Serial.print(":");
			}
		}

		Serial.print("\nIP: ");
		#if 0
		Serial.println(ip4addr_ntoa(&(station.ip)));
		#else
		char ip[IP4ADDR_STRLEN_MAX];
		esp_ip4addr_ntoa(&station.ip, ip, IP4ADDR_STRLEN_MAX);
		Serial.println(ip);
		#endif

	}

	Serial.println("-----------");
	delay(5000);
}
#endif

#if 0	// events

#include <WiFi.h>
 
const char* ssid = "REPLACE_WITH_YOUR_SSID";
const char* password = "REPLACE_WITH_YOUR_PASSWORD";

void WiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info){
  Serial.println("Connected to AP successfully!");
}

void WiFiGotIP(WiFiEvent_t event, WiFiEventInfo_t info){
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info){
  Serial.println("Disconnected from WiFi access point");
  Serial.print("WiFi lost connection. Reason: ");
  Serial.println(info.wifi_sta_disconnected.reason);
  Serial.println("Trying to Reconnect");
  WiFi.begin(ssid, password);
}

void setup(){
  Serial.begin(115200);

  // delete old config
  WiFi.disconnect(true);

  delay(1000);

  WiFi.onEvent(WiFiStationConnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_CONNECTED);
  WiFi.onEvent(WiFiGotIP, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_GOT_IP);
  WiFi.onEvent(WiFiStationDisconnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED);

  /* Remove WiFi event
  Serial.print("WiFi Event ID: ");
  Serial.println(eventID);
  WiFi.removeEvent(eventID);*/

  WiFi.begin(ssid, password);
    
  Serial.println();
  Serial.println();
  Serial.println("Wait for WiFi... ");
}

void loop(){
  delay(1000);
}
#endif

#if 0	// get all ips - edited

wifi_sta_list_t wifi_sta_list;
tcpip_adapter_sta_list_t adapter_sta_list;

void GetIps() {
	memset(&wifi_sta_list, 0, sizeof(wifi_sta_list));
	memset(&adapter_sta_list, 0, sizeof(adapter_sta_list));
	esp_wifi_ap_get_sta_list(&wifi_sta_list);
	tcpip_adapter_get_sta_list(&wifi_sta_list, &adapter_sta_list);
	for (int i = 0; i < adapter_sta_list.num; i++) {
		tcpip_adapter_sta_info_t station = adapter_sta_list.sta[i];
		Serial.print("station nr ");
		Serial.println(i);
		Serial.print("MAC: ");
		for(int i = 0; i< 6; i++) {
			Serial.printf("%02X", station.mac[i]);
			if(i<5) {
				Serial.print(":");
			}
		}

		Serial.print("\nIP: ");
		
		char ip[IP4ADDR_STRLEN_MAX];
		esp_ip4addr_ntoa(&station.ip, ip, IP4ADDR_STRLEN_MAX);
		Serial.println(ip);
	}
}
#endif

//====================================================================
#if 0	// main 2 - frickin' works!
// Check lines with "DEBUG" brfore release

#include <Arduino.h>
#include "WiFiAPStuff.h"
#include <WiFiUdp.h>
#include "esp_wifi.h"

WiFiAPStuff AP;
WiFiUDP udp;

const uint16_t UdpPort = 1984;
char* udpAddress = "192.168.0.106";
char udpAddressList[10][IP4ADDR_STRLEN_MAX];	// built for the esp32 max of 10 devices, default max is 4 devices though


const uint8_t bufferLen = 32;

char buffer[bufferLen];
uint8_t bufferUint8[bufferLen];
uint32_t PacketNum = 0;

wifi_sta_list_t wifi_sta_list;
tcpip_adapter_sta_list_t adapter_sta_list;

void GetIps() {
	for(uint8_t i = 0; i < 10; i++) {
		memset(udpAddressList[i], 0, 16);
	}

	memset(&wifi_sta_list, 0, sizeof(wifi_sta_list));
	memset(&adapter_sta_list, 0, sizeof(adapter_sta_list));
	esp_wifi_ap_get_sta_list(&wifi_sta_list);
	tcpip_adapter_get_sta_list(&wifi_sta_list, &adapter_sta_list);
	for(uint8_t i = 0; i < adapter_sta_list.num; i++) {
		tcpip_adapter_sta_info_t station = adapter_sta_list.sta[i];
		char ip[IP4ADDR_STRLEN_MAX];
		esp_ip4addr_ntoa(&station.ip, ip, IP4ADDR_STRLEN_MAX);
		for(uint8_t i2 = 0; i2 < IP4ADDR_STRLEN_MAX; i2++) {
			udpAddressList[i][i2] = ip[i2];
		}
		
		Serial.println(ip);
	}

}

void StationConnectedToAP(WiFiEvent_t event, WiFiEventInfo_t info) {
	vTaskDelay(100);
	GetIps();
	Serial.println("------------");
	
}

void StationDisconnectedFromAP(WiFiEvent_t event, WiFiEventInfo_t info) {
	vTaskDelay(100);
	GetIps();
	Serial.println("------------");
}



void setup() {
	Serial.begin(115200);

	AP.InitAP("SUDPRCP_U#1", "018f34a5-6daa-7729-8ed0-884b8a7c6c45", IPAddress(192,168,1,22));	// 192.168.1.22

	udp.begin(UdpPort);

	WiFi.onEvent(StationConnectedToAP, ARDUINO_EVENT_WIFI_AP_STACONNECTED);
	WiFi.onEvent(StationDisconnectedFromAP, ARDUINO_EVENT_WIFI_AP_STADISCONNECTED);

	delay(5000);
}

void loop() {
	
	//processing incoming packet, must be called before reading the buffer
	if(udp.parsePacket() > 0) {
		memset(buffer, 0, bufferLen);
		udp.read(buffer, bufferLen);
		Serial.print("UDP recieved: ");
		Serial.print((char *)buffer);
		Serial.print("\tfrom: ");
		Serial.println(udp.remoteIP());
	}



	memset(bufferUint8, 0, bufferLen);	// clear buffer
	for(uint8_t i = 0; i < String(PacketNum).length(); i++) {	// set packets num
		bufferUint8[i] = String(PacketNum)[i];
	}

	bufferUint8[String(PacketNum).length()] = '#';	// add dividing char '#'

	for(uint8_t i = 0; i < String("test1").length()+1; i++) {	// add the message
		bufferUint8[i+1+String(PacketNum).length()] = "test1"[i];
	}
	
	for(uint8_t i2 = 0; i2 < 5; i2++) {	// send to each ip 5 times
		for(uint8_t i = 0; i < adapter_sta_list.num; i++) {	// send to all connected ips
			udp.beginPacket(udpAddressList[i], UdpPort);
			udp.write(bufferUint8, bufferLen);
			udp.endPacket();
		}
	}

	PacketNum++;


	vTaskDelay(5000);
}

#endif

//====================================================================
#if 0	// main 2 - but better writen
// Check lines with "DEBUG" brfore release

#include <Arduino.h>
#include "WiFiAPStuff.h"
#include <WiFiUdp.h>
#include "esp_wifi.h"

WiFiAPStuff AP;	// create my AP lib object
WiFiUDP udp;	// create the udp lib object

const uint16_t UdpPort = 1984;	// set the udp port, savva picked 1984 and i don't expect much trafic on there form our ips
char udpAddressList[10][IP4ADDR_STRLEN_MAX];	// array for storing connected ips. built for the esp32 max of 10 devices, default max is 4 devices though


const uint8_t bufferLen = 32;	// the max length of the packets in bytes. first 6 bytes are for inefficient packet num shenanigans (sends numbers as chars)
char buffer[bufferLen];
uint8_t bufferUint8[bufferLen];

uint16_t PacketNum = 0;	// packet counter. range = <0; 65535> (5 digits)

wifi_sta_list_t wifi_sta_list;
tcpip_adapter_sta_list_t adapter_sta_list;

uint8_t IsIP0000 = 0;

char ReturnMessage[bufferLen];			// DEBUG/testing var
IPAddress ReturnIp;						// DEBUG/testing var
uint8_t ReturnSize;						// DEBUG/testing var
const uint64_t TimePeriodSend = 5000;	// DEBUG/testing var
uint64_t TimeLastSend = 0;				// DEBUG/testing var

void GetIps() {	// sets the array of char*(s) udpAddressList to connected ip(s)
	for(uint8_t i = 0; i < 10; i++) {
		memset(udpAddressList[i], 0, 16);		// clear the char* array
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
			Serial.println("Station connected too soon. Reconnect it.");
			memset(udpAddressList[i], 0, 16);	// delete 0.0.0.0
			udpAddressList[i][0] = '#';
		}
	}
}

void StationConnectedToAP(WiFiEvent_t event, WiFiEventInfo_t info) {
	vTaskDelay(100);
	GetIps();
	Serial.println("------------");
	
}

void StationDisconnectedFromAP(WiFiEvent_t event, WiFiEventInfo_t info) {
	vTaskDelay(100);
	GetIps();
	Serial.println("------------");
}

void SendUdpToAll(String Message, uint8_t SendNTimes) {
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

	Serial.print(millis());
	Serial.print("\tSent: \t");
	for(uint8_t i = 0; i < bufferLen; i++) {
		Serial.printf("%c", bufferUint8[i]);
	}

	Serial.print("\n");
}

void CheckIfRecieved(uint8_t* ReturnSize, char* ReturnMessage, IPAddress* ReturnIp) {
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

void setup() {
	Serial.begin(115200);

	AP.InitAP("SUDPRCP_U#1", "018f34a5-6daa-7729-8ed0-884b8a7c6c45", IPAddress(192,168,1,22));	// 192.168.1.22

	udp.begin(UdpPort);

	WiFi.onEvent(StationConnectedToAP, ARDUINO_EVENT_WIFI_AP_STACONNECTED);			// add callback to "station connected to ap" event
	WiFi.onEvent(StationDisconnectedFromAP, ARDUINO_EVENT_WIFI_AP_STADISCONNECTED);	// add the same callback to "station disconected from ap" event

	delay(5000);
}

void loop() {
	
	CheckIfRecieved(&ReturnSize, ReturnMessage, &ReturnIp);
	if(ReturnSize > 0) {
		Serial.print("UDP recieved: ");
		Serial.print(ReturnMessage);
		Serial.print("\tfrom: ");
		Serial.println(ReturnIp);
	}
	
	if(millis()-TimePeriodSend >= TimeLastSend) {
		TimeLastSend = millis();
		SendUdpToAll("Test1", 5);
	}
}

#endif

//====================================================================
#if 0	// main 2 - as a class
// Check lines with "DEBUG" brfore release

#ifndef _SUDPRCP_
#define _SUDPRCP_

#include <Arduino.h>
#include "WiFiAPStuff.h"
#include <WiFiUdp.h>
#include "esp_wifi.h"

WiFiAPStuff AP;	// create my AP lib object
WiFiUDP udp;	// create the udp lib object

class SUDPRCP {
	private:
		char udpAddressList[10][IP4ADDR_STRLEN_MAX];	// array for storing connected ips. built for the esp32 max of 10 devices, default max is 4 devices though

		uint16_t PacketNum = 0;	// packet counter. range = <0; 65535> (5 digits)

		wifi_sta_list_t wifi_sta_list;
		tcpip_adapter_sta_list_t adapter_sta_list;

		uint8_t IsIP0000 = 0;

		uint16_t UdpPort = 0;

		uint8_t* bufferUint8Pointer = 0;
		char* bufferPointer = 0;
		
		void StationConnectedToAP(WiFiEvent_t event, WiFiEventInfo_t info);
		void StationDisconnectedFromAP(WiFiEvent_t event, WiFiEventInfo_t info);
		void GetIps();

	public:
		SUDPRCP();

		uint16_t bufferLen = 0;

		void begin(const uint16_t LUdpPort, const uint16_t LBufferLen);
		void SendUdpToAll(String Message, uint8_t SendNTimes);
		void CheckIfRecieved(uint8_t* ReturnSize, char* ReturnMessage, IPAddress* ReturnIp);
};

SUDPRCP::SUDPRCP() {}

/**
 * @brief 
 * @param LUdpPort Port to send the packets to - ex. 1984 (savva picked)
 * @param LBufferLen Max length of the packets in bytes. first 6 bytes are for inefficient packet num shenanigans (sends numbers as chars) - ex. 32
*/
void SUDPRCP::begin(const uint16_t LUdpPort, uint16_t LBufferLen) {
	uint8_t bufferUint8[LBufferLen];
	char buffer[LBufferLen];

	bufferUint8Pointer = bufferUint8;
	bufferPointer = buffer;
	bufferLen = LBufferLen;
	UdpPort = LUdpPort;

	AP.InitAP("SUDPRCP_U#1", "018f34a5-6daa-7729-8ed0-884b8a7c6c45", IPAddress(192,168,1,22));	// 192.168.1.22

	udp.begin(UdpPort);


	WiFi.onEvent(StationConnectedToAP, ARDUINO_EVENT_WIFI_AP_STACONNECTED);			// add callback to "station connected to ap" event
	WiFi.onEvent(StationDisconnectedFromAP, ARDUINO_EVENT_WIFI_AP_STADISCONNECTED);	// add the same callback to "station disconected from ap" event


}

/**
 * @brief Sets the array of char*(s) udpAddressList to connected ip(s)
*/
void SUDPRCP::GetIps() {
	for(uint8_t i = 0; i < 10; i++) {
		memset(udpAddressList[i], 0, 16);		// clear the char* array
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
			Serial.println("[Error - SUDPRCP] Station connected too soon. Reconnect it.");
			memset(udpAddressList[i], 0, 16);	// delete 0.0.0.0
			udpAddressList[i][0] = '#';
		}
	}
}

/**
 * @brief Callback for when a station connects
 * same as the disconnect one
*/
void SUDPRCP::StationConnectedToAP(WiFiEvent_t event, WiFiEventInfo_t info) {
	vTaskDelay(100);
	GetIps();
	
}

/**
 * @brief Callback for when a station disconnects
 * same as the connect one
*/
void SUDPRCP::StationDisconnectedFromAP(WiFiEvent_t event, WiFiEventInfo_t info) {
	vTaskDelay(100);
	GetIps();
}


/**
 * @brief
 * @param
*/
void SUDPRCP::SendUdpToAll(String Message, uint8_t SendNTimes) {
	memset(bufferUint8Pointer, 0, bufferLen);	// clear buffer
	for(uint8_t i = 0; i < String(PacketNum).length(); i++) {	// set packets num
		bufferUint8Pointer[i] = String(PacketNum)[i];
	}

	bufferUint8Pointer[String(PacketNum).length()] = '#';	// add dividing char '#'

	for(uint8_t i = 0; i < String(Message).length()+1; i++) {	// add the message
		bufferUint8Pointer[i+1+String(PacketNum).length()] = Message[i];
	}
	
	for(uint8_t i2 = 0; i2 < SendNTimes; i2++) {	// send to each ip 5 times
		for(uint8_t i = 0; i < adapter_sta_list.num; i++) {	// send to all connected ips
			if(udpAddressList[i][0] != '#') {
				udp.beginPacket(udpAddressList[i], UdpPort);
				udp.write(bufferUint8Pointer, bufferLen);
				udp.endPacket();
			}
		}
	}

	if(PacketNum == 65535) {
		PacketNum = 0;
	} else {
		PacketNum++;
	}

	Serial.print(millis());
	Serial.print("\tSent: \t");
	for(uint8_t i = 0; i < bufferLen; i++) {
		Serial.printf("%c", bufferUint8Pointer[i]);
	}

	Serial.print("\n");
}

/**
 * @brief
 * @param
*/
void SUDPRCP::CheckIfRecieved(uint8_t* ReturnSize, char* ReturnMessage, IPAddress* ReturnIp) {
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

SUDPRCP Test;


char ReturnMessage[32];					// DEBUG/testing var
IPAddress ReturnIp;						// DEBUG/testing var
uint8_t ReturnSize;						// DEBUG/testing var
const uint64_t TimePeriodSend = 5000;	// DEBUG/testing var
uint64_t TimeLastSend = 0;				// DEBUG/testing var

void setup() {
	Serial.begin(115200);

	Test.begin(1984, 32);

	delay(5000);
}

void loop() {
	Test.CheckIfRecieved(&ReturnSize, ReturnMessage, &ReturnIp);
	if(ReturnSize > 0) {
		Serial.print("UDP recieved: ");
		Serial.print(ReturnMessage);
		Serial.print("\tfrom: ");
		Serial.println(ReturnIp);
	}
	
	if(millis()-TimePeriodSend >= TimeLastSend) {
		TimeLastSend = millis();
		Test.SendUdpToAll("Test1", 5);
	}
}

#endif
#endif

//====================================================================
#if 0	// main 2 - main test
// Check lines with "DEBUG" brfore release

#include "SUDPRCP.h"

SUDPRCP Test;

char ReturnMessage[32];					// DEBUG/testing var
IPAddress ReturnIp;						// DEBUG/testing var
uint8_t ReturnSize;						// DEBUG/testing var
const uint64_t TimePeriodSend = 5000;	// DEBUG/testing var
uint64_t TimeLastSend = 0;				// DEBUG/testing var

void setup() {
	Serial.begin(115200);

	Test.begin(1984, 32);
	WiFi.onEvent(StationConnectedToAP, ARDUINO_EVENT_WIFI_AP_STACONNECTED);			// add callback to "station connected to ap" event
	WiFi.onEvent(StationDisconnectedFromAP, ARDUINO_EVENT_WIFI_AP_STADISCONNECTED);	// add the same callback to "station disconected from ap" event
}

void loop() {
	Test.CheckIfRecieved(&ReturnSize, ReturnMessage, &ReturnIp);
	if(ReturnSize > 0) {
		Serial.print("UDP recieved: ");
		Serial.print(ReturnMessage);
		Serial.print("\tfrom: ");
		Serial.println(ReturnIp);
	}
	
	if(millis()-TimePeriodSend >= TimeLastSend) {
		TimeLastSend = millis();
		Test.SendUdpToAll("Test1", 5);
	}
}

#endif

//====================================================================
#if 1	// main 2 - as a class with a function pointer
// Check lines with "DEBUG" brfore release

#include "SUDPRCP.h"

#ifndef _SUDPRCP_
#define _SUDPRCP_

#include <Arduino.h>
#include "WiFiAPStuff.h"
#include <WiFiUdp.h>
#include "esp_wifi.h"

WiFiAPStuff AP;	// create my AP lib object
WiFiUDP udp;	// create the udp lib object

class SUDPRCP {
	private:
		char udpAddressList[10][IP4ADDR_STRLEN_MAX];	// array for storing connected ips. built for the esp32 max of 10 devices, default max is 4 devices though

		uint16_t PacketNum = 0;	// packet counter. range = <0; 65535> (5 digits)

		wifi_sta_list_t wifi_sta_list;
		tcpip_adapter_sta_list_t adapter_sta_list;

		uint8_t IsIP0000 = 0;

		uint16_t UdpPort = 0;

		uint8_t* bufferUint8Pointer = 0;
		char* bufferPointer = 0;
		
		void GetIps();

	public:
		SUDPRCP();

		uint16_t bufferLen = 0;

		void begin(const uint16_t LUdpPort, const uint16_t LBufferLen);
		void SendUdpToAll(String Message, uint8_t SendNTimes);
		void CheckIfRecieved(uint8_t* ReturnSize, char* ReturnMessage, IPAddress* ReturnIp);

		void StationConnectedToAP(WiFiEvent_t event, WiFiEventInfo_t info);
		void StationDisconnectedFromAP(WiFiEvent_t event, WiFiEventInfo_t info);
};

SUDPRCP::SUDPRCP() {}

/**
 * @brief 
 * @param LUdpPort Port to send the packets to - ex. 1984 (savva picked)
 * @param LBufferLen Max length of the packets in bytes. first 6 bytes are for inefficient packet num shenanigans (sends numbers as chars) - ex. 32
*/
void SUDPRCP::begin(const uint16_t LUdpPort, uint16_t LBufferLen) {
	uint8_t bufferUint8[LBufferLen];
	char buffer[LBufferLen];

	bufferUint8Pointer = bufferUint8;
	bufferPointer = buffer;
	bufferLen = LBufferLen;
	UdpPort = LUdpPort;

	AP.InitAP("SUDPRCP_U#1", "018f34a5-6daa-7729-8ed0-884b8a7c6c45", IPAddress(192,168,1,22));	// 192.168.1.22

	udp.begin(UdpPort);
}

/**
 * @brief Sets the array of char*(s) udpAddressList to connected ip(s)
*/
void SUDPRCP::GetIps() {
	for(uint8_t i = 0; i < 10; i++) {
		memset(udpAddressList[i], 0, 16);		// clear the char* array
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
			Serial.println("[Error - SUDPRCP] Station connected too soon. Reconnect it.");
			memset(udpAddressList[i], 0, 16);	// delete 0.0.0.0
			udpAddressList[i][0] = '#';
		}
	}
}

/**
 * @brief Callback for when a station connects
 * same as the disconnect one
*/
void SUDPRCP::StationConnectedToAP(WiFiEvent_t event, WiFiEventInfo_t info) {
	vTaskDelay(100);
	GetIps();
}

/**
 * @brief Callback for when a station disconnects
 * same as the connect one
*/
void SUDPRCP::StationDisconnectedFromAP(WiFiEvent_t event, WiFiEventInfo_t info) {
	vTaskDelay(100);
	GetIps();
}


/**
 * @brief
 * @param
*/
void SUDPRCP::SendUdpToAll(String Message, uint8_t SendNTimes) {
	memset(bufferUint8Pointer, 0, bufferLen);	// clear buffer
	for(uint8_t i = 0; i < String(PacketNum).length(); i++) {	// set packets num
		bufferUint8Pointer[i] = String(PacketNum)[i];
	}

	bufferUint8Pointer[String(PacketNum).length()] = '#';	// add dividing char '#'

	for(uint8_t i = 0; i < String(Message).length()+1; i++) {	// add the message
		bufferUint8Pointer[i+1+String(PacketNum).length()] = Message[i];
	}
	
	for(uint8_t i2 = 0; i2 < SendNTimes; i2++) {	// send to each ip 5 times
		for(uint8_t i = 0; i < adapter_sta_list.num; i++) {	// send to all connected ips
			if(udpAddressList[i][0] != '#') {
				udp.beginPacket(udpAddressList[i], UdpPort);
				udp.write(bufferUint8Pointer, bufferLen);
				udp.endPacket();
			}
		}
	}

	if(PacketNum == 65535) {
		PacketNum = 0;
	} else {
		PacketNum++;
	}

	Serial.print(millis());
	Serial.print("\tSent: \t");
	for(uint8_t i = 0; i < bufferLen; i++) {
		Serial.printf("%c", bufferUint8Pointer[i]);
	}

	Serial.print("\n");
}

/**
 * @brief
 * @param
*/
void SUDPRCP::CheckIfRecieved(uint8_t* ReturnSize, char* ReturnMessage, IPAddress* ReturnIp) {
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

SUDPRCP Test;


char ReturnMessage[32];					// DEBUG/testing var
IPAddress ReturnIp;						// DEBUG/testing var
uint8_t ReturnSize;						// DEBUG/testing var
const uint64_t TimePeriodSend = 5000;	// DEBUG/testing var
uint64_t TimeLastSend = 0;				// DEBUG/testing var

void setup() {
	Serial.begin(115200);

	Test.begin(1984, 32);
	SUDPRCPCallbackSetup();

	delay(5000);
}

void loop() {
	Test.CheckIfRecieved(&ReturnSize, ReturnMessage, &ReturnIp);
	if(ReturnSize > 0) {
		Serial.print("UDP recieved: ");
		Serial.print(ReturnMessage);
		Serial.print("\tfrom: ");
		Serial.println(ReturnIp);
	}
	
	if(millis()-TimePeriodSend >= TimeLastSend) {
		TimeLastSend = millis();
		Test.SendUdpToAll("Test1", 5);
	}
}

#endif