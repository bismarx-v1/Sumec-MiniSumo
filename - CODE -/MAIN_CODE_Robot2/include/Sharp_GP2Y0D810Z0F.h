/*
* When constructin object use "'L'" or "'R'" to pick the sensor
* 	- "'L'" means Left
* 	- "'R'" means Right
* 
* Use .get() to get sensors val. returns '1' or '0' with data-type uint8_t
* 
* Sensors range is 2-10cm
*/

class Sharp {
	private:
		const uint8_t Sensor_Pin[2] = {35, 16};	// Pins in order: {"left", "right"}
		uint8_t Sensor;
		
	public:
		Sharp(uint8_t SensorId);
		bool get();
		
};

Sharp::Sharp(uint8_t SensorId) {	// Input "SensorId" when making a new object
	if(SensorId == 'L') {			// Left sensor
		this->Sensor = Sensor_Pin[0];			// Left sensor's pin
	} else if(SensorId == 'R') {	// Right sensor
		this->Sensor = Sensor_Pin[1];			// Right sensor's pin
	}
	
	pinMode(Sensor, INPUT);
}

bool Sharp::get() {				// Func for getting sensor's data
	return(1-digitalRead(Sensor));	// Return flipped value from sensor; 0 = clear, 1 = object in range 2-10cm;
}