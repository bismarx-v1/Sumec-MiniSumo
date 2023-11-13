

const int led = 14;

void pin25() {

}

void pin26() {

}

void pin27() {

}


void setup() {
	
  pinMode(25, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(25), pin25, CHANGE);
  
  pinMode(26, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(26), pin26, CHANGE);
  
  pinMode(27, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(27), pin27, CHANGE);
}

void loop() {
	//
}