/* WiFi Peer-to-Peer example, Transmitter Sketch
 * Rob Reynolds, SparkFun Electronics, November 2021
 * This example uses a pair of SparkFun ESP32 Thing Plus Wroom modules
 * (https://www.sparkfun.com/products/15663, a SparkFun Qwiic Environmental
 * Combo Breakout (https://www.sparkfun.com/products/14348), and a SparkFun
 * Qwiic 20x4 SerLCD - RGB Backlight (https://www.sparkfun.com/products/16398).
 * 
 * Feel like supporting our work? Buy a board from SparkFun!
 * https://www.sparkfun.com/
 * 
 * License: MIT. See license file for more information but you can
 * basically do whatever you want with this code.
 * 
 * Based on original code by 
 * Rui Santos
 * Complete project details at https://RandomNerdTutorials.com/esp-now-esp32-arduino-ide/
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files.
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
*/

#include <esp_now.h>
#include <WiFi.h>

#include <Wire.h>            // Used to establish serial communication on the I2C bus
#include "SparkFunBME280.h"  // Install library for the BME280
BME280 mySensor;             // Define sensor


// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

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

  //**********Setup for BME280 module**********//
  if (mySensor.beginI2C() == false) //Begin communication over I2C
  {
    Serial.println("The sensor did not respond. Please check wiring.");
    while(1); //Freeze
  }  

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

  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  // Set values to send
  //strcpy(myData.a, "THIS IS A CHAR");
  myData.a = (mySensor.readTempF());
  myData.b = (mySensor.readFloatHumidity());
  myData.c = (mySensor.readFloatPressure());

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
