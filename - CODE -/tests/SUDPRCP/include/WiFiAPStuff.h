#ifndef SUDPRCP_LIB
#define SUDPRCP_LIB

#include <WiFi.h>

/**
 * @brief Class for creating or connecting to a WiFi Access Point on the ESP. Disable compilation of this lib by using "#define SUDPRCP_LIB" before it's include.
*/
class WiFiAPStuff {
	public:
		WiFiAPStuff();
		void InitAP(char* Ssid, char* Password, IPAddress EspIp);
		IPAddress ConnAP(char* Ssid, char* Password);
		uint16_t TIMEOUT_LEN = 60000;	// time in ms before timeout error. probably won't work because the WiFi.h lib most likely has it's own timeout timer, but better than an inf loop.
	private:
		uint8_t TIMEOUT_ERR = 1;	// code for timeout err
};

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

#endif