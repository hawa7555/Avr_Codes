#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

void main()
{
	DDRA=0xFF;
	while(1)
	{
		for(int i=0;i<4;i++)
		{
			PORTA=(1<<i)|(1<<(7-i));
			_delay_ms(500);
		 }
		/* for(int i=0;i<8;i++)
		 {
			 PORTA=(1<<i)|(1<<(7-i));
			 _delay_ms(500);
		 }*/
	}

}
