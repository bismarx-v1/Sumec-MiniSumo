/**
 * working backup without objects and with too large functions that should be broken up into smaller ones.
*/

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <esp_wifi.h>

#define S_UDP_DEBUG 1	// Enable debug mode. Needs serial.

#define MAX_STATIONS 4	// How many stations can be connected to the esp. Normally max 4, apparently can be increased to max 10.

WiFiUDP udpObj;

IPAddress connectedIps[MAX_STATIONS];	// Array of connected ips.
#define RX_BUFFER_LEN 255
uint8_t rxBuffer[RX_BUFFER_LEN];



/**
 * @brief Callback triggered when a station connects or disconnects. Updates the connectedIps array.
*/
static void updateConnectedIps(WiFiEvent_t event, WiFiEventInfo_t info) {
	wifi_sta_list_t wifi_sta_list;	// Magic.
	memset(&wifi_sta_list, 0, sizeof(wifi_sta_list));	// Clear it.

	tcpip_adapter_sta_list_t adapter_sta_list;	// More magic.
	memset(&adapter_sta_list, 0, sizeof(adapter_sta_list));	// Clear that too.

	for(uint8_t i = 0; i < MAX_STATIONS; i++) {	// Clear
		for(uint8_t i2 = 0; i2 < 4; i2++) {		// connected
			connectedIps[i][i2] = 0;			// IPs.
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

			// Fix #3 - Push through.
			#if 0
			stationIp = 0x104A8C0;	// Set the ip to 192.168.4.1 because that apparently should fix it (source: https://github.com/espressif/esp-idf/issues/1665)
			#endif
		}
		
		// Add IP to the IP array.	Station ip is a 32bit number 0b(4th octet)(3rd octet)(2nd octet)(1st octet)
		connectedIps[i] = {uint8_t(stationIp & 0xFF), 
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

		for(uint8_t i = 0; i < MAX_STATIONS; i++) {
			for(uint8_t i2 = 0; i2 < 3; i2++) {
				Serial.print(connectedIps[i][i2]);
				Serial.print(".");
			}

			Serial.println(connectedIps[i][3]);
		}

		Serial.print("@ ");
		Serial.print(millis());
		Serial.println("millis\tnya");
	#endif
}

/**
 * TODO: comments
*/
void udpSendToMultiple(IPAddress* ipArray, uint8_t ipArrayLen, uint16_t remotePort, uint8_t* byteArray, uint8_t byteArrayLen) {
	for(uint8_t i = 0; i < ipArrayLen; i++) {
		if(ipArray[i] == IPAddress({0, 0, 0, 0})) {
			continue;
		}

		udpObj.beginPacket(ipArray[i], remotePort);
		for(uint8_t i2 = 0; i2 < byteArrayLen; i2++) {
			udpObj.write(byteArray[i2]);
		}
		
		udpObj.endPacket();
	}
}


/**
 * TODO: comments
*/
int8_t updGetOneNewPacket(uint8_t* rxBuffer, uint16_t rxBufferLen) {
	uint32_t newPacketSize = udpObj.parsePacket();
	if(newPacketSize == 0) {
		return(0);
	}

	//memset(rxBuffer, 0, rxBufferLen);
	uint16_t rxPacketLen = udpObj.read(rxBuffer, rxBufferLen);
	if(rxPacketLen > 0) {
		rxBuffer[rxPacketLen] = 0;
	}

	return(1);
}




const char* ssid = "ssid";
const char* password = "password";
const IPAddress localIp = {192, 168, 1, 1};
const uint16_t udpPortLocal = 2038;
const uint16_t udpPortRemote = 2038;
const IPAddress gateway = {192,186,1,5};
const IPAddress subnet = {255,255,255,0};




/**
 * TODO: Comments.
*/
void udpSetup() {
	WiFi.softAPConfig(localIp, gateway, subnet);	// Setup the AP.
	WiFi.softAP(ssid, password);	// Begin the AP.
	WiFi.onEvent(updateConnectedIps, ARDUINO_EVENT_WIFI_AP_STACONNECTED);		// Attach a callback to wifi event.
	WiFi.onEvent(updateConnectedIps, ARDUINO_EVENT_WIFI_AP_STADISCONNECTED);	// Here too.

	udpObj.begin(udpPortLocal);	// TODO: Only for rx.
}

void setup() {
	Serial.begin(115200);	// TODO: Serial in relese?
	udpSetup();
}

void loop() {
	#define packetTestSize 5
	uint8_t packetTest[packetTestSize] = "test";

	udpSendToMultiple(connectedIps, MAX_STATIONS, udpPortRemote, packetTest, packetTestSize);
	vTaskDelay(5000);

	if(updGetOneNewPacket(rxBuffer, RX_BUFFER_LEN) == 1) {
		Serial.print("Recieved: ");
		Serial.printf("%s\n", rxBuffer);
	}
}