
#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
void uart_init(void);
void rx();
int main()
{
 uart_init();
 while(1)
 {
  rx();
 }
return 0;
}

void rx()
{
 while( (UCSRA &(1<<RXC))==0);
 PORTA=UDR;
}
void uart_init()
{
 DDRA=0xFF;
 UBRRL=0x33;//Fosc=8Mhz,BR=9600
 UCSRB=UCSRB|(1<<RXEN);
 UCSRC=UCSRC|(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);

}
