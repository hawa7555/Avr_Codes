#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
int main()
{
  DDRD=0xff;
  SPCR=SPCR|(1<<SPE)|(1<<DORD);
  while(1)
  {
   while( (SPSR&(1<<SPIF))==0);
   PORTD=SPDR;
  }
return 0;
}
