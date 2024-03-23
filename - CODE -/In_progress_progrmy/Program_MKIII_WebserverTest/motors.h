
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