#if 0
// Check lines with "DEBUG" brfore release

#include "WiFiAPStuff.h"

WiFiAPStuff AP;

void setup() {
	Serial.begin(115200);
	#if	1
		AP.InitAP("SUDPRCP_U#1", "018f34a5-6daa-7729-8ed0-884b8a7c6c45", IPAddress(192,168,1,22));
	#else
		Serial.print(AP.ConnAP("Nat's pc", "********"));	// DEBUG
	#endif

	WiFi.

	
}

void loop() {
	vTaskDelay(1000);
}

#endif
//====================================================================
#if 1
// Check lines with "DEBUG" brfore release

#include <Arduino.h>
#include "WiFiAPStuff.h"
#include <WiFiUdp.h>

WiFiAPStuff AP;
WiFiUDP udp;

const uint16_t UdpPort = 1984;
const char* udpAddress = "192.168.0.106";

const uint8_t bufferLen = 50;
uint8_t buffer[bufferLen];
uint32_t PacketNum = 0;


void CharSToArray(uint8_t* CharArr, char* Str, uint8_t Offset) {
	for(uint8_t i = 0; i <= (sizeof(Str)/sizeof(Str[1]))-1; i++) {
		CharArr[i+Offset] = Str[i];
	}
}

/*
void StringToArray(char* CharArr, String Str, uint8_t Offset) {
	for(uint8_t i = 0; i <= (sizeof(Str)/sizeof(Str[1]))-1; i++) {
		CharArr[i+Offset] = Str[i];
	}
}
*/

void StringToArray(char* CharArr, String Str, uint8_t Offset) {
	Str.toCharArray(CharArr, 50);
}



void SetPacket(uint8_t* Packet, uint32_t PacketNum, char* Payload) {
	//char* PacketNumStr = to_string(PacketNum);
	char* PacketNumStr;
	StringToArray(PacketNumStr, String(PacketNum), 0);

	CharSToArray(Packet, PacketNumStr, 0);
	Packet[(sizeof(PacketNumStr)/sizeof(PacketNumStr[0]))] = '#';
	CharSToArray(Packet, Payload, (sizeof(PacketNumStr)/sizeof(PacketNumStr[0]))+1);
}

void setup() {
	Serial.begin(115200);
	#if	0
		AP.InitAP("SUDPRCP_U#1", "018f34a5-6daa-7729-8ed0-884b8a7c6c45", IPAddress(192,168,1,22));
	#else
		Serial.print(AP.ConnAP("Nat's pc", "********"));	// DEBUG
	#endif

	udp.begin(UdpPort);

	for (uint8_t i = 0; i < 5; i++) {
		SetPacket(buffer, PacketNum, "Test2");
		udp.beginPacket(udpAddress, UdpPort);
		udp.write(buffer, bufferLen);
		udp.endPacket();
		PacketNum++;
		memset(buffer, 0, bufferLen);
	}

	
}

void loop() {
	//processing incoming packet, must be called before reading the buffer
	udp.parsePacket();
	//receive response from server, it will be HELLO WORLD
	if(udp.read(buffer, 50) > 0) {
		Serial.print("Server to client: ");
		Serial.println((char *)buffer);
	}

	vTaskDelay(10);
}

#endif