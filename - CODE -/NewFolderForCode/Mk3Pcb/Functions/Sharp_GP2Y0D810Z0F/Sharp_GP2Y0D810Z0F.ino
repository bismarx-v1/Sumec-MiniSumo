#include "Sharp_GP2Y0D810Z0F.h"

Sharp SharpLeft('L');
Sharp SharpRight('R');

void setup() {
	Serial.begin(115200);
}

void loop() {
	Serial.printf("%i\n", SharpLeft.get());
	Serial.printf("%i\n", SharpRight.get());
	delay(100);
}