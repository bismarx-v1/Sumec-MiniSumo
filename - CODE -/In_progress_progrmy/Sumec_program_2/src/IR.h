#define IR_IRPin 39

void IR_Wait() {
	while(analogRead(IR_IRPin)!=0) {
		delay(10);
	}
	return;
}