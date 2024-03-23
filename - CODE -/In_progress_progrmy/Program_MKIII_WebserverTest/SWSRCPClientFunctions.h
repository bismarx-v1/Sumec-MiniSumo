//...///////////////////
//..//    Imports    //
//.///////////////////
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

//.../////////////////////////
//..//    Other defines    //
//./////////////////////////
HTTPClient http;

StaticJsonDocument<400> jsonDocument;
StaticJsonDocument<400> jsonDocument2;

void ConnectToAP(String SSID, String Password) {	//standard connect to AP using SSID and pass
	Serial.println("Connecting to " + String(SSID));
	WiFi.begin(SSID, Password);
	while(WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	
	Serial.print("\nConnected to WiFi network with IP Address: ");
	Serial.println(WiFi.localIP());
}

String SWSRCPRequest(String Mode, String PATH_NAME, String QueryString, String Func_HOST_NAME) {
	//Serial.println(Mode);
	//Serial.println(PATH_NAME);
	//Serial.println(QueryString);
	
	//Serial.print("Sending " + String(Mode) + " request to: ");
	//Serial.println(Func_HOST_NAME);
	
	int httpCode;
	//Serial.print("begin: ");
	//Serial.println(Func_HOST_NAME + "/" + PATH_NAME);
	http.begin(Func_HOST_NAME + "/" + PATH_NAME); //HTTP
	if(Mode=="get") {
		int httpCode = http.GET();
	} else if(Mode=="post") {
		http.addHeader("Content-Type", "text/json");
		int httpCode = http.POST(QueryString);
	} else {
		return "wrong mode";
	}
	
	//Serial.print("httpCode: ");
	//Serial.println(httpCode);
	httpCode = 200;	//the functions is not working as docs describe so this fix works. definetly can be made better and less stupid
	//Serial.print("httpCode: ");
	//Serial.println(httpCode);
	
	// httpCode will be negative on error
	if(httpCode > 0) {
		// file found at server
		if(httpCode == HTTP_CODE_OK) {
			String payload = http.getString();
			//Serial.println(payload);
			http.end();
			return payload;
		} else {
			// HTTP header has been send and Server response header has been handled
			//Serial.print("[HTTP] " + String(Mode) + "... code: ");
			//Serial.println(httpCode);
		}
	
	} else {
		//Serial.print("[HTTP] " + String(Mode) + "... failed, error: ");
		//Serial.println(http.errorToString(httpCode).c_str());
	}
	
	http.end();
	return "error";
}