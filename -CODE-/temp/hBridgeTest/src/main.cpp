#include <Arduino.h>


#define nSleep 25	// nSleep in schematic
#define ina 26		// in1 in schematic
#define inb 27		// pwm in schematic



void set() {
	pinMode(nSleep, OUTPUT);
	pinMode(ina, OUTPUT);
	pinMode(inb, OUTPUT);
}

void fwd() {
	digitalWrite(nSleep, 1);
	digitalWrite(ina, 1);
	digitalWrite(inb, 1);
}

void bwd() {
	digitalWrite(nSleep, 1);
	digitalWrite(ina, 0);
	digitalWrite(inb, 1);
}

void stp() {
	digitalWrite(nSleep, 1);
	digitalWrite(inb, 0);
}


void setup() {
	set();
}

void loop() {
	fwd();
	delay(10000);
	stp();
	delay(10000);
	bwd();
	delay(10000);
	stp();
	delay(10000);
}