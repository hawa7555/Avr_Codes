#define F_CPU 1000000UL
#include<avr/io.h>
#include<util/delay.h>
int main()
{
int i;
  DDRB=DDRB|(1<<PB3);
 
  	TCNT0=0;
  	TCCR0=0x69;
	while(1)
	{
		for(i=0;i<=255;i++)
		{
	  		OCR0=i;
	  		_delay_ms(10);
		}
   }
  while(1);
}
