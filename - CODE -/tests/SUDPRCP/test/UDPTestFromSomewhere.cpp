#if 0
#include <WiFi.h>
#include <WiFiUdp.h>

/* WiFi network name and password */
const char * ssid = ".....";
const char * pwd = ".....";

// IP address to send UDP data to.
// it can be ip address of the server or 
// a network broadcast address
// here is broadcast address
const char * udpAddress = "73.180.146.22";
const int udpPort = 3333;

//create UDP instance
WiFiUDP udp;

void setup(){
  Serial.begin(115200);
  
  //Connect to the WiFi network
   WiFi.begin(ssid, pwd);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  //This initializes udp and transfer buffer
  udp.begin(udpPort);
}

void loop(){
  //data will be sent to server
  uint8_t buffer[50] = "hello world";
  //send hello world to server
  udp.beginPacket(udpAddress, udpPort);
  udp.write(buffer, 11);
  udp.endPacket();
  memset(buffer, 0, 50);
  //processing incoming packet, must be called before reading the buffer
  udp.parsePacket();
  //receive response from server, it will be HELLO WORLD
  if(udp.read(buffer, 50) > 0){
    Serial.print("Server to client: ");
    Serial.println((char *)buffer);
  }
  //Wait for 1 second
  delay(1000);
}

#endif
//==============================================================
#if 1

#include <WiFi.h>
#include <WiFiUdp.h>

uint32_t Time = 0;
uint8_t buffer[50];

/* WiFi network name and password */
const char* ssid = "Nat's pc";
const char* pwd = "********";

// IP address to send UDP data to.
// it can be ip address of the server or 
// a network broadcast address
// here is broadcast address
const char* udpAddress = "192.168.0.106";
const int udpPort = 3333;

//create UDP instance
WiFiUDP udp;

void setup() {
	Serial.begin(115200);
	
	//Connect to the WiFi network
	 WiFi.begin(ssid, pwd);
	Serial.println("");

	// Wait for connection
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println("");
	Serial.print("Connected to ");
	Serial.println(ssid);
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
	//This initializes udp and transfer buffer
	udp.begin(udpPort);
}

void loop() {
	//data will be sent to server
	//uint8_t buffer[50] = "hello world";
	
	for(int i = 0; i <= 50-1; i++) {
		buffer[i] = 0;
	}

	Time = millis();
	for(int i = 32-1; i >= 0; i--) {
		buffer[i] = Time%10+48;
		Time = Time/10;
	}
	

	//send hello world to server
	udp.beginPacket(udpAddress, udpPort);
	udp.write(buffer, 32);
	udp.endPacket();
	memset(buffer, 0, 50);
	//processing incoming packet, must be called before reading the buffer
	udp.parsePacket();
	//receive response from server, it will be HELLO WORLD
	if(udp.read(buffer, 50) > 0){
		Serial.print("Server to client: ");
		Serial.println((char*)buffer);
	}
	//Wait for 1 second
	delay(1000);
}

#endif