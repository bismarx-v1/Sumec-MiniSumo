//dulezity #define
#define MOTORS_LeftSpeed 5
#define MOTORS_LeftBackward 18
#define MOTORS_LeftForward 19
#define MOTORS_RightSpeed 15
#define MOTORS_RightBackward 2
#define MOTORS_RightForward 4
#define MOTORS_STBY 23


//funkce ktera ze ma zavolat jednou v void setup()
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

//brake - zastavi motory
void MOTORS_Brake() {
  digitalWrite(MOTORS_LeftForward,LOW);
  digitalWrite(MOTORS_RightForward,LOW);
  digitalWrite(MOTORS_LeftBackward,LOW);
  digitalWrite(MOTORS_RightBackward,LOW);
  ledcWrite(0, 255);
  ledcWrite(1, 255);
  digitalWrite(MOTORS_STBY, HIGH);
}



//universalni funkce pro motory
void MOTORS_Go(int MOTORS_SpeedLeft, int MOTORS_SpeedRight) {//speed is from -255 to 255
  if(MOTORS_SpeedLeft < -255) {
    MOTORS_SpeedLeft = -255;
  }
  else {
    if(MOTORS_SpeedLeft > 255) {
      MOTORS_SpeedLeft = 255;
    }
    else {
      if(MOTORS_SpeedLeft < 0) {
        digitalWrite(MOTORS_LeftForward,LOW);
        digitalWrite(MOTORS_LeftBackward,HIGH);
      }
      else {
        if(MOTORS_SpeedLeft > 0) {
          digitalWrite(MOTORS_LeftForward,HIGH);
          digitalWrite(MOTORS_LeftBackward,LOW);
        }
        else {
          digitalWrite(MOTORS_LeftForward,LOW);
          digitalWrite(MOTORS_LeftBackward,LOW);
          MOTORS_SpeedLeft = 255;
        }
      }
    }
  }
  
  if(MOTORS_SpeedRight < -255) {
    MOTORS_SpeedRight = -255;
  }
  else {
    if(MOTORS_SpeedRight > 255) {
      MOTORS_SpeedRight = 255;
    }
    else {
      if(MOTORS_SpeedRight < 0) {
        digitalWrite(MOTORS_RightForward,LOW);
        digitalWrite(MOTORS_RightBackward,HIGH);
      }
      else {
        if(MOTORS_SpeedRight > 0) {
          digitalWrite(MOTORS_RightForward,HIGH);
          digitalWrite(MOTORS_RightBackward,LOW);
        }
        else {
          digitalWrite(MOTORS_RightForward,LOW);
          digitalWrite(MOTORS_RightBackward,LOW);
          MOTORS_SpeedRight = 255;
        }
      }
    }
  }
  if(MOTORS_SpeedLeft < 0) {
    MOTORS_SpeedLeft = MOTORS_SpeedLeft*-1;
  }
  
  if(MOTORS_SpeedRight < 0) {
    MOTORS_SpeedRight = MOTORS_SpeedRight*-1;
  }
  
  ledcWrite(0, MOTORS_SpeedLeft);
  ledcWrite(1, MOTORS_SpeedRight);
  digitalWrite(MOTORS_STBY, HIGH);
  return;
}


//normalni void setup() s funkci MOTORS_Setup()
void setup() {
  MOTORS_Setup();

}


//normalni void loop()
void loop() {
  
}
