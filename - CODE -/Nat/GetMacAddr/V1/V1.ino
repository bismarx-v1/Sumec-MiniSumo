/*
 * MAC Address Finder
 * Run this on each of your WiFi-enabled
 * boards to get their MAC addresses, so
 * you can plug them into your code,
 * allowing your components to connect
 * on power-up or after power-cycling
 * without the need for any intervention!
 * 
 * Once you've uploaded the code, open
 * the Serial Monitor, hit the reset
 * button on your board, and write down
 * the MAC address.
 * (I use a label maker to put the MAC
 * address on the back of each board.)
 */

#include "WiFi.h"

void setup(){
  Serial.begin(115200);

}

void loop(){
  WiFi.mode(WIFI_STA);
  Serial.print("The MAC address for this board is: ");
  Serial.println(WiFi.macAddress());
  while(1){     // This holds the loop, so it doesn't 
    }           // print the info a million times.
}
