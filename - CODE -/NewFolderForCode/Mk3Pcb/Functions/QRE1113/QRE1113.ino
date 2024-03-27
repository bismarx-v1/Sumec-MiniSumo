#include "QRE1113.h"

QRE QRELeft('L');	// Create object for left sensor
QRE QRERight('R');	// Create object for right sensor
QRE QREBack('B');	// Create object for rear sensor

void setup() {
	Serial.begin(115200);
	QRELeft.Threshold = 3500;	// Default threshold is 3000, but this can override it
	QRERight.Threshold = 3500;	// Default threshold is 3000, but this can override it
	QREBack.Threshold = 3500;	// Default threshold is 3000, but this can override it
}

void loop() {
	Serial.printf("Left: %i\t", QRELeft.get());		// Get and print left value
	Serial.printf("Left: %i\t", QRELeft.getRaw());		// Get and print left value - raw
	Serial.printf("Rear: %i\t", QREBack.get());		// Get and print rear value
	Serial.printf("Rear: %i\t", QREBack.getRaw());		// Get and print rear value - raw
	Serial.printf("Right: %i\t", QRERight.get());	// Get and print right value
	Serial.printf("Right: %i\n", QRERight.getRaw());	// Get and print right value - raw
	delay(200);
}