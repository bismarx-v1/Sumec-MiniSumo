class Sharp {
	private:
		uint8_t Sensor;
		
	public:
		Sharp(uint8_t SensorId);
		uint8_t get();
		
};

Sharp::Sharp(uint8_t SensorId) {
	if(SensorId == 'L') {
		this->Sensor = 35;
	} else if(SensorId == 'R') {
		this->Sensor = 16;
	}
}

uint8_t Sharp::get() {
	return(1-digitalRead(Sensor));
}