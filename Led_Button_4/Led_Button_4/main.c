#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
void main()
{
  DDRA=DDRA|(0x0F);
  DDRC=DDRC&~(0x0F);
 while(1)
{
  if(PINC&(1<<0))
  { 
	PORTA=PORTA|(1<<0);
  }
  else if(PINC&(1<<1))
  {
	  PORTA=PORTA|(1<<1);
  }
  else if(PINC&(1<<2))
  {
	  PORTA=PORTA|(1<<2);
  }
  else if(PINC&(1<<3))
  {
	  PORTA=PORTA|(1<<3);
  }
  else
   {
	  PORTA=PORTA&~(0x0F);
	 }
  }
}