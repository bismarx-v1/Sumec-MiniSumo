#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>
//#include <FreeRTOS.h>

const char *SSID = "[]";
const char *PWD = "[]";



WebServer server(80);


StaticJsonDocument<250> jsonDocument;
char buffer[250];

float temperature;
float humidity;
float pressure;

void setup_routing() {
	server.on("/temperature", getTemperature);
	server.on("/pressure", getPressure);
	server.on("/humidity", getHumidity);
	server.on("/data", getData);
	server.on("/led", HTTP_POST, handlePost);
	
	server.begin();
}

void create_json(char *tag, float value, char *unit) {
	jsonDocument.clear();
	jsonDocument["type"] = tag;
	jsonDocument["value"] = value;
	jsonDocument["unit"] = unit;
	serializeJson(jsonDocument, buffer);
}

void add_json_object(char *tag, float value, char *unit) {
	JsonObject obj = jsonDocument.createNestedObject();
	obj["type"] = tag;
	obj["value"] = value;
	obj["unit"] = unit;
}

/*void read_sensor_data(void * parameter) {
	for (;;) {
		temperature = random(256);
		humidity = random(256);
		pressure = random(256) / 100;
		Serial.print("Core [" + String(xPortGetCoreID()) + "]: ");
		Serial.println("Read sensor data: " + String(temperature) + ", " + String(humidity) + ", " + String(pressure));
		
		vTaskDelay(5000 / portTICK_PERIOD_MS);
	}
}*/

void CustonGetData() {
	temperature = random(256);
	humidity = random(256);
	pressure = random(256) / 100;
	Serial.print("Core [" + String(xPortGetCoreID()) + "]: ");
	Serial.println("Read sensor data: " + String(temperature) + ", " + String(humidity) + ", " + String(pressure));
}


void getTemperature() {
	Serial.println("Get temperature");
	create_json("temperature", temperature, "°C");
	server.send(200, "application/json", buffer);
}

void getHumidity() {
	Serial.println("Get humidity");
	create_json("humidity", humidity, "%");
	server.send(200, "application/json", buffer);
}

void getPressure() {
	Serial.println("Get pressure");
	create_json("pressure", pressure, "hPa");
	server.send(200, "application/json", buffer);
}

void getData() {
	CustonGetData();
	Serial.println("Get BME280 Sensor Data");
	jsonDocument.clear();
	add_json_object("temperature", temperature, "°C");
	add_json_object("humidity", humidity, "%");
	add_json_object("pressure", pressure, "hPa");
	serializeJson(jsonDocument, buffer);
	server.send(200, "application/json", buffer);
}

void handlePost() {
	if (server.hasArg("plain") == false) {
	}
	String body = server.arg("plain");
	deserializeJson(jsonDocument, body);
	
	int red_value = jsonDocument["red"];
	int green_value = jsonDocument["green"];
	int blue_value = jsonDocument["blue"];
	
	Serial.println(red_value);
	Serial.println(green_value);
	Serial.println(blue_value);
	
	server.send(200, "application/json", "{}");
}

/*void setup_task() {
	xTaskCreate(
	read_sensor_data,
	"Read sensor data",
	1000,
	NULL,
	1,
	NULL
	);
}*/

void setup() {
	Serial.begin(115200);
	
	Serial.print("Core [" + String(xPortGetCoreID()) + "]: ");
	
	Serial.print("Connecting to Wi-Fi");
	WiFi.begin(SSID, PWD);
	while (WiFi.status() != WL_CONNECTED) {
		Serial.print(".");
		delay(500);
	}

	Serial.print("Connected! IP Address: ");
	Serial.println(WiFi.localIP());
	//setup_task();
	setup_routing();
}

void loop() {
	server.handleClient();
}