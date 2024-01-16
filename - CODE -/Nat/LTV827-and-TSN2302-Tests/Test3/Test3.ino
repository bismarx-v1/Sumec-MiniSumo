const int sda1 = 14;
const int sda2 = 27;
const int Luna1 = 32;
const int Luna2 = 33;
const int XS1 = 26;
const int XS2 = 25;
const int MODE = 0;	//0=analog; 1=digital

//gnd -> gnd
//sda -> 14
//Luna1 -> 32
//Luna2 -> 33
//XS1 -> 26
//XS2 -> 25

void setup() {
	Serial.begin(115200);
	pinMode(sda1, OUTPUT);
	pinMode(sda2, OUTPUT);
	pinMode(XS1, OUTPUT);
	pinMode(XS2, OUTPUT);
	pinMode(Luna1, INPUT);
	pinMode(Luna2, INPUT);
	digitalWrite(sda1, 0);	//sda=0, XS1=0, XS2=0;
	digitalWrite(XS1, 0);
	digitalWrite(XS2, 0);
	delay(2000);
	Serial.println("START");
}

void loop() {
	Serial.println("New loop");
	Serial.println(millis());
	
	digitalWrite(sda1, 0);
	digitalWrite(sda2, 0);
	digitalWrite(XS1, 0);
	digitalWrite(XS2, 0);
	Serial.println("sda=0, XS1=0, XS2=0");
	delay(100);
	
	Serial.print("Luna1: \t");
	if(MODE==0) {
		Serial.println(analogRead(Luna1));
	} else if(MODE==1) {
		Serial.println(digitalRead(Luna1));
	}
	Serial.print("Luna2: \t");
	if(MODE==0) {
		Serial.println(analogRead(Luna2));
	} else if(MODE==1) {
		Serial.println(digitalRead(Luna2));
	}
	Serial.println("===============\n");
	delay(5000);
	
	
	digitalWrite(sda1, 1);
	digitalWrite(sda2, 1);
	digitalWrite(XS1, 0);
	digitalWrite(XS2, 0);
	Serial.println("sda=1, XS1=0, XS2=0");
	delay(100);
	
	Serial.print("Luna1: \t");
	if(MODE==0) {
		Serial.println(analogRead(Luna1));
	} else if(MODE==1) {
		Serial.println(digitalRead(Luna1));
	}
	Serial.print("Luna2: \t");
	if(MODE==0) {
		Serial.println(analogRead(Luna2));
	} else if(MODE==1) {
		Serial.println(digitalRead(Luna2));
	}
	Serial.println("===============\n");
	delay(5000);
	
	
	digitalWrite(sda1, 0);
	digitalWrite(sda2, 0);
	digitalWrite(XS1, 1);
	digitalWrite(XS2, 0);
	Serial.println("sda=0, XS1=1, XS2=0");
	delay(100);
	
	Serial.print("Luna1: \t");
	if(MODE==0) {
		Serial.println(analogRead(Luna1));
	} else if(MODE==1) {
		Serial.println(digitalRead(Luna1));
	}
	Serial.print("Luna2: \t");
	if(MODE==0) {
		Serial.println(analogRead(Luna2));
	} else if(MODE==1) {
		Serial.println(digitalRead(Luna2));
	}
	Serial.println("===============\n");
	delay(5000);
	
	
	digitalWrite(sda1, 0);
	digitalWrite(sda2, 0);
	digitalWrite(XS1, 0);
	digitalWrite(XS2, 1);
	Serial.println("sda=0, XS1=0, XS2=1");
	delay(100);
	
	Serial.print("Luna1: \t");
	if(MODE==0) {
		Serial.println(analogRead(Luna1));
	} else if(MODE==1) {
		Serial.println(digitalRead(Luna1));
	}
	Serial.print("Luna2: \t");
	if(MODE==0) {
		Serial.println(analogRead(Luna2));
	} else if(MODE==1) {
		Serial.println(digitalRead(Luna2));
	}
	Serial.println("===============\n");
	delay(5000);
	
	
	
	
	digitalWrite(sda1, 1);
	digitalWrite(sda2, 1);
	digitalWrite(XS1, 1);
	digitalWrite(XS2, 0);
	Serial.println("sda=1, XS1=1, XS2=0");
	delay(100);
	
	Serial.print("Luna1: \t");
	if(MODE==0) {
		Serial.println(analogRead(Luna1));
	} else if(MODE==1) {
		Serial.println(digitalRead(Luna1));
	}
	Serial.print("Luna2: \t");
	if(MODE==0) {
		Serial.println(analogRead(Luna2));
	} else if(MODE==1) {
		Serial.println(digitalRead(Luna2));
	}
	Serial.println("===============\n");
	delay(5000);
	
	
	digitalWrite(sda1, 1);
	digitalWrite(sda2, 1);
	digitalWrite(XS1, 0);
	digitalWrite(XS2, 1);
	Serial.println("sda=1, XS1=0, XS2=1");
	
	Serial.print("Luna1: \t");
	if(MODE==0) {
		Serial.println(analogRead(Luna1));
	} else if(MODE==1) {
		Serial.println(digitalRead(Luna1));
	}
	Serial.print("Luna2: \t");
	if(MODE==0) {
		Serial.println(analogRead(Luna2));
	} else if(MODE==1) {
		Serial.println(digitalRead(Luna2));
	}
	Serial.println("===============\n");
	delay(5000);
	
	
	digitalWrite(sda1, 0);	//sda=0, XS1=0, XS2=0
	digitalWrite(sda2, 0);
	digitalWrite(XS1, 1);
	digitalWrite(XS2, 1);
	Serial.println("sda=0, XS1=1, XS2=1");
	
	Serial.print("Luna1: \t");
	if(MODE==0) {
		Serial.println(analogRead(Luna1));
	} else if(MODE==1) {
		Serial.println(digitalRead(Luna1));
	}
	Serial.print("Luna2: \t");
	if(MODE==0) {
		Serial.println(analogRead(Luna2));
	} else if(MODE==1) {
		Serial.println(digitalRead(Luna2));
	}
	Serial.println("===============\n");
	delay(5000);
	
	
	
	
	digitalWrite(sda1, 1);	//sda=1, XS1=0, XS2=0
	digitalWrite(sda2, 1);
	digitalWrite(XS1, 1);
	digitalWrite(XS2, 1);
	Serial.println("sda=1, XS1=1, XS2=1");
	
	Serial.print("Luna1: \t");
	if(MODE==0) {
		Serial.println(analogRead(Luna1));
	} else if(MODE==1) {
		Serial.println(digitalRead(Luna1));
	}
	Serial.print("Luna2: \t");
	if(MODE==0) {
		Serial.println(analogRead(Luna2));
	} else if(MODE==1) {
		Serial.println(digitalRead(Luna2));
	}
	Serial.println("===============\n");
	delay(5000);
}