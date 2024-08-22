// running @16MHz
#include <arduino.h>
#include <avr/eeprom.h>
// #include <avr/io.h>
// #include <avr/interrupt.h>
// #include <avr/power.h>
#include <util/delay.h>

// #define Delay50 500*0.0625


int main() {
	DDRB |= (1 << DDB0);     // set pin 0 of Port B as output
	DDRB |= (1 << DDB1);     // set pin 1 of Port B as output
	DDRB |= (1 << DDB2);     // set pin 2 of Port B as output

	Loop:	// MAIN LOOP
	PORTB |= (1 << PB0);     // set pin 0 of Port B high
	// PORTB |= (1 << PB1);     // set pin 1 of Port B high
	// PORTB |= (1 << PB2);     // set pin 2 of Port B high
	// delay(100);
	// _delay_ms(100);
	_delay_us(500000);
	PORTB &= ~(1 << PB0);    // set pin 0 of Port B low
	// PORTB &= ~(1 << PB1);    // set pin 1 of Port B low
	// PORTB &= ~(1 << PB2);    // set pin 2 of Port B low
	// delay(100);
	// _delay_ms(100);
	_delay_us(500000);
	goto Loop;	// /MAIN LOOP
}
