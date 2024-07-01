#include <esp_now.h>
#include <WiFi.h>

#include <Wire.h>						// Used to establish serial communication on the I2C bus					 // Define sensor


// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0xb0,0xa7,0x32,0xf3,0x7b,0xf8};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
	float a;
	float b;
	float c;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
	Serial.print("\r\nLast Packet Send Status:\t");
	Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
	Serial.begin(115200);
	Serial.println("Reading basic values from BME280");

	Wire.begin();	

	// Set device as a Wi-Fi Station
	WiFi.mode(WIFI_STA);

	// Init ESP-NOW
	if (esp_now_init() != ESP_OK) {
		Serial.println("Error initializing ESP-NOW");
		return;
	}

	// Once ESPNow is successfully Init, we will register for Send CB to
	// get the status of Trasnmitted packet
	esp_now_register_send_cb(OnDataSent);

	// Register peer
	esp_now_peer_info_t peerInfo;
	memcpy(peerInfo.peer_addr, broadcastAddress, 6);
	peerInfo.channel = 0;	
	peerInfo.encrypt = false;
	
	RetryAddPeer:
	// Add peer				
	if (esp_now_add_peer(&peerInfo) != ESP_OK){
		Serial.println("Failed to add peer");
		delay(1000);
		goto RetryAddPeer;
	}
}

void loop() {
	// Set values to send
	//strcpy(myData.a, "THIS IS A CHAR");
	myData.a = (millis());
	myData.b = (random(2));
	myData.c = (random(256));

	// Send message via ESP-NOW
	esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

	// The following is only used for testing, to check data in Serial Monitor
	Serial.print("Temperature in Fahrenheit: ");
	Serial.println(myData.a);
	Serial.print("Humidity: ");
	Serial.println(myData.b);
	Serial.print("Pressure: ");
	Serial.println(myData.c);

	if (result == ESP_OK) {
		Serial.println("Sent with success");
	}
	else {
		Serial.println("Error sending the data");
	}
	delay(2000); // Send data every two seconds
}
