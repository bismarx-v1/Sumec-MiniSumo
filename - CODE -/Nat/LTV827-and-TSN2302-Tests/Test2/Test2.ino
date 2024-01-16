//gnd -> gnd
//sda -> 14
//Luna1 -> 32
//Luna2 -> 33
//XS1 -> 26
//XS2 -> 25

const int sda = 14;
const int Luna1 = 32;
const int Luna2 = 33;
const int XS1 = 26;
const int XS2 = 25;

void setup() {
	Serial.begin(115200);
	pinMode(sda, OUTPUT);
	pinMode(XS1, OUTPUT);
	pinMode(XS2, OUTPUT);
	pinMode(Luna1, INPUT);
	pinMode(Luna2, INPUT);
	digitalWrite(sda, 0);
	digitalWrite(XS1, 0);
	digitalWrite(XS2, 0);
	delay(2000);
	Serial.println("START");
}

void loop() {
	Serial.println("New loop");
	Serial.println(millis());
	
	digitalWrite(sda, 0);	//sda=0, XS1=0, XS2=0
	digitalWrite(XS1, 0);
	digitalWrite(XS2, 0);
	Serial.println("sda=0, XS1=0, XS2=0");
	delay(100);
	
	Serial.print("Luna1: \t");
	Serial.println(digitalRead(Luna1));
	Serial.print("Luna2: \t");
	Serial.println(digitalRead(Luna2));
	Serial.println("===============\n");
	delay(1000);
	
	
	digitalWrite(sda, 1);	//sda=1, XS1=0, XS2=0
	digitalWrite(XS1, 0);
	digitalWrite(XS2, 0);
	Serial.println("sda=1, XS1=0, XS2=0");
	delay(100);
	
	Serial.print("Luna1: \t");
	Serial.println(digitalRead(Luna1));
	Serial.print("Luna2: \t");
	Serial.println(digitalRead(Luna2));
	Serial.println("===============\n");
	delay(1000);
	
	
	digitalWrite(sda, 0);	//sda=0, XS1=1, XS2=0
	digitalWrite(XS1, 1);
	digitalWrite(XS2, 0);
	Serial.println("sda=0, XS1=1, XS2=0");
	delay(100);
	
	Serial.print("Luna1: \t");
	Serial.println(digitalRead(Luna1));
	Serial.print("Luna2: \t");
	Serial.println(digitalRead(Luna2));
	Serial.println("===============\n");
	delay(1000);
	
	
	digitalWrite(sda, 0);	//sda=0, XS1=0, XS2=1
	digitalWrite(XS1, 0);
	digitalWrite(XS2, 1);
	Serial.println("sda=0, XS1=0, XS2=1");
	delay(100);
	
	Serial.print("Luna1: \t");
	Serial.println(digitalRead(Luna1));
	Serial.print("Luna2: \t");
	Serial.println(digitalRead(Luna2));
	Serial.println("===============\n");
	delay(1000);
	
	
	
	
	digitalWrite(sda, 1);	//sda=1, XS1=1, XS2=0
	digitalWrite(XS1, 1);
	digitalWrite(XS2, 0);
	Serial.println("sda=1, XS1=1, XS2=0");
	delay(100);
	
	Serial.print("Luna1: \t");
	Serial.println(digitalRead(Luna1));
	Serial.print("Luna2: \t");
	Serial.println(digitalRead(Luna2));
	Serial.println("===============\n");
	delay(1000);
	
	
	digitalWrite(sda, 1);	//sda=1, XS1=0, XS2=1
	digitalWrite(XS1, 0);
	digitalWrite(XS2, 1);
	Serial.println("sda=1, XS1=0, XS2=1");
	
	Serial.print("Luna1: \t");
	Serial.println(digitalRead(Luna1));
	Serial.print("Luna2: \t");
	Serial.println(digitalRead(Luna2));
	Serial.println("===============\n");
	delay(1000);
	
	
	digitalWrite(sda, 0);	//sda=0, XS1=1, XS2=1
	digitalWrite(XS1, 1);
	digitalWrite(XS2, 1);
	Serial.println("sda=0, XS1=1, XS2=1");
	
	Serial.print("Luna1: \t");
	Serial.println(digitalRead(Luna1));
	Serial.print("Luna2: \t");
	Serial.println(digitalRead(Luna2));
	Serial.println("===============\n");
	delay(1000);
	
	
	
	
	digitalWrite(sda, 1);	//sda=1, XS1=1, XS2=1
	digitalWrite(XS1, 1);
	digitalWrite(XS2, 1);
	Serial.println("sda=1, XS1=1, XS2=1");
	
	Serial.print("Luna1: \t");
	Serial.println(digitalRead(Luna1));
	Serial.print("Luna2: \t");
	Serial.println(digitalRead(Luna2));
	Serial.println("===============\n");
	delay(1000);
}