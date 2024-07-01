#include <Wire.h>        //libs
#include <TFLI2C.h>

TFLI2C tflI2C;
int TfL_Succ = 0;
const int XSMid = 32;  //XShutMidLuna
const int XSRight = 33;  //XShutRightLuna
const int Sda = 21;  //Sda
const int Scl = 22;  //Scl
const int TestLed = 2;  //TestLed

int16_t TfL_Addr1 = 0x11;	//TfL Lib - first address (usualy left sensor)
int16_t TfL_Addr2 = 0x12;	//TfL Lib - second address (usualy mid sensor)
int16_t TfL_Addr3 = 0x13;	//TfL Lib - third address (usualy right sensor)
int16_t TfL_AddrDefault = 0x10;

void TfL_Setup() {
	pinMode(XSMid, OUTPUT);
	pinMode(XSRight, OUTPUT);
	digitalWrite(XSMid, LOW);	//xs mid initial pos
	digitalWrite(XSRight, LOW);	//xs right initial pos
	
	pinMode(TestLed, OUTPUT);
	
    Wire.begin(Sda,Scl,400000);
	return;
}

void TfL_SetAddrs() {
	digitalWrite(TestLed, HIGH);
	delay(100);
	digitalWrite(TestLed, LOW);
	delay(100);
	
	goto TEMP1;
	
	while(TfL_Succ==0) {
		TfL_Succ = tflI2C.Set_I2C_Addr(TfL_Addr1, TfL_AddrDefault);	//only left sensor should be connected
		Serial.println(TfL_Succ);
		delay(1000);
		digitalWrite(TestLed, HIGH);
		delay(10);
		digitalWrite(TestLed, LOW);
		delay(10);
	}
	Serial.println("0x11");
	TfL_Succ = 0;
	
	digitalWrite(TestLed, HIGH);
	delay(100);
	digitalWrite(TestLed, LOW);
	delay(100);
	digitalWrite(TestLed, HIGH);
	delay(100);
	digitalWrite(TestLed, LOW);
	delay(100);
	
	TEMP1:
	
	digitalWrite(XSMid, HIGH);
	Serial.println("XS is HIGH");
	
	while(TfL_Succ==0) {
		TfL_Succ = tflI2C.Set_I2C_Addr(TfL_Addr2, TfL_AddrDefault);	//only left and mid sensors should be connected
		Serial.println(TfL_Succ);
		delay(1000);
		digitalWrite(TestLed, HIGH);
		delay(10);
		digitalWrite(TestLed, LOW);
		delay(10);
	}
	Serial.println("0x12");
	TfL_Succ = 0;
	
	digitalWrite(TestLed, HIGH);
	delay(100);
	digitalWrite(TestLed, LOW);
	delay(100);
	digitalWrite(TestLed, HIGH);
	delay(100);
	digitalWrite(TestLed, LOW);
	delay(100);
	
	goto TEMP2;
	
	digitalWrite(XSRight, HIGH);
	
	while(TfL_Succ==0) {
		TfL_Succ = tflI2C.Set_I2C_Addr(TfL_Addr3, TfL_AddrDefault);	//all sensors should be connected
		Serial.println(TfL_Succ);
		delay(1000);
		digitalWrite(TestLed, HIGH);
		delay(10);
		digitalWrite(TestLed, LOW);
		delay(10);
	}
	Serial.println("0x13");
	TfL_Succ = 0;
	
	digitalWrite(TestLed, HIGH);
	delay(100);
	digitalWrite(TestLed, LOW);
	delay(100);
	digitalWrite(TestLed, HIGH);
	delay(100);
	digitalWrite(TestLed, LOW);
	delay(100);
	digitalWrite(TestLed, HIGH);
	delay(100);
	digitalWrite(TestLed, LOW);
	delay(100);
	
	TEMP2:
	
	return;
}

int TfL_Get(int TfLAddr=0x10) {
	int16_t TfL_Dist = 0;
	tflI2C.getData(TfL_Dist, TfLAddr);
	return TfL_Dist;
}

int TfL_IsSet() {
	byte error, address;
	int A1, A2, A3;
	//A1=0;
	A1=1;
	A2=0;
	//A3=0;
	A3=1;

	for(address = 1; address < 127; address++ ) {
		Wire.beginTransmission(address);
		error = Wire.endTransmission();
		if(error == 0) {
			if(address==0x11) {
				if(A1!=1) {
				A1=1;
				}
				else {
					return 0;
				}
			} else if(address==0x12) {
				if(A2!=1) {
				A2=1;
				}
				else {
					return 0;
				}
			} else if(address==0x13) {
				if(A3!=1) {
				A3=1;
				}
				else {
					return 0;
				}
			}
		}
	}
	
	if(A1==1&&A2==1&&A3==1) {
		return 1;
	} else {
		return 0;	//this should never be reached
	}
}
