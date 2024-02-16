//...///////////////////
//..//    Imports    //
//.///////////////////
#include <WiFi.h>

//...//////////////////////
//..//    APSettings    //
//.//////////////////////
const char* ssid = "SWSRCP#01";
const char* password = "3ac5c0cc-24bd-4d68-90b9-20d97ed3e080";
IPAddress local_IP(192,168,1,22);

void SWSRCPWiFiConnect(String SetupAP_LocalIP, String SetupAP_Password, IPAddress SetupAP_IP) {	//Set up an AP WiFi
	IPAddress gateway(192,168,1,5);
	IPAddress subnet(255,255,255,0);
	
	Serial.print("Setting up AP. ");
	Serial.println(WiFi.softAPConfig(SetupAP_IP, gateway, subnet)?"Passed":"Failed");
	
	Serial.print("Starting the AP. ");
	Serial.println(WiFi.softAP(SetupAP_LocalIP, SetupAP_Password)?"Passed":"Failed");
	
	Serial.println("======================");
	Serial.print("SSID: ");
	Serial.println(SetupAP_LocalIP);
	Serial.println("----------------------");
	Serial.print("Pass: ");
	Serial.println(SetupAP_Password);
	Serial.println("----------------------");
	Serial.print("IP: ");
	Serial.println(WiFi.softAPIP());
	Serial.println("======================");
}

void setup() {
	Serial.begin(115200);
	SWSRCPWiFiConnect(ssid, password, local_IP);
}

void loop() {
	
}