
#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
int main()
{
 int i;
  DDRA=0b11111111;
  while(1)
  {
   for(i=0;i<=7;i++)
   {
    PORTA=(1<<i);
	_delay_ms(100);
   }
  }
return 0;
}

/*
	PORTA=(1<<1)
	_delay_ms(100);
	PORTA=(1<<2)
	_delay_ms(100);
	PORTA=(1<<3)
	_delay_ms(100);
	PORTA=(1<<4)
	_delay_ms(100);
	PORTA=(1<<5)
	_delay_ms(100);
	PORTA=(1<<6)
	_delay_ms(100);
	PORTA=(1<<7)
	_delay_ms(100);
*/
