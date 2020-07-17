/*
#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
#define PA0_INPUT (DDRA=DDRA &~(1<<0))
#define PC0_OUTPUT (DDRC=DDRC|(1<<0))
#define SW (PINA&(1<<0))
#define LED_ON (PORTC=PORTC|(1<<0))
#define LED_OFF (PORTC=PORTC&~(1<<0))
int main()
{
 PA0_INPUT;
 PC0_OUTPUT;

  while(1)
  {
    if(SW)
	{
	  LED_ON;
	}
	else
	{
	 LED_OFF;
	}
  }
}
*/



#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>

int main()
{
  DDRA=DDRA&~(1<<0); // PA0 input
  DDRC=DDRC|(1<<0); //PC0 Output
  while(1)
  {
    if( (PINA&(1<<0)) ==1)
	{
	 PORTC=PORTC|(1<<0);
	}
	else
	{
	  PORTC=PORTC&~(1<<0);
	}
  }
}
