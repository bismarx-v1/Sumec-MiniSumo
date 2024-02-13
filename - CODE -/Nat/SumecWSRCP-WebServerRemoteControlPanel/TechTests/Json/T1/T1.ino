#include <ArduinoJson.h>



void setup() {
	Serial.begin(115200);
	delay(2000);
	/*String SerialJson;

	doc["sensor"] = "gps";
	doc["time"] = round(random(10));
	
	serializeJson(doc, Serial);
	
	deserializeJson(doc2, Serial);

	const char* sensor2 = doc2["sensor"];
	long time2 = doc2["time"];
	double latitude2 = doc2["data"][0];
	double longitude2 = doc2["data"][1];
	
	Serail.println("sensor2 = " + String(sensor2));
	Serail.println("time2 = " + String(time2));
	Serail.println("latitude2 = " + String(latitude2));
	Serail.println("longitude2 = " + String(longitude2));*/
	
	StaticJsonDocument<400> doc_tx;
	
	String TestVal1 = "";

	TestVal1 = doc_tx["Test1"] = 64;
	Serial.println(TestVal1);
	TestVal1 = doc_tx["Test2"] = "Test2";
	Serial.println(TestVal1);
	TestVal1 = doc_tx;
	Serial.println(TestVal1);
	
	
	

}