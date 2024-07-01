void setup() {
	Serial.begin(115200);
	pinMode(47, OUTPUT);
	pinMode(48, OUTPUT);
}

void loop() {
	Serial.println("FFF");
	digitalWrite(47, 1);
	digitalWrite(48, 0);
	delay(100);
	digitalWrite(47, 0);
	digitalWrite(48, 1);
	delay(100);

}