/*
 * DDUC.c
 *
 * Created: 10/17/2019 11:47:31 AM
 * Author : Harshal
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 8000000UL
int main(void)
{
	DDRB |= (31<<0);
	//PORTB &= ~(15<<0);
    /* Replace with your application code */
    while (1) {
		PORTB &= ~(31<<0);
		
		for(int i=0; i<4; i++) {
		PORTB |= (1<<i);
		if(!(i % 2)) {
			PORTB |= (1<<4);
		}
		else {
			PORTB &= ~(1<<4); 
			}
		_delay_ms(10000);
		//PORTB &= ~(1<<i);
		//_delay_ms(2000);
		}
	}
}

