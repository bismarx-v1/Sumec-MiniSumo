
//important #defines
#define MOTORS_LeftSpeed 11
#define MOTORS_Left 9
#define MOTORS_RightSpeed 21
#define MOTORS_Right 14
#define nSLEEP 12

//setup function
void MOTORS_Setup() {
  pinMode(MOTORS_Left, OUTPUT);
  pinMode(MOTORS_Right, OUTPUT);
  pinMode(MOTORS_LeftSpeed, OUTPUT);
  pinMode(MOTORS_RightSpeed, OUTPUT);
  pinMode(nSLEEP, OUTPUT);
}

//brake function
/*void MOTORS_Brake() {
  digitalWrite(MOTORS_LeftForward, LOW);
  digitalWrite(MOTORS_RightForward, LOW);
  digitalWrite(MOTORS_LeftBackward, LOW);
  digitalWrite(MOTORS_RightBackward, LOW);
  ledcWrite(0, 255);
  ledcWrite(1, 255);
  digitalWrite(MOTORS_STBY, HIGH);
}*/



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
    digitalWrite(MOTORS_Left, LOW);
  } else  if (MOTORS_SpeedLeft > 0) { //if left motor set to go forward
    digitalWrite(MOTORS_Left, HIGH);
  } else {  //else left motor will stop
    digitalWrite(nSLEEP, HIGH);

    MOTORS_SpeedLeft = 255;
  }
  

  if (MOTORS_SpeedRight < -255) { //right motor speed cap -
    MOTORS_SpeedRight = -255;
  } else if (MOTORS_SpeedRight > 255) { //right motor speed cap +
    MOTORS_SpeedRight = 255;
  }

  if (MOTORS_SpeedRight < 0) {  //if right motor set to go backward
    digitalWrite(MOTORS_Right, LOW);
  } else  if (MOTORS_SpeedRight > 0) {  //if right motor set to go forward
    digitalWrite(MOTORS_Right, HIGH);
  } else {  //else right motor will stop
    digitalWrite(nSLEEP, HIGH);
    MOTORS_SpeedRight = 255;
  }

  if (MOTORS_SpeedLeft < 0) { //if left motor backward
    MOTORS_SpeedLeft = MOTORS_SpeedLeft * -1; //speed *-1 because negative numbers can't be used
  }

  if (MOTORS_SpeedRight < 0) {  //if right motor backward
    MOTORS_SpeedRight = MOTORS_SpeedRight * -1; //speed *-1 because negative numbers can't be used
  }

  analogWrite(MOTORS_LeftSpeed, MOTORS_SpeedLeft); //set speed for left motor
  analogWrite(MOTORS_RightSpeed, MOTORS_SpeedRight);  //set speed for right motor
  digitalWrite(nSLEEP, HIGH);  //set standby to high
}
