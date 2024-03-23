#include "QRE1113.h"

QRE QRELeft('L');
QRE QRERight('R');
QRE QREBack('B');

void setup() {
	Serial.begin(115200);
	QRELeft.Threshold = 3000;
	QRERight.Threshold = 3000;
	QREBack.Threshold = 3000;
}

void loop() {
	Serial.printf("%i\n", QRELeft.get());
	Serial.printf("%i\n", QRERight.get());
	Serial.printf("%i\n", QREBack.get());
	delay(100);
}