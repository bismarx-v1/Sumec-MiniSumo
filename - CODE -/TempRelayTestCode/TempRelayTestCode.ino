const int SdaBoard = 14;
const int XShut1 = 32;
const int XShut2 = 33;
const int SdaLuna1 = 26;
const int SdaLuna2 = 27;
const int MODE = 1; //0 = analog; !0 = digital

void PinsSet(int Sda, int XS1, int XS2) {
  digitalWrite(SdaBoard, Sda);
  digitalWrite(XShut1, XS1);
  digitalWrite(XShut2, XS2);
  delay(500);
  Serial.println("===========================");
  Serial.println("Sda\tXShut1\tXShut2");
  Serial.print(Sda);
  Serial.print("\t");
  Serial.print(XS1);
  Serial.print("\t");
  Serial.println(XS2);
  Serial.print("\t");
  Serial.println("Luna1\tLuna2");
  Serial.print("\t");
  if(MODE==0) {
    Serial.print(analogRead(SdaLuna1));
  } else {
   Serial.print(digitalRead(SdaLuna1)); 
  }
  Serial.print("\t");
  if(MODE==0) {
    Serial.println(analogRead(SdaLuna2));
  } else {
   Serial.println(digitalRead(SdaLuna2)); 
  }
  Serial.println("===========================");
}

void setup() {
  pinMode(SdaBoard, OUTPUT);
  pinMode(XShut1, OUTPUT);
  pinMode(XShut2,OUTPUT);
  pinMode(SdaLuna1, INPUT);
  pinMode(SdaLuna2, INPUT);
  
  Serial.begin(115200);
  delay(2000);
  Serial.println(millis());
  delay(1000);
}

void loop() {
  Serial.println("New Loop");
  
  PinsSet(0, 0, 0);
  delay(4500);
  
  PinsSet(0, 0, 1);
  delay(4500);
  
  PinsSet(0, 1, 0);
  delay(4500);
  
  PinsSet(0, 1, 1);
  delay(4500);
  
  
  PinsSet(1, 0, 0);
  delay(4500);
  
  PinsSet(1, 0, 1);
  delay(4500);
  
  PinsSet(1, 1, 0);
  delay(4500);
  
  PinsSet(1, 1, 1);
  delay(4500);
}
