/*
* This lib is a bit more complex than the others
* Bast is to first try to understand the code and than maybe ask Natani Si. for more explanation
* 
* Uses the Wire.h lib for reading and writing to TF-Ls
*/

#include <Wire.h>

class TF_Luna {
	private:
		uint16_t Read2Bytes(uint8_t RNB_Address, uint8_t RNB_Reg) {	// Read 2 bytes from an i2c address and a register
			uint16_t RNB_Data = 0;	// 2 byte var for return
			Wire.beginTransmission(RNB_Address);	// Start i2c transmission on inputed address
			Wire.write(RNB_Reg);	// Set pointer to register
			Wire.requestFrom(RNB_Address, 2);	// Request 2 bytes
			if(Wire.available() == 2) {	// If recieved 2 bytes
				for(uint8_t i = 0; i <= 2-1; i++) {
					RNB_Data = RNB_Data << 8;	// Shift byte left
					RNB_Data = RNB_Data + Wire.read();	// Add new byte
				}
			}
			
			Wire.endTransmission();
			return(RNB_Data);
		}
		
	public:
		uint8_t DebugMode = 0;
		TF_Luna(uint8_t Sda, uint8_t Scl);
		uint8_t save(uint8_t Address);
		uint8_t reboot(uint8_t Address);
		uint8_t writeAddress(uint8_t Address, uint8_t NewAddress);
		uint8_t factoryReset(uint8_t Address);
		void readData(uint8_t Address, uint16_t* DataArray);
		uint8_t readOnlyDist(uint8_t Address);
};

TF_Luna::TF_Luna(uint8_t Sda, uint8_t Scl) {
	Wire.begin(Sda, Scl, 40000);
}

uint8_t TF_Luna::save(uint8_t Address) {	// Save
	if(DebugMode==1) {
		Serial.printf("TFL.SAVE; addr= %i\n", Address);
	}
	
	Wire.beginTransmission(Address);
	Wire.write(0x20);	// REG.SAVE
	Wire.write(0x01);	// DATA.COMMIT
	return(Wire.endTransmission());
}

uint8_t TF_Luna::reboot(uint8_t Address) {	// Reboot
	if(DebugMode==1) {
		Serial.printf("TFL.REBOOT; addr= %i\n", Address);
	}
	
	Wire.beginTransmission(Address);
	Wire.write(0x21);	// REG.REBOOT
	Wire.write(0x02);	// DATA.REBOOT
	return(Wire.endTransmission());
}

uint8_t TF_Luna::writeAddress(uint8_t Address, uint8_t NewAddress) {	// Set address
	if(DebugMode==1) {
		Serial.printf("TFL.WRITE_ADDRESS; addr= %i\n", Address);
	}
	
	Wire.beginTransmission(Address);
	Wire.write(0x22);	// REG.ADDR_WRITE
	Wire.write(NewAddress);	// New address
	return(Wire.endTransmission());
}

uint8_t TF_Luna::factoryReset(uint8_t Address) {	// Factory reset
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

void TF_Luna::readData(uint8_t Address, uint16_t* DataArray) {	// Read data
	DataArray[0] = Read2Bytes(Address, 0x00);	// Distance (in cm)
	DataArray[1] = Read2Bytes(Address, 0x02);	// Amplitude - don't know what this means
	DataArray[2] = Read2Bytes(Address, 0x04);	// Temp multiply by 0.01 to get °C
	DataArray[3] = Read2Bytes(Address, 0x06);	// Ticks - don't know what this means
	DataArray[4] = Read2Bytes(Address, 0x08);	// Error - don't know what this means
}

uint8_t TF_Luna::readOnlyDist(uint8_t Address) {	// Read data
	return(Read2Bytes(Address, 0x00));	// Distance (in cm)
}