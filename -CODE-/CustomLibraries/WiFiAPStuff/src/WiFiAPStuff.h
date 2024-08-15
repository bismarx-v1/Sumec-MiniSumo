#ifndef _WIFI_AP_STUFF
#define _WIFI_AP_STUFF

#include <Arduino.h>

#include <WiFi.h>

/**
 * @brief Class for creating or connecting to a WiFi Access Point on the ESP. Disable compilation of this lib by using "#define _WIFI_AP_STUFF" before it's include.
*/
class WiFiAPStuff {
	public:
		WiFiAPStuff();
		void InitAP(char* Ssid, char* Password, IPAddress EspIp);
		IPAddress ConnAP(char* Ssid, char* Password);
		uint16_t TIMEOUT_LEN = 60000;	// time in ms before timeout error. probably won't work because the WiFi.h lib most likely has it's own timeout timer, but better than an inf loop.
		const uint8_t TIMEOUT_ERR = 1;	// code for timeout err
};

#endif