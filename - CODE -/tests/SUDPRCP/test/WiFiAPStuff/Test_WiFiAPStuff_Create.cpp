#include "WiFiAPStuff.h"

char* SSID = "SUDPRCP_U#1";
char* PASSWORD = "018f34a5-6daa-7729-8ed0-884b8a7c6c45";
IPAddress IP = {192,168,1,22};

void setup() {
	Serial.begin(115200);

	WiFiAPStuff APObject;
	APObject.InitAP(SSID, PASSWORD, IP);

}

void loop() {
	
}
