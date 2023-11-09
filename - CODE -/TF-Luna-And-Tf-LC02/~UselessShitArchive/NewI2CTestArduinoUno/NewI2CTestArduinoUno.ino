#include <Wire.h>



void setup() {
	Wire.begin();

	Serial.begin(9600);
	while (!Serial) {delay(10);}						 // Leonardo: wait for serial monitor
	Serial.println("START");
}

void loop() {
	int EndData[5];	
	byte error, address;
	int nDevices;

	Serial.println("Scanning...");

	nDevices = 0;
	
	EndData[0]=0;
	EndData[1]=0;
	EndData[2]=0;
	EndData[3]=0;
	EndData[4]=0;
	EndData[5]=0;

	Serial.println(EndData[0]);
	Serial.println(EndData[1]);
	Serial.println(EndData[2]);
	Serial.println(EndData[3]);
	Serial.println(EndData[4]);
	Serial.println(EndData[5]);

	for(address = 0; address <= 127; address++ ) {
		Wire.beginTransmission(address);
		error = Wire.endTransmission();
		switch(error) {
			case 0:
				Serial.print(address);
				Serial.println("\tSuccess");
				EndData[0]=EndData[0]+1;
				break;
			case 1:
				Serial.print(address);
				Serial.println("\t1");
				EndData[1]=EndData[1]+1;
				break;
			case 2:
				Serial.print(address);
				Serial.println("\t2=");
				EndData[2]=EndData[2]+1;
				break;
			case 3:
				Serial.print(address);
				Serial.println("\t3==");
				EndData[3]=EndData[3]+1;
				break;
			case 4:
				Serial.print(address);
				Serial.println("\t4===");
				EndData[4]=EndData[4]+1;
				break;
			case 5:
				Serial.print(address);
				Serial.println("\t5====");
				EndData[5]=EndData[5]+1;
				break;
			default:
				Serial.print(address);
				Serial.println("\tdef");
				break;
		}
	}
	
	Serial.println("=========================");
	Serial.print("Success\t\t> ");
	Serial.println(EndData[0]);
	Serial.print("Data too long\t> ");
	Serial.println(EndData[1]);
	Serial.print("NACK (address)\t> ");
	Serial.println(EndData[2]);
	Serial.print("NACK (data)\t> ");
	Serial.println(EndData[3]);
	Serial.print("other error\t> ");
	Serial.println(EndData[4]);
	Serial.print("Timeout\t\t> ");
	Serial.println(EndData[5]);
	Serial.println("=========================");
	
	
	delay(5000);
}