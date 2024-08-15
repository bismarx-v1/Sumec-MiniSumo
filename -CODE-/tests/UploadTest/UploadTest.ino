#include <arduino.h>
#define ledpin 1
uint8_t led = 0;

void setup() {
	pinMode(ledpin, OUTPUT);
}

void loop() {
	led = 1- led;
	digitalWrite(ledpin, led);
	delay(500);
}