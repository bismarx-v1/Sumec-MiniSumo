//const int LEDPin = 48;
const int LEDPin1 = 47;

const int MOTORS_LeftSpeed = 14;
const int MOTORS_Left = 12;
const int MOTORS_RightSpeed = 21;
const int MOTORS_Right = 13;
const int nSLEEP = 11;

void setup() {

  pinMode(LEDPin1, OUTPUT);
  pinMode(MOTORS_Left, OUTPUT);
  pinMode(MOTORS_Right, OUTPUT);
  pinMode(MOTORS_LeftSpeed, OUTPUT);
  pinMode(MOTORS_RightSpeed, OUTPUT);
  pinMode(nSLEEP, OUTPUT);


}



void loop() {

  digitalWrite(MOTORS_RightSpeed, HIGH);  //set speed for right motor
  digitalWrite(MOTORS_Right, HIGH);
  digitalWrite(MOTORS_LeftSpeed, HIGH);  //set speed for right motor
  digitalWrite(MOTORS_Left, LOW);
  digitalWrite(nSLEEP, HIGH);  //set standby to high
  //digitalWrite(LEDPin1, HIGH);


}
