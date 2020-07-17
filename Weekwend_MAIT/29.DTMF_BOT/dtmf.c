#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
#define Forward  0b00010100
#define Backward 0b00101000
#define Left 	 0b00000100
#define Right    0b00100000
#define Stop 	 0b00000000
#define BOT PORTC
int main()
{
  DDRA=DDRA &~ 0x0F;
  DDRC=DDRC | (0x0F<<2);
  int x;
  while(1)
	{
	  x=PINA;
	  x=x & 0x0F;
	  switch(x)
	  {
	   case 2: BOT=Forward;break;
	    case 4: BOT=Left;break;
		 case 6: BOT=Right;break;
		  case 8: BOT=Backward;break;
		   case 5: BOT=Stop;break;
 			default: BOT=Stop;
	  }        
  }
return 0;
}
