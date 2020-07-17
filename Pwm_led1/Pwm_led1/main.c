#define F_CPU 14745600UL
#include <avr/io.h>
#include <util/delay.h>

void tim_init(float volt)
{
	TCCR0=0x61;
	TCNT0=0;
	TIFR=TIFR|(1<<TOV0);
	OCR0=(int)(volt*255/5);
}

void main()
{
	//DDRA=DDRA|(1<<0);
	DDRB=DDRB|(1<<PB3);
	tim_init(2.5);
	while(1);
	
}