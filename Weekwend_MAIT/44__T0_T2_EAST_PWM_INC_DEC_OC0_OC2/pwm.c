#define F_CPU 1000000UL
#include<avr/io.h>
#include<util/delay.h>
int main()
{
int i;
  DDRB=DDRB|(1<<PB3);
  DDRD=DDRD|(1<<PD7);
 
  	TCNT0=TCNT2=0;
  	
	while(1)
	{
	    TCCR0=TCCR2=0x69;
		for(i=0;i<=255;i++)
		{
	  		OCR0=OCR2=i;
	  		_delay_ms(10);
		}
		TCCR0=TCCR2=0x79;
		for(i=0;i<=255;i++)
		{
	  		OCR0=OCR2=i;
	  		_delay_ms(10);
		}
		
   }

}
