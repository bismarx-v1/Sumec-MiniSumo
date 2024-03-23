class QRE {
	private:
		uint8_t Sensor;
		
	public:
		QRE(uint8_t SensorId);
		uint8_t get();
		uint8_t Threshold = 3000;
		
};

QRE::QRE(uint8_t SensorId) {
	if(SensorId == 'L') {
		this->Sensor = 10;
	} else if(SensorId == 'R') {
		this->Sensor = 9;
	} else if(SensorId == 'B') {
		this->Sensor = 8;
	}
}

uint8_t QRE::get() {
	if(analogRead(Sensor)<Threshold) {
		return(1);
	} else {
		return(0);
	}
}