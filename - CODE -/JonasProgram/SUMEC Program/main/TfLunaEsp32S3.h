#include <Wire.h>        //libs
#include <TFLI2C.h>

TFLI2C tflI2C;
int TfL_Succ = 0;

int16_t TfL_Addr1 = 0x11;	//TfL Lib - first address (usualy left sensor)
int16_t TfL_Addr2 = 0x12;	//TfL Lib - second address (usualy mid sensor)
int16_t TfL_Addr3 = 0x13;	//TfL Lib - third address (usualy right sensor)
int16_t TfL_AddrDefault = 0x10;

void TfL_Setup() {
	pinMode(41, OUTPUT);
	pinMode(42, OUTPUT);
	digitalWrite(41, LOW);
	digitalWrite(42, LOW);
	
	pinMode(15, OUTPUT);
	
    Wire.begin(18,17,400000);
	return;
}

void TfL_SetAddrs() {
	digitalWrite(15, HIGH);
	delay(100);
	digitalWrite(15, LOW);
	delay(100);
	
	while(TfL_Succ==0) {
		TfL_Succ = tflI2C.Set_I2C_Addr(TfL_Addr1, TfL_AddrDefault);	//only left sensor should be connected
		Serial.println(TfL_Succ);
		delay(1000);
		digitalWrite(15, HIGH);
		delay(10);
		digitalWrite(15, LOW);
		delay(10);
	}
	Serial.println("0x11");
	TfL_Succ = 0;
	
	digitalWrite(15, HIGH);
	delay(100);
	digitalWrite(15, LOW);
	delay(100);
	digitalWrite(15, HIGH);
	delay(100);
	digitalWrite(15, LOW);
	delay(100);
	
	digitalWrite(41, HIGH);
	
	while(TfL_Succ==0) {
		TfL_Succ = tflI2C.Set_I2C_Addr(TfL_Addr2, TfL_AddrDefault);	//only left and mid sensors should be connected
		Serial.println(TfL_Succ);
		delay(1000);
		digitalWrite(15, HIGH);
		delay(10);
		digitalWrite(15, LOW);
		delay(10);
	}
	Serial.println("0x12");
	TfL_Succ = 0;
	
	digitalWrite(15, HIGH);
	delay(100);
	digitalWrite(15, LOW);
	delay(100);
	digitalWrite(15, HIGH);
	delay(100);
	digitalWrite(15, LOW);
	delay(100);
	
	digitalWrite(42, HIGH);
	
	while(TfL_Succ==0) {
		TfL_Succ = tflI2C.Set_I2C_Addr(TfL_Addr3, TfL_AddrDefault);	//all sensors should be connected
		Serial.println(TfL_Succ);
		delay(1000);
		digitalWrite(15, HIGH);
		delay(10);
		digitalWrite(15, LOW);
		delay(10);
	}
	Serial.println("0x13");
	TfL_Succ = 0;
	
	digitalWrite(15, HIGH);
	delay(100);
	digitalWrite(15, LOW);
	delay(100);
	digitalWrite(15, HIGH);
	delay(100);
	digitalWrite(15, LOW);
	delay(100);
	digitalWrite(15, HIGH);
	delay(100);
	digitalWrite(15, LOW);
	delay(100);
	
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
	A1=0;
	A2=0;
	A3=0;

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