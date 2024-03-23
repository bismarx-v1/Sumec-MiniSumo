#include "QRE1113.h"

QRE QRELeft('L');	// Create object for left sensor
QRE QRERight('R');	// Create object for right sensor
QRE QREBack('B');	// Create object for rear sensor

void setup() {
	Serial.begin(115200);
	QRELeft.Threshold = 3001;	// Default threshold is 3000, but this can override it
	QRERight.Threshold = 3001;	// Default threshold is 3000, but this can override it
	QREBack.Threshold = 3001;	// Default threshold is 3000, but this can override it
}

void loop() {
	Serial.printf("Left: %i\n", QRELeft.get());		// Get and print left value
	Serial.printf("Rear: %i\n", QREBack.get());		// Get and print rear value
	Serial.printf("Right: %i\n", QRERight.get());	// Get and print right value
	delay(100);
}