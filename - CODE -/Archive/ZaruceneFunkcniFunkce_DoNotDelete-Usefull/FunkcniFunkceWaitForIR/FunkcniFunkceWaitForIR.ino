#include "IR.h"

void setup() {
	Serial.begin(115200);
	Serial.println("Loaded");
}

void loop() {
	IR_Wait();
	Serial.println(millis());
}