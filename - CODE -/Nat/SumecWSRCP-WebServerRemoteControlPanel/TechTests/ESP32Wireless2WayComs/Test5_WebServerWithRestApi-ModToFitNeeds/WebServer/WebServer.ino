//...///////////////////
//..//    Imports    //
//.///////////////////
#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>

//...//////////////////////
//..//    APSettings    //
//.//////////////////////
const char* ssid = "SWSRCP#01";
const char* password = "3ac5c0cc-24bd-4d68-90b9-20d97ed3e080";
IPAddress local_IP(192,168,1,22);

//.../////////////////////////
//..//    Other defines    //
//./////////////////////////
WebServer server(80);


StaticJsonDocument<200> jsonDocument;
StaticJsonDocument<400> doc_rx;

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

void setup_routing() {
	server.on("/get", getAll);
	server.on("/post", HTTP_POST, postAll);
	
	server.begin();
}

void getAll() {	//"all" get request response

	Serial.println("GetAll");
	
	String buffer = "";
	JsonObject obj = jsonDocument.to<JsonObject>();
	
	int TestVal1 = random(256);
	int TestVal2 = random(256);
	Serial.println("TestVal1: " + String(TestVal1));
	Serial.println("TestVal2: " + String(TestVal2));
	
	obj["Test1"] = String(TestVal1);
	obj["Test2"] = String(TestVal2);
	
	serializeJson(jsonDocument, buffer);
	server.send(200, "application/json", buffer);
}

void postAll() {	//"all" post request response
	if (server.hasArg("plain") == false) {	//this is useless, but i'd rather keep it
	}
	String body = server.arg("plain");
	
	Serial.print("body: ");
	Serial.println(body);
	
	const char* payload;
	payload = body.c_str();
	
	Serial.print("payload: ");
	Serial.println(payload);
	
	DeserializationError error = deserializeJson(doc_rx, payload);
	if(error) {
		Serial.print("Desr error: ");
		Serial.println(error.c_str());
		
	}
	else {
		const char* VarMode = doc_rx["Mode"];
		const char* VarTfL_Left = doc_rx["TfL_Left"];
		const char* VarTfL_Mid = doc_rx["TfL_Mid"];
		const char* VarTfL_Right = doc_rx["TfL_Right"];
		const char* VarSharp_Left = doc_rx["Sharp_Left"];
		const char* VarSharp_Right = doc_rx["Sharp_Right"];
		const char* VarQRE_Left = doc_rx["QRE_Left"];
		const char* VarQRE_Rear = doc_rx["QRE_Rear"];
		const char* VarQRE_Right = doc_rx["QRE_Right"];
		const char* VarIR = doc_rx["IR"];
		
		Serial.println("recieved: ");
		Serial.println(VarMode);
		Serial.println(VarTfL_Left);
		Serial.println(VarTfL_Mid);
		Serial.println(VarTfL_Right);
		Serial.println(VarSharp_Left);
		Serial.println(VarSharp_Right);
		Serial.println(VarQRE_Left);
		Serial.println(VarQRE_Rear);
		Serial.println(VarQRE_Right);
		Serial.println(VarIR);
		Serial.println("rec end");
	}
	
	server.send(200, "application/json", body);
}

void setup() {
	Serial.begin(115200);
	delay(2000);
	Serial.println("START");
	
	Serial.println("Core [" + String(xPortGetCoreID()) + "]: ");
	SWSRCPWiFiConnect(ssid, password, local_IP);
	
	setup_routing();
}

void loop() {
	server.handleClient();
	delay(0.1);
}