#include <IRremote.h>
#include <Wire.h>
#include "motorsEsp32S3.h"
#include "lineEsp32S3.h"
#include "IRstart.h"
#include "TfLunaEsp32S3.h"

int16_t tfAddr1 = 0x11;	//TfL Lib - first address (usualy left sensor)
int16_t tfAddr2 = 0x12;	//TfL Lib - second address (usualy mid sensor)
int16_t tfAddr3 = 0x13;	//TfL Lib - third address (usualy right sensor)
const int LEDPin = 15;
TaskHandle_t Task1;
int LEDBlink = 0;
int TfLCase;
int ResetProgramVar = 0;
int PrevLEDBlink = 0;

///////////////////////////////////////////////////////
///										Settings										 ///
///////////////////////////////////////////////////////
const int QreTreshold = 3000;
const int GlobalSpeed = 255;
const int BackQreEnabled = 0;
const int TfLRange = 40;

int LedBlinkState = 0;

void CodeForTask1(void * parameter) {	/*Code for core 0*/
	Serial.print("Core ["); Serial.print(xPortGetCoreID()); Serial.println("] started");	//print this core
	
	for(;;) {	//void loop()
		switch(LEDBlink) {
			case 0:
				if(LedBlinkState != 0) {
					LedBlinkState = 0;
					digitalWrite(LEDPin, 0);
					break;
				}
				
				else {
					break;
				}
			
			case 1:
				if(LedBlinkState != 1) {
					LedBlinkState = 1;
					digitalWrite(LEDPin, 1);
					delay(200);
					digitalWrite(LEDPin, 0);
					delay(400);
					break;
				}
				
				else {
					break;
				}
			
			case 2:
				if(LedBlinkState != 2) {
					LedBlinkState = 2;
					digitalWrite(LEDPin, 1);
					delay(500);
					digitalWrite(LEDPin, 0);
					delay(200);
					digitalWrite(LEDPin, 1);
					delay(200);
					digitalWrite(LEDPin, 0);
					delay(200);
					break;
				}
				
				else {
					break;
				}
		}
	}
}

void ResetProgram() {
	//detachInterrupt(2);
	LEDBlink = 0;
	MOTORS_Go(0, 0);
  delay(100);
	while (digitalRead(2)!= 1) {
		delay(10);
	}
	//attachInterrupt(2, ResetProgram, RISING);
	//setup(); 
	loop();
}

/*
int Rec11Bits;
int Address;
int Command;
int DohyoID;

void IRStart() {
	while (1) {
		decode_results results;	//IR wait

		if (irrecv.decode(&results)) {

			Rec11Bits = results.value & 0x7FF;
			Command = Rec11Bits & 0x3F;
			Address = Rec11Bits >> 6;

			if (Address == 0x0B) {
				DohyoID = Command >> 1;
				digitalWrite(LEDPin, HIGH);
				delay(100);
				digitalWrite(LEDPin, LOW);
				delay(100);
				digitalWrite(LEDPin, HIGH);
				delay(100);
				digitalWrite(LEDPin, LOW);
				delay(100);
			}

			if (Address == 0x07) {
				if (Command >> 1 == DohyoID) {
					if(Command & 0b1 == 1) {
						irrecv.resume();			// resume IR reception
						break;
					}
				}
			}
		}
		irrecv.resume();			// resume IR reception
	}
}
*/

void setup() {
	Serial.begin(115200);

	if (ResetProgramVar == 0) {
		//goto StartOfProgram;
	

		pinMode(2, INPUT);
		//attachInterrupt(2, ResetProgram, RISING);

		MOTORS_Setup();
		pinMode(LEDPin, OUTPUT);
		
		xTaskCreatePinnedToCore(CodeForTask1, "Task_1", 3500, NULL, 0, &Task1, 0);

		TfL_Setup();	//TfL Lib - libs setup
		
		SetAddrLabel:	//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|

		TfL_SetAddrs();	//TfL Lib - start the process for setting adresses

		delay(1000);						 //|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
		if (TfL_IsSet() == 0) {	//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
			Serial.println("goto");
			goto SetAddrLabel;	//|UNTESTED CODE||UNTESTED CODE||UNTESTED CODE||UNTESTED CODE|
		}
		Serial.print("Lunas Ok");

		ResetProgramVar = 1;

		//StartOfProgram:
	}
	else {
		//IRStart();
		LEDBlink = 2;
	}
}

void loop() {
	delay(10);
	
	Serial.println("START");
	
	if(digitalRead(2) >= 1) {
		Serial.println("RESET");
		ResetProgram();
	}
	
	/*	decode_results results;	//IR wait

	if (irrecv.decode(&results)) {
		Rec11Bits = results.value & 0x7FF;
		Command = Rec11Bits & 0x3F;
		Address = Rec11Bits >> 6;
		
		if (Address == 0x07) {
			if (Command >> 1 == DohyoID) {
				if(Command & 0b1 == 0) {
					irrecv.resume();	// resume IR reception
					ResetProgram();
				}
			}
		}
	}
	irrecv.resume();	// resume IR reception
*/
	if ((LINE_Get(1, QreTreshold) == 1 && LINE_Get(3, QreTreshold) == 1) || (LINE_Get(2, QreTreshold))) {	//If (left and right) or front Qre = 1
		MOTORS_Go(-GlobalSpeed, -GlobalSpeed);
		delay(500);
		MOTORS_Go(GlobalSpeed, -GlobalSpeed);
		delay(250);
		return;
	}
	if (LINE_Get(1, QreTreshold) == 1) {	//If left Qre = 1
		MOTORS_Go(GlobalSpeed, -GlobalSpeed);
		delay(250);
		return;
	}
	if (LINE_Get(3, QreTreshold) == 1) {	//If right Qre = 1
		MOTORS_Go(-GlobalSpeed, GlobalSpeed);
		delay(250);
		return;
	}
	if (BackQreEnabled == 1) {							//If back Qre (enabled = 1)
		if (LINE_Get(4, QreTreshold) == 1) {	//If back Qre = 1
			MOTORS_Go(GlobalSpeed, GlobalSpeed);
			return;
		}
	}

	TfLCase = 0;
	if (TfL_Get(0x11) <= TfLRange) {
		TfLCase += 1;
	}
	if (TfL_Get(0x12) <= TfLRange) {
		TfLCase += 2;
	}
	if (TfL_Get(0x13) <= TfLRange) {
		TfLCase += 4;
	}

	switch (TfLCase) {
		case 0:																 //Enemy not found
			MOTORS_Go(GlobalSpeed, GlobalSpeed);	//Think of a better strategy
			return;

		case 1:	//Enemy is left of SUMEC
			MOTORS_Go(-GlobalSpeed, GlobalSpeed);
			return;

		case 2:	//Enemy is infront of SUMEC
			MOTORS_Go(GlobalSpeed, GlobalSpeed);
			return;

		case 3:	//Enemy is left/front of SUMEC
			MOTORS_Go(GlobalSpeed / 4, GlobalSpeed / 2);
			return;

		case 4:	//Enemy is right of SUMEC
			MOTORS_Go(GlobalSpeed, -GlobalSpeed);
			return;

		case 5:	//Enemy is left/right of SUMEC
			MOTORS_Go(GlobalSpeed, GlobalSpeed);
			return;

		case 6:	//Enemy is front/right of SUMEC
			MOTORS_Go(GlobalSpeed / 2, GlobalSpeed / 4);
			return;

		case 7:	//Enemy is everywhere of SUMEC
			MOTORS_Go(GlobalSpeed, GlobalSpeed);
			return;
	}
}