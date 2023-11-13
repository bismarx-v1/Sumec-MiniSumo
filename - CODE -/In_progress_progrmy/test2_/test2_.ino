//important #defines
#define MOTORS_LeftSpeed 11
#define MOTORS_LeftBackward 9
#define MOTORS_LeftForward 10
#define MOTORS_RightSpeed 21
#define MOTORS_RightBackward 13
#define MOTORS_RightForward 14
#define MOTORS_STBY 12

#define led 15

//setup function
void MOTORS_Setup() {
  ledcSetup(0, 5000, 8);
  ledcSetup(1, 5000, 8);
  pinMode(MOTORS_LeftBackward, OUTPUT);
  pinMode(MOTORS_LeftForward, OUTPUT);
  pinMode(MOTORS_RightBackward, OUTPUT);
  pinMode(MOTORS_RightForward, OUTPUT);
  pinMode(MOTORS_STBY, OUTPUT);
  ledcAttachPin(MOTORS_LeftSpeed, 0);
  ledcAttachPin(MOTORS_RightSpeed, 1);
}

//brake function
void MOTORS_Brake() {
  digitalWrite(MOTORS_LeftForward, LOW);
  digitalWrite(MOTORS_RightForward, LOW);
  digitalWrite(MOTORS_LeftBackward, LOW);
  digitalWrite(MOTORS_RightBackward, LOW);
  ledcWrite(0, 255);
  ledcWrite(1, 255);
  digitalWrite(MOTORS_STBY, HIGH);
}



//universal motors function
//ex.: MOTORS_Go([SpeedLeft], [SpeedRight]);
//speed can be from -255 to 255

void MOTORS_Go(int MOTORS_SpeedLeft, int MOTORS_SpeedRight) {

  if (MOTORS_SpeedLeft < -255) {  //left motor speed cap -
    MOTORS_SpeedLeft = -255;
  } else if (MOTORS_SpeedLeft > 255) {  //left motor speed cap +
    MOTORS_SpeedLeft = 255;
  }

  if (MOTORS_SpeedLeft < 0) { //if left motor set to go backward
    digitalWrite(MOTORS_LeftForward, LOW);
    digitalWrite(MOTORS_LeftBackward, HIGH);
  } else  if (MOTORS_SpeedLeft > 0) { //if left motor set to go forward
    digitalWrite(MOTORS_LeftForward, HIGH);
    digitalWrite(MOTORS_LeftBackward, LOW);
  } else {  //else left motor will stop
    digitalWrite(MOTORS_LeftForward, LOW);
    digitalWrite(MOTORS_LeftBackward, LOW);
    MOTORS_SpeedLeft = 255;
  }
  

  if (MOTORS_SpeedRight < -255) { //right motor speed cap -
    MOTORS_SpeedRight = -255;
  } else if (MOTORS_SpeedRight > 255) { //right motor speed cap +
    MOTORS_SpeedRight = 255;
  }

  if (MOTORS_SpeedRight < 0) {  //if right motor set to go backward
    digitalWrite(MOTORS_RightForward, LOW);
    digitalWrite(MOTORS_RightBackward, HIGH);
  } else  if (MOTORS_SpeedRight > 0) {  //if right motor set to go forward
    digitalWrite(MOTORS_RightForward, HIGH);
    digitalWrite(MOTORS_RightBackward, LOW);
  } else {  //else right motor will stop
    digitalWrite(MOTORS_RightForward, LOW);
    digitalWrite(MOTORS_RightBackward, LOW);
    MOTORS_SpeedRight = 255;
  }

  if (MOTORS_SpeedLeft < 0) { //if left motor backward
    MOTORS_SpeedLeft = MOTORS_SpeedLeft * -1; //speed *-1 because negative numbers can't be used
  }

  if (MOTORS_SpeedRight < 0) {  //if right motor backward
    MOTORS_SpeedRight = MOTORS_SpeedRight * -1; //speed *-1 because negative numbers can't be used
  }

  ledcWrite(0, MOTORS_SpeedLeft); //set speed for left motor
  ledcWrite(1, MOTORS_SpeedRight);  //set speed for right motor
  digitalWrite(MOTORS_STBY, HIGH);  //set standby to high
}





int LINE_Get(int LINE_Sensor, int LINE_Threshold, int LINE_Mode) {
	switch(LINE_Sensor) {
		case 1:	//Front Left
			switch(LINE_Mode) {	//Mode
				case 0:	//Mode 0
					return (analogRead(32)<LINE_Threshold ? 1: 0);
					break;
					
				case 1:	//Mode 1
					return analogRead(32);
					break;
			}
			break;
			
		case 2:	//Front Right
			switch(LINE_Mode) {	//Mode
				case 0:	//Mode 0
					return (analogRead(33)<LINE_Threshold ? 1: 0);
					break;
					
				case 1:	//Mode 1
					return analogRead(33);
					break;
			}
			break;
			
		case 3:	//Back Left
			switch(LINE_Mode) {	//Mode
				case 0:	//Mode 0
					return (analogRead(5)<LINE_Threshold ? 1: 0);
					break;
					
				case 1:	//Mode 1
					return analogRead(5);
					break;
			}
			break;
			
		case 4:	//Back Right
			switch(LINE_Mode) {	//Mode
				case 0:	//Mode 0
					return (analogRead(35)<LINE_Threshold ? 1: 0);
					break;
					
				case 1:	//Mode 1
					return analogRead(35);
					break;
			}
			break;
		
		default:
			return 0;
			break;
		
	}
	return 0;
}




void setup() {
  Serial.begin(9600);
  MOTORS_Setup();
  pinMode(led, OUTPUT);
}

void loop() {
  Serial.println(LINE_Get(3, 750, 0));
  // MOTORS_Go(255 * -1, 255 * -1);
  digitalWrite(led, HIGH);
  
}
