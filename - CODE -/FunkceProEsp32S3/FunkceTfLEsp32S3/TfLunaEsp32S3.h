#include <Wire.h>        //libs
#include <TFLI2C.h>

TFLI2C tflI2C;

void TfL_Setup() {
	pinMode(40, OUTPUT);
	pinMode(41, OUTPUT);
	pinMode(42, OUTPUT);
	digitalWrite(40, LOW);
	digitalWrite(41, LOW);
	digitalWrite(42, LOW);
	
    Wire.begin(18,17,400000);
	return
}

void TfL_SetAddrs() {
	
	
	return
}




int TfL_Get(int TfLAddr=0x10) {
	int tfDist = 0;
	tflI2C.getData(tfDist, TfLAddr);
	return tfDist
}