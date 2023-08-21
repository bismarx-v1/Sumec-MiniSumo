#define SensorPin 32 //define sensor pin
#define LedPin 14  //define led pin
int SensVal = 0;  //create a var for sensor output


void setup() {
  pinMode(LedPin, OUTPUT); //set pinmode for led
  Serial.begin(9600);
}


void loop() {
  int SensVal = analogRead(SensorPin); //read from sensor and store in SensVal
  Serial.println(SensVal);  //print SensVal to serial monitor


  if(SensVal < 3500) {  //compare SensVal to set threshold
    digitalWrite(LedPin, HIGH); //if SensVal is more than set threshold switch led on
  }

  else {
    digitalWrite(LedPin, LOW); //else switch led off
  }

}
