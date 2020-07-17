#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
void main()
{
	DDRA=DDRA|(1<<0);
	DDRC=DDRC&~(1<<0);
	while(1)
  {
		if(PINC&(1<<0))
	  {
		PORTA=PORTA|(1<<0);
	   }
	else
	 {
		PORTA=PORTA&~(1<<0);
	  }
	}
	
}