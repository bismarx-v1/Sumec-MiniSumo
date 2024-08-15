#include <Arduino.h>



//====================================CLASS=====================================================

/*
* Truthtable
* ╔═════════╤═══════╤═══════╦═══════════╗
* ║ nSleep	│  EN	│ PH	║ Status    ║
* ╠═════════╪═══════╪═══════╬═══════════╣
* ║   0	    │  any	│ any   ║ Sleep  	║
* ╟─────────┼───────┼───────╫───────────╢
* ║   1	    │  0  	│ any	║ Brake  	║
* ╟─────────┼───────┼───────╫───────────╢
* ║	  1     │  1  	│ 0  	║ Backward 	║
* ╟─────────┼───────┼───────╫───────────╢
* ║	  1		│  1  	│ 1  	║ Forward  	║
* ╚═════════╧═══════╧═══════╩═══════════╝
* this means that if pwm is OFF, robot BRAKES
* if PH is 0 robot goes BACKWARD, 1 robot goes FORWARD
*/

#define PWM_RESOLUTION	8
#define PWM_FREQUENCY	5000

class Motor {

	private:
		uint8_t mSleepPin;	// nSLEEP pin
		uint8_t mEnablePin;	// EN/IN1 pin
		uint8_t mPhasePin;	// PH/IN2 pin
		uint8_t mChannel;
		uint8_t mResolution;
		uint32_t mFrequency;
	
	public:
		Motor(uint8_t pinSleep, uint8_t pinEnable, uint8_t pinPhase, uint8_t channel);
		void goForward();
		void goBackward();
		void stop();
		void setSpeed(float speed);
		void setFrequency(uint32_t frequency);
		void setResolution(uint8_t resolution);
};

Motor::Motor(uint8_t pinSleep, uint8_t pinEnable, uint8_t pinPhase, uint8_t channel) {

	mSleepPin = pinSleep;
	mEnablePin = pinEnable;
	mPhasePin = pinPhase;
	mChannel = channel;

	// set nSLEEP pin
	
	pinMode(mSleepPin, OUTPUT);
	digitalWrite(mSleepPin, 1);

	// set PH pin
	
	pinMode(mPhasePin, OUTPUT);
	goForward();

	// set EN pin

	ledcAttachPin(mEnablePin, mChannel);
	ledcSetup(mChannel, PWM_FREQUENCY, PWM_RESOLUTION);
	stop();
}

void Motor::goForward() {
	digitalWrite(mPhasePin, 1);
}

void Motor::goBackward() {
	digitalWrite(mPhasePin, 0);
}

void Motor::stop() {
	setSpeed(0.0);
}

void Motor::setSpeed(float speed) {
	ledcWrite(mChannel, speed*255);
}
//====================================CLASS=====================================================


Motor MotorLeft(PIN_MOTOR_LEFT_NSLEEP,
                PIN_MOTOR_LEFT_ENABLE,
                PIN_MOTOR_LEFT_PHASE,
                MOTOR_LEFT_CHANNEL);
Motor MotorRight(PIN_MOTOR_RIGHT_NSLEEP,
                 PIN_MOTOR_RIGHT_ENABLE,
                 PIN_MOTOR_RIGHT_PHASE,
                 MOTOR_RIGHT_CHANNEL);


void setup() 
{

}

void loop() 
{
  MotorLeft.goForward();
    MotorLeft.setSpeed(0.5);
    MotorRight.goBackward();
    MotorRight.setSpeed(0.5);

    delay(2000);

    MotorLeft.stop();
    MotorRight.stop();

    delay(2000);

    MotorLeft.goBackward();
    MotorLeft.setSpeed(0.5);
    MotorRight.goForward();
    MotorRight.setSpeed(0.5);

    delay(2000);

    MotorLeft.stop();
    MotorRight.stop();

    delay(2000);
}

