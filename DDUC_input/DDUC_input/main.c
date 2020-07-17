/*
 * DDUC_input.c
 *
 * Created: 10/17/2019 1:17:04 PM
 * Author : Harshal
 */ 

#include <avr/io.h>


int main(void)
{
	DDRB &= ~(1<<0);
	DDRB |= (1<<1);
    /* Replace with your application code */
    while (1) 
    {
		while(PINB & 0x01)
		{
			PORTB |= (1<<1);
    }
	PORTB &= ~(1<<1);
}
}

