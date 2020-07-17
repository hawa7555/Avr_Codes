#define F_CPU 14745600
#include <avr/io.h>
#include <util/delay.h>

void main()
{
	DDRA=0xFF;
	DDRB=DDRB|(1<<PB4);
	DDRH=DDRH|(1<<PH6);
	PORTA=PORTA|(1<<2)|(1<<4);
	PORTA=PORTA&~(1<<3);
	PORTA=PORTA&~(1<<5);
	_delay_ms(3000);
	
}

