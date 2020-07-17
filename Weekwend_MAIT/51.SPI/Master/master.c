#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
int main()
{
  DDRB=DDRB|(1<<5)|(1<<7);
  SPCR=SPCR|(1<<SPE)|(1<<DORD)|(1<<MSTR);
  SPDR='A';
  while( (SPSR&(1<<SPIF))==0);
return 0;
}
