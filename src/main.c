/*
 * HelloWorld.c
 *
 * Created: 30.12.2017 10:19:11
 * Author : mpue
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile int phase = 0;
#define timefactor 1000

void initISR(void) {
	
	// DDRD &= ~(1 << DDD2);     // Clear the PD2 pin
	// PD2 (PCINT0 pin) is now an input

	DDRD = 1<<PD2;
	PORTD = 1<<PD2;	

	// PORTD |= (1 << PORTD2);    // turn On the Pull-up
	// PD2 is now an input with pull-up enabled

	EICRA |= (0 << ISC00);    // set INT0 to trigger on ANY logic change
	EIMSK |= (1 << INT0);     // Turns on INT0

	sei();                    // turn on interrupts
	
}

ISR(INT0_vect) {
	PORTB = 0xff;
}

int main(void)
{

	DDRB |= (1 << PB0);
	DDRB |= (1 << PB1);
	DDRB |= (1 << PB2);


	initISR();

	while(1) {
		
		if (phase == 0) // red lights
		{
			PORTB = 1;
			_delay_ms(5 * timefactor);
		}		
		else if (phase == 1) // red + orange indicate that it's going to be green, hell yeah!
		{
			PORTB = 3; 
			_delay_ms(1 * timefactor);
		}
		else if (phase == 2) // green, we are good to go!
		{
			PORTB = 4;					
			_delay_ms(5 * timefactor);
		}
		else if (phase == 3) // orange indicates that red is coming, oh no...
		{
			PORTB = 2;					
			_delay_ms(1 * timefactor);
			
		}

		phase = (phase + 1) % 4;
		_delay_ms(100);
		
	}

	return 0;
}

