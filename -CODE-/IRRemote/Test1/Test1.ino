#include <IRremote.h>
const int led = 14;
IRsend irsend;
int Reset;



void pin25() {
	irsend.sendRC5(0b11101011100110, 14);
	//IRsend.write(RC5, 01011, 100110);	//should set DohyoID to 10011	//zero at end needed
	Serial.println("Pin25 - Set");
	Reset=1;
	while(Reset==1) {
		if(digitalRead(25)==LOW) {
			Reset=0;
		}
		delay(10);
	}
}

void pin26() {
	irsend.sendRC5(0b11100111100111, 14);
	//IRsend.write(RC5, 00111, 100111);	//if DohyoID is 10011 Sumec will start
	Serial.println("Pin26 - Start");
	Reset=1;
	while(Reset==1) {
		if(digitalRead(26)==LOW) {
			Reset=0;
		}
		delay(10);
	}
}

void pin27() {
	irsend.sendRC5(0b11100111100110, 14);
	//IRsend.write(RC5, 00111, 100110);	//if DohyoID is 10011 Sumec will stop
	Serial.println("Pin27 - Stop");
	Reset=1;
	while(Reset==1) {
		if(digitalRead(27)==LOW) {
			Reset=0;
		}
		delay(10);
	}
}


void setup() {
	Serial.begin(9600);
	pinMode(25, INPUT);
	pinMode(26, INPUT);
	pinMode(27, INPUT);
	pinMode(14, OUTPUT);
}

void loop() {
	if(digitalRead(25)==HIGH) {
		pin25();
		
	}
	if(digitalRead(26)==HIGH) {
		pin26();
		
	}
	if(digitalRead(27)==HIGH) {
		pin27();
		
	}
	delay(10);
}