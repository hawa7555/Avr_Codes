#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
#define PA0_INPUT (DDRA=DDRA &~(1<<0))
#define PA1_INPUT (DDRA=DDRA &~(1<<1))

#define PC0_OUTPUT (DDRC=DDRC|(1<<0))
#define PC1_OUTPUT (DDRC=DDRC|(1<<1))

#define SW0 (PINA&(1<<0))
#define SW1 (PINA&(1<<1))

#define LED0_ON (PORTC=PORTC|(1<<0))
#define LED1_ON (PORTC=PORTC|(1<<1))

#define LED0_OFF (PORTC=PORTC&~(1<<0))
#define LED1_OFF (PORTC=PORTC&~(1<<1))
int main()
{
 PA0_INPUT;
 PA1_INPUT;
 PC0_OUTPUT;
 PC1_OUTPUT;

  while(1)
  {
    if(SW0)
	{
	  LED0_ON;
	}
	else if(SW1)
	{
	 LED1_ON;
	}
	else
	{
	  LED0_OFF;
	  LED1_OFF;
	}
  }
}
/*



#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>

int main()
{
  DDRA=DDRA&~(1<<0); // PA0 input
  DDRC=DDRC|(1<<); //PC0 Output
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
*/
	
