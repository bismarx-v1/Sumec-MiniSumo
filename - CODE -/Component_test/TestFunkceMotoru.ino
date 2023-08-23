#define MOTORS_LeftSpeed 5
#define MOTORS_LeftBackward 18
#define MOTORS_LeftForward 19
#define MOTORS_RightSpeed 15
#define MOTORS_RightBackward 2
#define MOTORS_RightForward 4
#define MOTORS_STBY 23
#define Button 13
bool Go = false;
int BPressed = 0;



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

//brake
void MOTORS_Brake() {
  digitalWrite(MOTORS_LeftForward,LOW);
  digitalWrite(MOTORS_RightForward,LOW);
  digitalWrite(MOTORS_LeftBackward,LOW);
  digitalWrite(MOTORS_RightBackward,LOW);
  ledcWrite(0, 255);
  ledcWrite(1, 255);
  digitalWrite(MOTORS_STBY, HIGH);
}



//universal function for both motors
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
        Serial.println("LeftBack");
      }
      else {
        if(MOTORS_SpeedLeft > 0) {
          digitalWrite(MOTORS_LeftForward,HIGH);
          digitalWrite(MOTORS_LeftBackward,LOW);
          Serial.println("LeftFwd");
        }
        else {
          digitalWrite(MOTORS_LeftForward,LOW);
          digitalWrite(MOTORS_LeftBackward,LOW);
          MOTORS_SpeedLeft = 255;
          Serial.println("LeftBrake");
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
        Serial.println("RightBack");
      }
      else {
        if(MOTORS_SpeedRight > 0) {
          digitalWrite(MOTORS_RightForward,HIGH);
          digitalWrite(MOTORS_RightBackward,LOW);
          Serial.println("RightFwd");
        }
        else {
          digitalWrite(MOTORS_RightForward,LOW);
          digitalWrite(MOTORS_RightBackward,LOW);
          MOTORS_SpeedRight = 255;
          Serial.println("RightBrake");
        }
      }
    }
  }
  ledcWrite(0, MOTORS_SpeedLeft);
  ledcWrite(1, MOTORS_SpeedRight);
  digitalWrite(MOTORS_STBY, HIGH);
  return;
}



void setup() {
  Serial.begin(9600);
  MOTORS_Setup();
  
}



void loop() {
  BPressed = digitalRead(Button);
  if(BPressed==1) {
    if(Go==true) {
      Go=false;
      while(BPressed==1) {
        BPressed = digitalRead(Button);
        delay(10);
      }
      MOTORS_Go(-255, -255);
      Serial.println("Back");
      
      Serial.println("=============");
    }
    else {
      if(Go==false) {
        Go=true;
        while(BPressed==1) {
          BPressed = digitalRead(Button);
          delay(10);
        }
        MOTORS_Brake();
        Serial.println("Brake");
        Serial.println("=============");
      }
    }
  }
}
