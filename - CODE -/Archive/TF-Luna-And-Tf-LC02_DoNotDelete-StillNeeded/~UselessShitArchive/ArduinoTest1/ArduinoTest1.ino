void setup() {
	Serial.begin(115200);
	Serial.println("Start");
}


int i = 0;


void loop() {
	if(i%2==0 && i%3==0) {
		Serial.println(i);
	}
	
	i=i+1;
	delay(10);
}