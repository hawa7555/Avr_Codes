#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
void main()
{
	DDRA=0b11111111;
	while(1)
	{
		PORTA=0b11111111;
	    //PORTA=0xFF;
	    _delay_ms(1000);
		PORTA=0b00000000;
		//PORTA=0x00;
		_delay_ms(1000);
	 }
}
