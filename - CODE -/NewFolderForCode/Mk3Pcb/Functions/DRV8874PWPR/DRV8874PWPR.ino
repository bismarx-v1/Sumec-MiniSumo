#include "DRV8874PWPR.h"

DRV8874PWPR DRV8874PWPR_Obj(5000, 8, 0, 1);	// Values are uint16_t[LedcFrequency], uint8_t[LedcResolutionInBits], uint8_t[LedcChannelForLeftMotor], uint8_t[LedcChannelForRightMotor]
// ESP32-S3 has 8 ledc channels starting from 0
void setup() {
}

void loop() {
	DRV8874PWPR_Obj.left(100);		// Set speed to "100" out of "250" for the left driver
	DRV8874PWPR_Obj.right(-100);	// Set speed to "-100" out of "250" for the right driver
	delay(3000);
	DRV8874PWPR_Obj.left(0);
	DRV8874PWPR_Obj.right(0);
	delay(1000);
	DRV8874PWPR_Obj.left(-100);
	DRV8874PWPR_Obj.right(100);
	delay(3000);
	DRV8874PWPR_Obj.left(0);
	DRV8874PWPR_Obj.right(0);
	delay(1000);
	DRV8874PWPR_Obj.left(100);
	DRV8874PWPR_Obj.right(100);
	delay(3000);
	DRV8874PWPR_Obj.left(0);
	DRV8874PWPR_Obj.right(0);
	delay(1000);
	DRV8874PWPR_Obj.left(-100);
	DRV8874PWPR_Obj.right(-100);
	delay(3000);
	DRV8874PWPR_Obj.left(0);
	DRV8874PWPR_Obj.right(0);
	delay(1000);
	DRV8874PWPR_Obj.left(100);
	DRV8874PWPR_Obj.right(0);
	delay(3000);
	DRV8874PWPR_Obj.left(0);
	DRV8874PWPR_Obj.right(0);
	delay(1000);
	DRV8874PWPR_Obj.left(0);
	DRV8874PWPR_Obj.right(100);
	delay(3000);
	DRV8874PWPR_Obj.left(0);
	DRV8874PWPR_Obj.right(0);
	delay(1000);
	DRV8874PWPR_Obj.left(-100);
	DRV8874PWPR_Obj.right(0);
	delay(3000);
	DRV8874PWPR_Obj.left(0);
	DRV8874PWPR_Obj.right(0);
	delay(1000);
	DRV8874PWPR_Obj.left(0);
	DRV8874PWPR_Obj.right(-100);
	delay(3000);
	DRV8874PWPR_Obj.left(0);
	DRV8874PWPR_Obj.right(0);
	delay(1000);
}