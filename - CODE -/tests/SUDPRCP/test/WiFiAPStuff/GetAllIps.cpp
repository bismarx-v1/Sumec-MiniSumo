#if 1	// get all ips
#include <WiFi.h>
#include "esp_wifi.h"

void setup() { 
	Serial.begin(115200);
	WiFi.softAP("MyESP32AP");
}

void loop() {
	wifi_sta_list_t wifi_sta_list;  tcpip_adapter_sta_list_t adapter_sta_list;
	memset(&wifi_sta_list, 0, sizeof(wifi_sta_list));
	memset(&adapter_sta_list, 0, sizeof(adapter_sta_list));
	esp_wifi_ap_get_sta_list(&wifi_sta_list);
	tcpip_adapter_get_sta_list(&wifi_sta_list, &adapter_sta_list);
	for (int i = 0; i < adapter_sta_list.num; i++) {
		tcpip_adapter_sta_info_t station = adapter_sta_list.sta[i];
		Serial.print("station nr ");
		Serial.println(i);
		Serial.print("MAC: ");
		for(int i = 0; i< 6; i++) {
			Serial.printf("%02X", station.mac[i]);
			if(i<5) {
				Serial.print(":");
			}
		}

		Serial.print("\nIP: ");
		#if 0
		Serial.println(ip4addr_ntoa(&(station.ip)));
		#else
		char ip[IP4ADDR_STRLEN_MAX];
		esp_ip4addr_ntoa(&station.ip, ip, IP4ADDR_STRLEN_MAX);
		Serial.println(ip);
		#endif

	}

	Serial.println("-----------");
	delay(5000);
}
#endif