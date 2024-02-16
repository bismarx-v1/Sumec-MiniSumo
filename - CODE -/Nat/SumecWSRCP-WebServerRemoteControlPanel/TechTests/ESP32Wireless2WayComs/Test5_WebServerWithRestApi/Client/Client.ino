/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-http-request
 */

#include <WiFi.h>
#include <HTTPClient.h>

const char WIFI_SSID[] = "[]";
const char WIFI_PASSWORD[] = "[]";

String HOST_NAME	 = "http://192.168.0.109";
String PATH_NAME	 = "/data";

void setup() {
	Serial.begin(115200); 

	WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
	Serial.println("Connecting");
	while(WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println("");
	Serial.print("Connected to WiFi network with IP Address: ");
	Serial.println(WiFi.localIP());
	
	HTTPClient http;
	
	Request:
	
	Serial.print("Sending request to: ");
	Serial.println(HOST_NAME);
	
	http.begin(HOST_NAME + PATH_NAME); //HTTP
	int httpCode = http.GET();

	// httpCode will be negative on error
	if(httpCode > 0) {
		// file found at server
		if(httpCode == HTTP_CODE_OK) {
			String payload = http.getString();
			Serial.println(payload);
		} else {
			// HTTP header has been send and Server response header has been handled
			Serial.printf("[HTTP] GET... code: %d\n", httpCode);
		}
	} else {
		Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
	}
	
	http.end();
	delay(5000);
	goto Request;
}

void loop() {
	
}
