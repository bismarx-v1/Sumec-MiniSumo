#include "WiFiAPStuff.h"

char* SSID = "SUDPRCP_U#1";
char* PASSWORD = "018f34a5-6daa-7729-8ed0-884b8a7c6c45";

void setup() {
	Serial.begin(115200);

	WiFiAPStuff APObject;
	Serial.print(APObject.ConnAP(SSID, PASSWORD));

}

void loop() {
	
}
