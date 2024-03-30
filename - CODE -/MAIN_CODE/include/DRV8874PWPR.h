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

class DRV8874PWPR {
	private:
		const uint8_t nSleep_Pin = 11;					// nSleep pin is shared
		const uint8_t Driver_Pin[2][2] = {{14, 12}, {21, 13}};	//	Pins in order: {{"EN", "PH"}, {"EN", "PH"}}
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