#define F_CPU 14745600UL
#include <avr/io.h>
#include <util/delay.h>

void tim_init(float volt)
{
	TCCR0A=0x61;
	TCNT0=0;
	TIFR0=TIFR0|(1<<TOV0);
	OCR0A=(int)(volt*255/5);
}

int  main()
{
	//DDRA=DDRA|(1<<0);
	DDRC=DDRC|(1<<PB0);
	
	while(1)
	{
	tim_init(5);
	_delay_ms(1000);	
	}	
}