#include <Wire.h>

int TfLuna_Command(int CustomTfLuna_Address=0x10, String CustomTfLuna_Command, int CustomTfLuna_Additional=0x0) {
	switch(Command) {
	case "Get":
		Wire.beginTransmission(CustomTfLuna_TfLuna_Address);
		Wire.write(0x5A);	//head
		Wire.write(0x05);	//len
		Wire.write(0x0B);	//id
		Wire.write(0x1E); 	//payload			//Address goes here. hex number (0x##) min 0x08 max 0x77
		Wire.write(0x00);	//checksum
		
		return Wire.endTransmission();
		break;
	
	case "SoftR":
		Wire.beginTransmission(CustomTfLuna_TfLuna_Address);
		Wire.write(0x5A);	//head
		Wire.write(0x04);	//len
		Wire.write(0x02);	//id
		Wire.write(0x00);	//checksum
		
		return Wire.endTransmission();
		break;
	
	case "SetOutput":
		Wire.beginTransmission(CustomTfLuna_TfLuna_Address);
		Wire.write(0x5A);	//head
		Wire.write(0x04);	//len
		Wire.write(0x0A);	//id
		Wire.write(0x00);	//checksum
		break;
	
	case "SetAddr":
		Wire.beginTransmission(CustomTfLuna_TfLuna_Address);
		Wire.write(0x5A);	//head
		Wire.write(0x05);	//len
		Wire.write(0x0B);	//id
		Wire.write(CustomTfLuna_Additional);	//payload		//new address (min 0x08 max 0x77) //test with 0x20
		Wire.write(0x00);	//checksum
		break;
	
	case "":
		Wire.beginTransmission(CustomTfLuna_TfLuna_Address);
		Wire.write(0x5A);	//head
		Wire.write(0x05);	//len
		Wire.write(0x0A);	//id
		Wire.write(0x00);	//checksum
		break;
	
	
	
	}
}









void setup() {
	Wire.begin(11, 10, 400000);	//start wire w/ SDA=11; SCL=10; 
	Serial.begin(115200);		//start serial
	while(!Serial) {;}	//wait for serial
	delay(1000);
	

}

void loop() {

}