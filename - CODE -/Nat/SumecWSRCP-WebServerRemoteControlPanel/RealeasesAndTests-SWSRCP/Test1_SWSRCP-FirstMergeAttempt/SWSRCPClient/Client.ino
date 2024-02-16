//...///////////////////
//..//    Imports    //
//.///////////////////
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

//...////////////////////
//..//    Settings    //
//.////////////////////
const char* SWSRCP_SSID = "SWSRCP#01";
const char* SWSRCP_PASSWORD = "3ac5c0cc-24bd-4d68-90b9-20d97ed3e080";
String HOST_NAME = "http://192.168.1.22";

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

String SWSRCPRequest(String Mode, String PATH_NAME, String QueryString) {
	Serial.println(Mode);
	Serial.println(PATH_NAME);
	Serial.println(QueryString);
	
	Serial.print("Sending " + String(Mode) + " request to: ");
	Serial.println(HOST_NAME);
	
	int httpCode;
	Serial.print("begin: ");
	Serial.println(HOST_NAME + "/" + PATH_NAME);
	http.begin(HOST_NAME + "/" + PATH_NAME); //HTTP
	if(Mode=="get") {
		int httpCode = http.GET();
	} else if(Mode=="post") {
		http.addHeader("Content-Type", "text/json");
		int httpCode = http.POST(QueryString);
	} else {
		return "";
	}
	
	Serial.print("httpCode: ");
	Serial.println(httpCode);
	httpCode = 200;
	Serial.print("httpCode: ");
	Serial.println(httpCode);
	
	// httpCode will be negative on error
	if(httpCode > 0) {
		// file found at server
		if(httpCode == HTTP_CODE_OK) {
			String payload = http.getString();
			Serial.println(payload);
			http.end();
			return payload;
		} else {
			// HTTP header has been send and Server response header has been handled
			Serial.print("[HTTP] " + String(Mode) + "... code: ");
			Serial.println(httpCode);
		}
	
	} else {
		Serial.print("[HTTP] " + String(Mode) + "... failed, error: ");
		Serial.println(http.errorToString(httpCode).c_str());
	}
	
	http.end();
	return "";
}

void setup() {
	Serial.begin(115200);
	delay(2000);
	Serial.begin(115200);
	delay(2000);
	Serial.println("START");
	Serial.println("Core [" + String(xPortGetCoreID()) + "]: ");
	
	ConnectToAP(SWSRCP_SSID, SWSRCP_PASSWORD);
}

void loop() {
	
	//get from server
	Serial.println("\nGET");
	DeserializationError error = deserializeJson(jsonDocument, SWSRCPRequest("get", "get", ""));	//get
	if(error) {
		Serial.println("Desr error (wrong mode?)");
	}
	else {
		const char* TestVal1 = jsonDocument["Test1"];
		const char* TestVal2 = jsonDocument["Test2"];
		
		Serial.println("recieved: ");
		Serial.println("Test1: " + String(TestVal1));
		Serial.println("Test2: " + String(TestVal2));
	}
	delay(5000);
	
	Serial.println("\nPOST");
	//post to server
	String buffer = "";
	JsonObject obj = jsonDocument2.to<JsonObject>();
	
	int VarMode = random(4);
	int VarTfL_Left = random(4096);
	int VarTfL_Mid = random(4096);
	int VarTfL_Right = random(4096);
	int VarSharp_Left = random(2);
	int VarSharp_Right = random(2);
	int VarQRE_Left = random(2);
	int VarQRE_Rear = random(2);
	int VarQRE_Right = random(2);
	int VarIR = random(65535);
	
	Serial.println("VarMode: " + String(VarMode));
	Serial.println("VarTfL_Left: " + String(VarTfL_Left));
	Serial.println("VarTfL_Mid: " + String(VarTfL_Mid));
	Serial.println("VarTfL_Right: " + String(VarTfL_Right));
	Serial.println("VarSharp_Left: " + String(VarSharp_Left));
	Serial.println("VarSharp_Right: " + String(VarSharp_Right));
	Serial.println("VarQRE_Left: " + String(VarQRE_Left));
	Serial.println("VarQRE_Rear: " + String(VarQRE_Rear));
	Serial.println("VarQRE_Right: " + String(VarQRE_Right));
	Serial.println("VarIR: " + String(VarIR));
	
	obj["Mode"] = String(VarMode);
	obj["TfL_Left"] = String(VarTfL_Left);
	obj["TfL_Mid"] = String(VarTfL_Mid);
	obj["TfL_Right"] = String(VarTfL_Right);
	obj["Sharp_Left"] = String(VarSharp_Left);
	obj["Sharp_Right"] = String(VarSharp_Right);
	obj["QRE_Left"] = String(VarQRE_Left);
	obj["QRE_Rear"] = String(VarQRE_Rear);
	obj["QRE_Right"] = String(VarQRE_Right);
	obj["IR"] = String(VarIR);
	
	serializeJson(jsonDocument2, buffer);
	
	
	error = deserializeJson(jsonDocument, SWSRCPRequest("post", "post", buffer));	//post
	if(error) {
		Serial.println("Desr error (wrong mode?)");
	}
	else {
		const char* TestVal1 = jsonDocument["Test1"];
		const char* TestVal2 = jsonDocument["Test2"];
		
		Serial.println("recieved: ");
		Serial.println("Test1: " + String(TestVal1));
		Serial.println("Test2: " + String(TestVal2));
	}
	delay(5000);
}