#include "SumecWebServerFuncs.h"

unsigned long WebServer_TimePrev;
int RandInt = 65534;

void setup() {
	Serial.begin(115200);
	delay(2000);
	SumecWebServer_Setup();
}

void loop() {
	SumecWebServer_Loop();
	
	
	
	
	if(WebServer_TimePrev + 500 <= millis()) {	//500 is the least delay befor update
		SumecWebServer_UpdatePrep();
		
		Serial.print("Core["+String(xPortGetCoreID())+"]: ");
		Serial.println("========New Loop========");
		
		RandInt = random(4);
		SumecWebServer_Update("Mode", RandInt);	//Sends an int from <0; 4) to Mode
		
		RandInt = random(4096);
		SumecWebServer_Update("TfL_Left", RandInt);
		
		RandInt = random(4096);
		SumecWebServer_Update("TfL_Mid", RandInt);
		
		RandInt = random(4096);
		SumecWebServer_Update("TfL_Right", RandInt);
		
		
		RandInt = random(2);
		SumecWebServer_Update("Sharp_Left", RandInt);

		RandInt = random(2);
		SumecWebServer_Update("Sharp_Right", RandInt);
		
		
		RandInt = random(4096);
		SumecWebServer_Update("QRE_Left", RandInt);
		
		RandInt = random(4096);
		SumecWebServer_Update("QRE_Rear", RandInt);
		
		RandInt = random(4096);
		SumecWebServer_Update("QRE_Right", RandInt);
		
		
		RandInt = random(65535);
		SumecWebServer_Update("IR", RandInt);
		
		Serial.print("Core["+String(xPortGetCoreID())+"]: ");
		Serial.println(RandInt);
		
		Serial.print("Core["+String(xPortGetCoreID())+"]: ");
		Serial.println("object = " + String(object["IR"]));
		
		SumecWebServer_UpdatePush();
		
		WebServer_TimePrev = millis();
	}
}

