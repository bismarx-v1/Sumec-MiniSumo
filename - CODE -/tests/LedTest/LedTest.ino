// CDC on boot = 1 ?
#include <arduino.h>
#define ledpin1 47
#define ledpin2 48

void setup() {
	pinMode(ledpin1, OUTPUT);
  pinMode(ledpin2, OUTPUT);
}

void loop() {
	digitalWrite(ledpin1, 1);
  digitalWrite(ledpin2, 1);
}
