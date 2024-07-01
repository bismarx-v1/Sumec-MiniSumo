//...///////////////////
//..//		Imports		//
//.///////////////////
#include <esp_now.h>
#include <WiFi.h>

//...////////////////////
//..//		Settings		//
//.////////////////////
uint8_t broadcastAddress[] = {0xb0,0xa7,0x32,0xf3,0x7b,0xf8};	//MAC Addr of reciever goes here


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
	Serial.println(ESP_NOW_SEND_SUCCESS);
}

void setup() {
	Serial.begin(115200);
	delay(2000);
	Serial.print("Local Mac: ");
	Serial.println(WiFi.macAddress());

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

	// Print Rec MAC Addr
	Serial.print("Connecting to: ");
	for(int i = 0; i <= 5; i++) {
		Serial.print(broadcastAddress[i], HEX);
		if(i!=5) {
			Serial.print(":");
		}
	}
	
	Serial.print("\r\n");
	
	// Register peer
	esp_now_peer_info_t peerInfo;
	memcpy(peerInfo.peer_addr, broadcastAddress, 6);
	peerInfo.channel = 0;	
	peerInfo.encrypt = false;

	RetryAddPeed:
	// Add peer				
	if (esp_now_add_peer(&peerInfo) != ESP_OK){
		Serial.println("Failed to add peer");
		delay(1000);
		goto RetryAddPeed;
	}
}

void loop() {
	// Set values to send
	//strcpy(myData.a, "THIS IS A CHAR");
	myData.a = (millis());
	myData.b = (random(2));
	myData.c = (1);

	// Send message via ESP-NOW
	esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

	// The following is only used for testing, to check data in Serial Monitor
	Serial.print("myData.a: ");
	Serial.println(myData.a);
	Serial.print("myData.b: ");
	Serial.println(myData.b);
	Serial.print("myData.c: ");
	Serial.println(myData.c);

	if (result == ESP_OK) {
		Serial.println("Sent with success");
	}
	else {
		Serial.println("Error sending the data");
	}
	delay(2000); // Send data every two seconds
}
