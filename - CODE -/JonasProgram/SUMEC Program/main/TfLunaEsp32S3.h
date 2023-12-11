#include <Wire.h>        //libs
#include <TFLI2C.h>

TFLI2C tflI2C;
int TfL_Succ = 0;

int16_t TfL_Addr1 = 0x11;	//TfL Lib - first address (usualy left sensor)
int16_t TfL_Addr2 = 0x12;	//TfL Lib - second address (usualy mid sensor)
int16_t TfL_Addr3 = 0x13;	//TfL Lib - third address (usualy right sensor)
int16_t TfL_AddrDefault = 0x10;

void TfL_Setup() {
	pinMode(40, OUTPUT);
	pinMode(41, OUTPUT);
	pinMode(42, OUTPUT);
	digitalWrite(40, LOW);
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
	
	while(TfL_Succ==0) {
		TfL_Succ = tflI2C.Set_I2C_Addr(TfL_Addr2, TfL_AddrDefault);	//only left and mid sensors should be connected
		Serial.println(TfL_Succ);
		delay(1000);
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
	
	while(TfL_Succ==0) {
		TfL_Succ = tflI2C.Set_I2C_Addr(TfL_Addr3, TfL_AddrDefault);	//all sensors should be connected
		Serial.println(TfL_Succ);
		delay(1000);
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

int TfL_IsSet() {									//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
	byte error, address;							//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
	int A1, A2, A3;									//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
	A1=0;											//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
	A2=0;											//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
	A3=0;											//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|

	for(address = 1; address < 127; address++ ) {	//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
		Wire.beginTransmission(address);			//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
		error = Wire.endTransmission();				//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
    if(error == 0) {							//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
			if(address==0x11) {						//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
				if(A1!=1) {							//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
				A1=1;								//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
				}									//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
				else {								//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
					return 0;						//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
				}									//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
			} else if(address==0x12) {				//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
				if(A2!=1) {							//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
				A2=1;								//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
				}									//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
				else {								//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
					return 0;						//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
				}									//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
			} else if(address==0x13) {				//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
				if(A3!=1) {							//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
				A3=1;								//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
				}									//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
				else {								//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
					return 0;						//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
				}									//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
			}										//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
		}											//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
	}												//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
	
	if(A1==1&&A2==1&&A3==1) {						//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
		return 1;									//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
	} else {										//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
		return 0;	//this should never be reached	//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
	}												//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
}													//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|