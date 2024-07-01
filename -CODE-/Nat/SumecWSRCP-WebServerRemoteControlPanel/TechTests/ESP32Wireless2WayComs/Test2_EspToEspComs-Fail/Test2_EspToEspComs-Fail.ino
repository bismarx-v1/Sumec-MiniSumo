#include <esp_now.h>
#include <WiFi.h>
#include <ArduinoJson.h>


StaticJsonDocument<200> doc_tx;
StaticJsonDocument<200> doc_rx;


uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

/*
String jsonString = "";
JsonObject object = doc_tx.to<JsonObject>();

object[Name] = Value;

serializeJson(doc_tx, jsonString);	//ENCODE; input doc_tx; output jsonString
*/

/*
DeserializationError error = deserializeJson(doc_rx, payload);	//DECODE; input payload; output doc_rx
if(error) {
	Serial.println("Desr error");
	return;
}
else {
	const char* Value = doc_rx["Name"];
}
*/

esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void OnDataRecv(const uint8_t * mac, const uint8_t *payload, int len) {
	//memcpy(&payload, incomingData, sizeof(payload));
	
	Serial.print("Bytes received: ");
	Serial.println(len);
	
	DeserializationError error = deserializeJson(doc_rx, payload);	//DECODE; input payload; output doc_rx
	if(error) {
		Serial.println("Desr error");
		return;
	}
	else {
		const char* RecTestVal1 = doc_rx["ObjectTestVal1"];
		const char* RecTestVal2 = doc_rx["ObjectTestVal2"];
		
		Serial.print("RecVal1: ");
		Serial.println(RecTestVal1);
		Serial.print("RecVal2: ");
		Serial.println(RecTestVal2);
	}
}

void setup() {
	Serial.begin(115200);
	Serial.print("Local Mac: ");
	Serial.println(WiFi.macAddress());
	if(WiFi.macAddress()=={0xb0,0xa7,0x32,0xf3,0x7b,0xf8}) {
		broadcastAddress[] = {0xa0,0xa3,0xb3,0xfe,0xd9,0xbc};	//newer
		Serial.println("Older board");
	} else if(WiFi.macAddress()=={0xa0,0xa3,0xb3,0xfe,0xd9,0xbc}) {
		broadcastAddress[] = {0xb0,0xa7,0x32,0xf3,0x7b,0xf8};	//older
		Serial.println("Newer board");
	} else {
		Serial.println("Unknown MAC");
	}
	
	WiFi.mode(WIFI_STA);
	
	if (esp_now_init() != ESP_OK) {
		Serial.println("Error initializing ESP-NOW");
		return;
	}
	
	esp_now_register_send_cb(OnDataSent);
	
	esp_now_register_recv_cb(OnDataRecv);
	
	memcpy(peerInfo.peer_addr, broadcastAddress, 6);
	peerInfo.channel = 0;  
	peerInfo.encrypt = false;
	
	RetryPair:
	
	if (esp_now_add_peer(&peerInfo) != ESP_OK){
		Serial.println("Failed to add peer");
		delay(1000);
		goto RetryPair;
	}
}

void loop() {
	String jsonString = "";
	JsonObject object = doc_tx.to<JsonObject>();
	
	SendTestVal1 = random(10)
	SendTestVal2 = random(10)
	
	Serial.print("SendVal1: ");
	Serial.println(SendTestVal1);
	Serial.print("SendVal2: ");
	Serial.println(SendTestVal2);

	object["ObjectTestVal1"] = SendTestVal1;
	object["ObjectTestVal2"] = SendTestVal2;
	
	serializeJson(doc_tx, jsonString);	//ENCODE; input doc_tx; output jsonString
	
	
	esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &jsonString, sizeof(jsonString));	//send
	if(result == ESP_OK) {
		Serial.println("Sent with success");
	} else {
		Serial.println("Error sending the data");
	}
	
	delay(5000);
}