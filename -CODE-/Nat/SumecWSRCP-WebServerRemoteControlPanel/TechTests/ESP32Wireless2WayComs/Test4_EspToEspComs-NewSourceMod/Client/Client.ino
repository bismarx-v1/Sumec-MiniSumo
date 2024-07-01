#include <esp_now.h>
#include <WiFi.h>

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
		float a;
		float b;
		float c;
		float d;
} struct_message;

// Create a struct_message called myData
struct_message myData;



void setup() {
	// Initialize Serial Monitor
	Serial.begin(115200);

	// Set device as a Wi-Fi Station
	WiFi.mode(WIFI_STA);


	// Init ESP-NOW
	if (esp_now_init() != ESP_OK) {
		Serial.println("Error initializing ESP-NOW");
		return;
	}

	// Once ESPNow is successfully Init, we will register for recv CB to
	// get recv packer info
	esp_now_register_recv_cb(OnDataRecv);
}

void loop() {

}



// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
	memcpy(&myData, incomingData, sizeof(myData));

	// Use this for testing in Serial Monitor if you're not seeing anything on the LCD display 
	Serial.print("Line1: ");
	Serial.println(myData.a);
	Serial.print("Line2: ");
	Serial.println(myData.b);
	Serial.print("Line3: ");
	Serial.println(myData.c);
	Serial.println();
}
