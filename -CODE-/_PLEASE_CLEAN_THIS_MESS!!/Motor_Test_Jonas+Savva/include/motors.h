#if 0
#include <Arduino.h>

//important #defines
#define MOTORS_LeftSpeed 39
#define MOTORS_Left 41
#define MOTORS_RightSpeed 42
#define MOTORS_Right 40
#define nSLEEP 38

//setup function
void MOTORS_Setup() {
  pinMode(MOTORS_Left, OUTPUT);
  pinMode(MOTORS_Right, OUTPUT);
  pinMode(MOTORS_LeftSpeed, OUTPUT);
  pinMode(MOTORS_RightSpeed, OUTPUT);
  ledcAttachPin(MOTORS_LeftSpeed, 0);
  ledcAttachPin(MOTORS_RightSpeed, 1);
  pinMode(nSLEEP, OUTPUT);
}



void MOTORS_Go(int MOTORS_SpeedLeft, int MOTORS_SpeedRight) 
{

  if(MOTORS_SpeedLeft > 0)
  {
    analogWrite(MOTORS_LeftSpeed, MOTORS_SpeedLeft);
    digitalWrite(MOTORS_Left, LOW);
  }
  if(MOTORS_SpeedLeft == 0)
  {
    analogWrite(MOTORS_LeftSpeed, 0);
    digitalWrite(MOTORS_Left, LOW);
  }
  if(MOTORS_SpeedLeft < 0)
  {
    analogWrite(MOTORS_LeftSpeed, (MOTORS_SpeedLeft*-1));
    digitalWrite(MOTORS_Left, HIGH);
  }


  if(MOTORS_SpeedRight > 0)
  {
    analogWrite(MOTORS_RightSpeed, MOTORS_SpeedRight);
    digitalWrite(MOTORS_Right, HIGH);
  }
  if(MOTORS_SpeedRight == 0)
  {
    analogWrite(MOTORS_RightSpeed, 0);
    digitalWrite(MOTORS_Right, LOW);
  }
  if(MOTORS_SpeedRight < 0)
  {
    analogWrite(MOTORS_RightSpeed, (MOTORS_SpeedRight*-1));
    digitalWrite(MOTORS_Right, LOW);
  }

  digitalWrite(nSLEEP, HIGH);
  
}
#endif

#if 1
/*
* Motor modes
* 	- Sleep
* 	- Brake
* 	- Reverse
* 	- Forward
* 
* Important variables
* 	- nSleep
* 		- Enables the bridge
* 	- EN
* 		- Sets speed
* 		- Could be called PWM_in
* 	- PH
* 		- Sets Direction
* 
* Truthtable
* ╔═════════╤═══════╤═══════╦═══════════╗
* ║nSpeel	│EN		│PH		║Status		║
* ╠═════════╪═══════╪═══════╬═══════════╣
* ║0		│any	│any	║Sleep		║
* ╟─────────┼───────┼───────╫───────────╢
* ║1		│0		│any	║Brake		║
* ╟─────────┼───────┼───────╫───────────╢
* ║1		│1		│0		║Backward	║
* ╟─────────┼───────┼───────╫───────────╢
* ║1		│1		│1		║Forward	║
* ╚═════════╧═══════╧═══════╩═══════════╝
* this means that if pwm is OFF, robot BRAKES
* if PH is 0 robot goes BACKWARD, 1 robot goes FORWARD
*/
#include <Arduino.h>

class DRV8874PWPR {
	private:
		const uint8_t nSleep_Pin = 38;					// nSleep pin is shared
		const uint8_t Driver_Pin[2][2] = {{42, 40}, {39, 41}};	//	Pins in order: {{"EN", "PH"}, {"EN", "PH"}}
	public:
		uint8_t LedcChannelLeft = 0;
		uint8_t LedcChannelRight = 1;
		DRV8874PWPR(uint16_t LedcFreq, uint8_t LedcRes);
		void left(int16_t Speed);
		void right(int16_t Speed);
		
};

DRV8874PWPR::DRV8874PWPR(uint16_t LedcFreq, uint8_t LedcRes) {	// Somewhat standard values are "5000" for "LedcFreq" and "8" bits for "LedcRes"
	/****************\
	*    pinModes    *
	\****************/
	pinMode(nSleep_Pin, OUTPUT);
	
	ledcSetup(LedcChannelLeft, LedcFreq, LedcRes);	// <pinModes left>
	ledcAttachPin(Driver_Pin[0][0], LedcChannelLeft);
	pinMode(Driver_Pin[0][1], OUTPUT);				// </pinModes left>
	
	ledcSetup(LedcChannelRight, LedcFreq, LedcRes);	// <pinModes right>
	ledcAttachPin(Driver_Pin[1][0], LedcChannelRight);
	pinMode(Driver_Pin[1][1], OUTPUT);				// </pinModes right>
	/*****************\
	*    /pinModes    *
	\*****************/
	
	digitalWrite(nSleep_Pin, 1);	// Sets nSleep to HIGH because we never sleep
}

void DRV8874PWPR::left(int16_t Speed) {
	if(Speed>255) {				// <Speed limits>
		Speed = 255;
	} else if(Speed<-255) {
		Speed = -255;
	}							// </SpeedLimits>
	
	if(Speed>0) {			// Forward
		digitalWrite(Driver_Pin[0][1], 0);
	} else if(Speed<0) {	// Backward
		digitalWrite(Driver_Pin[0][1], 1);
	} else {				// Stop
		
	}
	
	if(Speed<0) {
		Speed = Speed * -1;
	}
	
	ledcWrite(LedcChannelLeft, Speed);
}

void DRV8874PWPR::right(int16_t Speed) {
	if(Speed>255) {				// <Speed limits>
		Speed = 255;
	} else if(Speed<-255) {
		Speed = -255;
	}							// </SpeedLimits>
	
	if(Speed>0) {			// Forward
		digitalWrite(Driver_Pin[1][1], 1);
	} else if(Speed<0) {	// Backward
		digitalWrite(Driver_Pin[1][1], 0);
	} else {				// Stop
		
	}
	
	if(Speed<0) {
		Speed = Speed * -1;
	}
	
	ledcWrite(LedcChannelRight, Speed);
}
#endif