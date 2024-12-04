#include <Wire.h>        //libs
#include <TFLI2C.h>

TFLI2C tflI2C;
int TfL_Succ = 0;

// New
//int16_t TfL_Addr1 = 0x10;	//TfL Lib - first address (usualy left sensor)
//nt16_t TfL_Addr2 = 0x12;	//TfL Lib - second address (usualy mid sensor)
//int16_t TfL_Addr3 = 0x13;	//TfL Lib - third address (usualy right sensor)

// Old
int16_t TfL_Addr1 = 0x11;	//TfL Lib - first address (usualy left sensor)
int16_t TfL_Addr2 = 0x10;	//TfL Lib - second address (usualy mid sensor)
int16_t TfL_Addr3 = 0x13;	//TfL Lib - third address (usualy right sensor)

int16_t TfL_AddrDefault = 0x10;

void TfL_Setup() {
	pinMode(41, OUTPUT);
	pinMode(42, OUTPUT);
	digitalWrite(41, LOW);
	digitalWrite(42, LOW);
	
	pinMode(15, OUTPUT);
	
    Wire.begin(18,17,400000);
}

int TfL_Get(int TfLAddr) {
	int16_t TfL_Dist = 0;
	bool res = tflI2C.getData(TfL_Dist, TfLAddr);
	if (res == 0) TfL_Dist = 666;
	return TfL_Dist;
}

int TfL_IsOnline(int addrToCheck) {
	byte error, address;
	int A1;
	A1=0;

	for(address = 1; address < 127; address++ ) {
		Wire.beginTransmission(address);
		error = Wire.endTransmission();
		if(error == 0) {
			if(address==addrToCheck) {
				return 0;
			} else {
				return 1;
			}
		}
	}
}