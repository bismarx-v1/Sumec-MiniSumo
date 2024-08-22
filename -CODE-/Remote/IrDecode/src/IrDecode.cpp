#include <Arduino.h>
#include "IRremote.hpp"


#define RECV_PIN 32


uint16_t mAddress;
uint16_t mCommand;


void setup() {
	Serial.begin(115200);
	IrReceiver.begin(RECV_PIN);
}


void loop() {
	if(IrReceiver.decode()) {
		if(IrReceiver.decodedIRData.protocol == RC5) {
			IrReceiver.resume();
			IrReceiver.printIRResultShort(&Serial);
			mAddress = IrReceiver.decodedIRData.address;
			mCommand = IrReceiver.decodedIRData.command;
			Serial.print("Addr:\t");
			Serial.println(mAddress); // Expected 0x0b (set new id) or 0x07 (start)
			Serial.print("Cmd:\t");
			Serial.println(mCommand);
		} else {
			IrReceiver.resume();
			Serial.println("not rc5");
		}

		delay(100);
	}
}
