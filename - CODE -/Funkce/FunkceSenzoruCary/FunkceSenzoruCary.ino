#include "line.h"

void setup() {
	Serial.begin(115200);
}



void loop() {
	Serial.println(LINE_Get(1, 3700, 0));
	Serial.println(LINE_Get(2, 3700, 0));
	//Serial.println(LINE_Get(3, 3500, 0));
	//Serial.println(LINE_Get(4, 3500, 0));
	Serial.println("------------------");
	Serial.println(LINE_Get(1, 0, 1));
	Serial.println(LINE_Get(2, 0, 1));
	//Serial.println(LINE_Get(3, 0, 1));
	//Serial.println(LINE_Get(4, 0, 1));
	Serial.println("====================");
	delay(500);
}
