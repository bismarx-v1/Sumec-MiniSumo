// running @ 16MHz
#include <arduino.h>

#define Delay50 500*0.0625

void setup(){
	DDRB |= (1 << DDB0);     // set pin 0 of Port B as output
  DDRB |= (1 << DDB1);     // set pin 1 of Port B as output
  DDRB |= (1 << DDB2);     // set pin 2 of Port B as output
}

void loop() {
  #if 0
  PORTB |= (1 << PB0);     // set pin 0 of Port B high
  PORTB &= ~(1 << PB1);    // set pin 1 of Port B low
  delay(Delay50);
  PORTB |= (1 << PB1);     // set pin 1 of Port B high
  PORTB &= ~(1 << PB0);    // set pin 0 of Port B low
  delay(Delay50);
  PORTB |= (1 << PB2);     // set pin 2 of Port B high
  PORTB &= ~(1 << PB1);    // set pin 1 of Port B low
  delay(Delay50);
  PORTB |= (1 << PB1);     // set pin 1 of Port B high
  PORTB &= ~(1 << PB2);    // set pin 2 of Port B low
  delay(Delay50);
  #else
  PORTB |= (1 << PB0);     // set pin 0 of Port B high
  PORTB &= ~(1 << PB2);    // set pin 2 of Port B low
  delay(Delay50);
  PORTB |= (1 << PB1);     // set pin 1 of Port B high
  PORTB &= ~(1 << PB0);    // set pin 0 of Port B low
  delay(Delay50);
  PORTB |= (1 << PB2);     // set pin 2 of Port B high
  PORTB &= ~(1 << PB1);    // set pin 1 of Port B low
  delay(Delay50);
  #endif
}
