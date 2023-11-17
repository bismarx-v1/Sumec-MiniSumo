#include "TfLunaEsp32S3.h"	//TfL Lib - the lib import

int16_t tfAddr1 = 0x11;	//TfL Lib - first address (usualy left sensor)
int16_t tfAddr2 = 0x12;	//TfL Lib - second address (usualy mid sensor)
int16_t tfAddr3 = 0x13;	//TfL Lib - third address (usualy right sensor)

void setup() {
    Serial.begin(115200);
	TfL_Setup();	//TfL Lib - libs setup
	
	SetAddrLabel:									//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
	
	TfL_SetAddrs();	//TfL Lib - start the process for setting adresses
	
	delay(1000);									//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
	if(TfL_IsSet()!=1) {							//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
	goto SetAddrLabel;								//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
	}												//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
}

void loop() {
	Serial.print("Left:\t");
	Serial.println(TfL_Get(tfAddr1));	//TfL Lib - Get from sensor
	
	Serial.print("Mid:\t");
	Serial.println(TfL_Get(tfAddr2));	//TfL Lib - Get from sensor
	
	Serial.print("Right:\t");
	Serial.println(TfL_Get(tfAddr3));	//TfL Lib - Get from sensor
	Serial.println("=======================");
	delay(100);
}