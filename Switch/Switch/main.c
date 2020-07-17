#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
void main()
{
	DDRB=DDRB|0x01;
	if(PORTB==(PORTB|0x01))
	{
	 //DDRA=DDRA|0x01;
	 //PORTA=PORTA|0x01;
	 DDRA=0xFF;
	 PORTA=0xFF;
	 }
}

