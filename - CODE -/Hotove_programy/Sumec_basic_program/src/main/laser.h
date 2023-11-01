#include <Wire.h>
#include <VL53L0X.h>

VL53L0X LASER_SensorLeft;
VL53L0X LASER_SensorRight;
VL53L0X LASER_SensorFront;

#define LASER_PinLeft 25
#define LASER_PinRight 27
#define LASER_PinFront 26

int LASER_DistLeft = 0;
int LASER_DistRight = 0;
int LASER_DistFront = 0;


void LASER_Setup() {
	Wire.begin();

	pinMode(LASER_PinRight, OUTPUT);
	pinMode(LASER_PinLeft, OUTPUT);
	pinMode(LASER_PinFront, OUTPUT);
	digitalWrite(LASER_PinRight, LOW);
	digitalWrite(LASER_PinLeft, LOW);
	digitalWrite(LASER_PinFront, LOW);
	delay(500);

	digitalWrite(LASER_PinRight, HIGH);
	delay(150);
	LASER_SensorLeft.init(true);
	delay(100);
	LASER_SensorLeft.setAddress((uint8_t)01);

	digitalWrite(LASER_PinLeft, HIGH);
	delay(150);
	LASER_SensorRight.init(true);
	delay(100);
	LASER_SensorRight.setAddress((uint8_t)02);

	digitalWrite(LASER_PinFront, HIGH);delay(150);
	LASER_SensorFront.init(true);
	delay(100);
	LASER_SensorFront.setAddress((uint8_t)03);

	LASER_SensorLeft.startContinuous();
	LASER_SensorRight.startContinuous();
	LASER_SensorFront.startContinuous();
}

int LASER_Get(int LASER_Sensor, int LASER_Thereshold, int LASER_Mode) {
	if(LASER_Sensor==1) {
		if(LASER_Mode==0) {
			return (LASER_SensorLeft.readRangeContinuousMillimeters() <= LASER_Thereshold ? 1: 0);
		} else if(LASER_Mode==1) {
			return LASER_SensorLeft.readRangeContinuousMillimeters();
		} else {
			return 0;
		}
	} else if(LASER_Sensor==2) {
		if(LASER_Mode==0) {
			return (LASER_SensorRight.readRangeContinuousMillimeters() <= LASER_Thereshold ? 1: 0);
		} else if(LASER_Mode==1) {
			return LASER_SensorRight.readRangeContinuousMillimeters();
		} else {
			return 0;
		}
	} else if(LASER_Sensor==3) {
		if(LASER_Mode==0) {
			return (LASER_SensorFront.readRangeContinuousMillimeters() <= LASER_Thereshold ? 1: 0);
		} else if(LASER_Mode==1) {
			return LASER_SensorFront.readRangeContinuousMillimeters();
		} else {
			return 0;
		}
	} else {
		return 0;
	}
	
}