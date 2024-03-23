#include <Wire.h>

class TF_Luna {
	private:
		
	public:
		uint8_t DebugMode = 0;
		TF_Luna(uint8_t Sda, uint8_t Scl);
		uint8_t save(uint8_t Address);
		uint8_t reboot(uint8_t Address);
		uint8_t writeAddress(uint8_t Address, uint8_t NewAddress);
		uint8_t factoryReset(uint8_t Address);
		
};

TF_Luna::TF_Luna(uint8_t Sda, uint8_t Scl) {
	Wire.begin(Sda, Scl, 40000);
}

uint8_t TF_Luna::save(uint8_t Address) {	//save
	if(DebugMode==1) {
		Serial.printf("TFL.SAVE; addr= %i\n", Address);
	}
	
	Wire.beginTransmission(Address);
	Wire.write(0x20);	// REG.SAVE
	Wire.write(0x01);	// DATA.COMMIT
	return(Wire.endTransmission());
}

uint8_t TF_Luna::reboot(uint8_t Address) {	//reboot
	if(DebugMode==1) {
		Serial.printf("TFL.REBOOT; addr= %i\n", Address);
	}
	
	Wire.beginTransmission(Address);
	Wire.write(0x21);	// REG.REBOOT
	Wire.write(0x02);	// DATA.REBOOT
	return(Wire.endTransmission());
}

uint8_t TF_Luna::writeAddress(uint8_t Address, uint8_t NewAddress) {	//set address
	if(DebugMode==1) {
		Serial.printf("TFL.WRITE_ADDRESS; addr= %i\n", Address);
	}
	
	Wire.beginTransmission(Address);
	Wire.write(0x22);	// REG.ADDR_WRITE
	Wire.write(NewAddress);	// New address
	return(Wire.endTransmission());
}

uint8_t TF_Luna::factoryReset(uint8_t Address) {	//factory reset
	if(DebugMode==1) {
		Serial.printf("TFL.FACTORY_RESET; addr= %i\n", Address);
	}
	
	Wire.beginTransmission(Address);
	Wire.write(0x29);	// REG.FACTORY_RESET
	Wire.write(0x01);	// DATA.TRUE
	uint8_t err = Wire.endTransmission();
	reboot(Address);
	delay(1000);
	return(err);
}