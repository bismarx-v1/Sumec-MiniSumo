#include <Wire.h>

int TfLuna_Get(int TfLuna_Get_Address=0x10) {
	Wire.beginTransmission(TfLuna_Get_Address); //Address of sensor. default is 0x10
	Wire.write(0x5A);	//head
	Wire.write(0x05);	//len			//IS POSSIBLY WRONG FOR GET
	Wire.write(0x0B);	//id			//IS DEFINELY WRONG FOR GET
	Wire.write(0x1E); 	//payload		//IS DEFINELY WRONG FOR GET			//Address goes here. hex number (0x##) min 0x08 max 0x77
	Wire.write(0x00);	//checksum		//IS POSSIBLY WRONG FOR GET
	
	return Wire.endTransmission();
	
}









void setup() {
	Wire.begin(11, 10, 400000);	//start wire w/ SDA=11; SCL=10; 
	Serial.begin(115200);		//start serial
	while(!Serial) {delay(10);}	//wait for serial
	

}

void loop() {

}