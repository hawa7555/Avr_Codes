#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
void main()
{
	DDRA=0b11111111;
	//DDRA=DDRA|(1<<0);
	while(1)
	{
		//PORTA=PORTA|(1<<0);
		PORTA=0xFF;
		_delay_ms(12);
		//PORTA=PORTA&~(1<<0);
		PORTA=0x00;
		_delay_ms(12);
	}
}
