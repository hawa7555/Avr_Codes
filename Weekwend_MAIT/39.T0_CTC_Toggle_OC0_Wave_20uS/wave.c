#define F_CPU 1000000UL
#include<avr/io.h>
int main()
{
  DDRB=DDRB|(1<<PB3);
 
  	TCNT0=0;
  	OCR0=9;
  	TCCR0=0x19;
  while(1);
}
