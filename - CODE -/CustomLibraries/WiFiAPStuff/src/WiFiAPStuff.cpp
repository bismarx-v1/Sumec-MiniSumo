#include "WiFiAPStuff.h"

// constructor
WiFiAPStuff::WiFiAPStuff() {}

/**
 * @brief This method creates a WiFi Access Point on the ESP. 
 * @param Ssid Name of the AP - type:"char*" - ex.: "SUDPRCP_U#1"
 * @param Password Pass for the AP - type:"char*" - ex.: "018f34a5-6daa-7729-8ed0-884b8a7c6c45"
 * @param EspIp IP address of the ESP - type:"uint8_t <ArrayName>[4]" - ex.: {192,168,1,22}
*/
void WiFiAPStuff::InitAP(char* Ssid, char* Password, IPAddress EspIp) {
	IPAddress gateway(192,168,1,5);
	IPAddress subnet(255,255,255,0);

	WiFi.softAPConfig(EspIp, gateway, subnet);	// Set up AP
	WiFi.softAP(Ssid, Password);			// Start up AP
}

/**
 * @brief This method creates a WiFi Access Point on the ESP. 
 * @param Ssid Name of the AP - type:"char*" - ex.: "SUDPRCP_U#1"
 * @param Password Pass for the AP - type:"char*" - ex.: "018f34a5-6daa-7729-8ed0-884b8a7c6c45"
 * @returns Local IP Address on the connected network, returns [TIMEOUT_ERR] if it reaches timeout - type:"IPAddress"
*/
IPAddress WiFiAPStuff::ConnAP(char* Ssid, char* Password) {
	WiFi.begin(Ssid, Password);
	uint16_t TimeoutStart = millis();
	while(WiFi.status() != WL_CONNECTED) {
		delay(10);
		if(TimeoutStart + TIMEOUT_LEN <= millis()) {
			return(TIMEOUT_ERR);
		}
	}
	
	return(WiFi.localIP());
}