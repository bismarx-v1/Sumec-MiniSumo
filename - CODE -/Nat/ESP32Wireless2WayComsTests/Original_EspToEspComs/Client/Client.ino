/* WiFi Peer-to-Peer example, Receiver Sketch
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

#include <SerLCD.h> //Click here to get the library: http://librarymanager/All#SparkFun_SerLCD
SerLCD lcd; // Initialize the library with default I2C address 0x72


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

  Wire.begin();
  //********** Setup for LCD display**********//
  lcd.begin(Wire); //Set up the LCD for I2C communication

  lcd.setBacklight(50, 55, 255); //Set backlight to bright white
  lcd.setContrast(5); //Set contrast. Lower to 0 for higher contrast.

  lcd.clear(); //Clear the display - this moves the cursor to home position as well
  lcd.print(" Current Conditions");
  lcd.setCursor(0, 1);
  lcd.print("Temperature: ");
  lcd.setCursor(0,2);
  lcd.print("Humidity: ");
  lcd.setCursor(0,3);
  lcd.print("Pressure: ");

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
  Serial.print("Temperature F: ");
  Serial.println(myData.a);
  Serial.print("Humidity: ");
  Serial.println(myData.b);
  Serial.print("Pressure: ");
  Serial.println(myData.c);
  Serial.println();
  lcd.setCursor(13, 1);
  lcd.print(String(myData.a) + (char)223 + " F");
  lcd.setCursor(13, 2);
  lcd.print(String(myData.b) + (char)37);
  lcd.setCursor(13, 3);
  lcd.print(String(myData.c, 1)); // The comma followed bt 1 limits output to 1 decimal place

}
