#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
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
	   case 1: PORTC=0b00000100; break;//PC2 BULB
	   case 2: PORTC=0b00001000; break;//PC3 TV
	   case 3: PORTC=0b00010000; break;//PC4 AC
	   case 4: PORTC=0b00100000; break;//PC5 FAN
	   case 5: PORTC=0b00111100; break;// All On
	   case 6: PORTC=0b00000000; break;// All OFF
	   default: PORTC=0b00000000;		//All OFF
	  }        
  }
return 0;
}
