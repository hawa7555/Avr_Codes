#define F_CPU 8000000
#include<avr/io.h>
#include<util/delay.h>


void Spi_init()
{
	DDRB=DDRB|(1<<PB5)|(1<<PB7);
	SPCR=SPCR|(1<<SPE)|(1<<MSTR)|(1<<DORD);
}

void Spi_transmit(char *x)
{
//PORTB=PORTB&~(1<<PB4);
while(*x!='\0')
{
	SPDR=*x;
	while(!(SPSR&(1<<SPIF)));
	_delay_ms(10);
	x++;
 }
}
 void main()
 {
	 Spi_init();
   // while(1)
	 //{
		 Spi_transmit("Harshal");
      // }
	   
   
 }