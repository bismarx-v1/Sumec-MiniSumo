
//important #defines
#define MOTORS_LeftSpeed 14
#define MOTORS_Left 12
#define MOTORS_RightSpeed 21
#define MOTORS_Right 13
#define nSLEEP 11

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



void setup() {

  MOTORS_Setup();

  pinMode(MOTORS_Left, OUTPUT);
  pinMode(MOTORS_Right, OUTPUT);
  pinMode(MOTORS_LeftSpeed, OUTPUT);
  pinMode(MOTORS_RightSpeed, OUTPUT);
  pinMode(nSLEEP, OUTPUT);


}

void MOTORS_Go(int MOTORS_SpeedLeft, int MOTORS_SpeedRight) 
{

  switch(MOTORS_SpeedLeft)
  {
    case 255:
      digitalWrite(MOTORS_LeftSpeed, HIGH);  //set speed for right motor
      digitalWrite(MOTORS_Left, LOW);
      break;

    case 0:
      digitalWrite(MOTORS_LeftSpeed, LOW);  //set speed for right motor
      digitalWrite(MOTORS_Left, LOW);
      break;

    case -255:
      digitalWrite(MOTORS_LeftSpeed, HIGH);  //set speed for right motor
      digitalWrite(MOTORS_Left, HIGH);   
  }

    switch(MOTORS_SpeedRight)
  {
    case 255:
      digitalWrite(MOTORS_RightSpeed, HIGH);  //set speed for right motor
      digitalWrite(MOTORS_Right, HIGH);
      break;

    case 0:
      digitalWrite(MOTORS_RightSpeed, LOW);  //set speed for right motor
      digitalWrite(MOTORS_Right, LOW);
      break;

    case -255:
      digitalWrite(MOTORS_RightSpeed, HIGH);  //set speed for right motor
      digitalWrite(MOTORS_Right, LOW);
      break;   
  }

  
  digitalWrite(nSLEEP, HIGH);
}

void loop() {


MOTORS_Go(255, 255);

delay(1000);

MOTORS_Go(0, 0);

delay(1000);

MOTORS_Go(-255, -255);

delay(1000);

}
