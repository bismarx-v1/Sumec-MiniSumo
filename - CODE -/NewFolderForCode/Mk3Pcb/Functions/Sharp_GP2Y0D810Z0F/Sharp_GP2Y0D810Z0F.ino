#include "Sharp_GP2Y0D810Z0F.h"

Sharp SharpLeft('L');	// Create object for left sensor
Sharp SharpRight('R');	// Create object for right sensor

void setup() {
	Serial.begin(115200);
}

void loop() {
	Serial.printf("Left: %i\t", SharpLeft.get());		// Get and print left value
	Serial.printf("Right: %i\n", SharpRight.get());		// Get and print right value
	delay(500);
}