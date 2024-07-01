//...///////////////////
//..//    Imports    //
//.///////////////////
#include <WiFi.h>

//.../////////////////////////////
//..//    APConnectSettings    //
//./////////////////////////////
const char* ConnectToSSID = "SWSRCP#01";
const char* ConnectToPASSWORD = "3ac5c0cc-24bd-4d68-90b9-20d97ed3e080";

void ConnectToAP(String ConnectToAP_SSID, String ConnectToAP_Password) {	//standard connect to AP using SSID and pass
	WiFi.begin(ConnectToAP_SSID, ConnectToAP_Password);
	Serial.println("Connecting");
	while(WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	
	Serial.print("\nConnected to WiFi network with IP Address: ");
	Serial.println(WiFi.localIP());
}

void setup() {
	Serial.begin(115200);
	ConnectToAP(ConnectToSSID, ConnectToPASSWORD);
}

void loop() {
	
}