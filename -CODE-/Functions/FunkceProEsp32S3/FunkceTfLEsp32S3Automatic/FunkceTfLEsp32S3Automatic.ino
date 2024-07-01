#include "TfLunaEsp32S3.h"	//TfL Lib - the lib import

int16_t tfAddr1 = 0x11;	//TfL Lib - first address (usualy left sensor)
int16_t tfAddr2 = 0x12;	//TfL Lib - second address (usualy mid sensor)
int16_t tfAddr3 = 0x13;	//TfL Lib - third address (usualy right sensor)

void setup() {
	Serial.begin(115200);
	delay(2000);
	Serial.println(millis());
	delay(1000);
	
	TfL_Setup();	//TfL Lib - libs setup
}

void loop() {
	Serial.print(TfL_IsOnline(0x00));	//Check if there is a luna on this address; 0 if yes 1 if no;
	Serial.print(TfL_IsOnline(0x10));	//Check if there is a luna on this address; 0 if yes 1 if no;
	Serial.print(TfL_IsOnline(0x11));	//Check if there is a luna on this address; 0 if yes 1 if no;
	Serial.print(TfL_IsOnline(0x12));	//Check if there is a luna on this address; 0 if yes 1 if no;
	Serial.println(TfL_IsOnline(0x13));	//Check if there is a luna on this address; 0 if yes 1 if no;
	
	Serial.print("Left:\t");
	Serial.println(TfL_Get(tfAddr1));	//TfL Lib - Get from sensor
	
	Serial.print("Mid:\t");
	Serial.println(TfL_Get(tfAddr2));	//TfL Lib - Get from sensor
	
	Serial.print("Right:\t");
	Serial.println(TfL_Get(tfAddr3));	//TfL Lib - Get from sensor
	Serial.println("=======================");
	delay(100);
}