#include "DRV8874PWPR.h"

DRV8874PWPR DRV8874PWPR_Obj('L');

void setup() {
	Serial.begin(115200);
}

void loop() {
	DRV8874PWPR_Obj.left(100);
	DRV8874PWPR_Obj.right(-100);
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
}