/*
* When construnctiong object use "'L'", "'R'" or "'B'" to pick wich sensor is to be used
* 	- "'L'" means Left
* 	- "'R'" means Right
* 	- "'B'" means Back (Rear would be better but 'R' is taken)
* 
* Set threshold by using .Threshold = (uint8_t [Val]);
* 
* Read value by using .get() returns '1' or '0' of type uint8_t
* 
* Read value by using .getRaw() returns measured voltage from 0(0V) to 4096(3V3) of type uint16_t
*/

class QRE {
	private:
		const uint8_t Sensor_Pin[3] = {10, 9, 8};	// Pins in order: {"left", "right", "rear"}
		uint8_t Sensor;
		
	public:
		QRE(uint8_t SensorId);
		uint8_t get();
		uint16_t getRaw();
		uint16_t Threshold = 3000;	// Default threshold
		
};

QRE::QRE(uint8_t SensorId) {
	if(SensorId == 'L') {			// Left sensor
		this->Sensor = Sensor_Pin[0];			// Left sensor pin
	} else if(SensorId == 'R') {	// Right sensor
		this->Sensor = Sensor_Pin[1];			// Right sensor pin
	} else if(SensorId == 'B') {	// Rear sensor marked with "B" for "Back", cos "R" is taken
		this->Sensor = Sensor_Pin[2];			// Rear sensor pin
	}
	
	pinMode(Sensor, INPUT);
}

uint8_t QRE::get() {
	if(analogRead(Sensor)<Threshold) {	// Returns true/false based on "sensor value" and "threshold"
		return(1);
	} else {
		return(0);
	}
}

uint16_t QRE::getRaw() {
	return(analogRead(Sensor));	// Returns measured voltage from 0(0V) to 4095(3V3)
}