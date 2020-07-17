#define F_CPU 8000000
#include<avr/io.h>
#include<util/delay.h>

void uart_init();
void rx();

int main()
{
	DDRA=0xFF;
	uart_init();
	while(1)
	{
		rx();
	}

}
void rx()
{
	char a;
	while( (UCSRA &(1<<RXC))==0);
	a=UDR;
	if(a=='a' || a=='A')
	{
		PORTA=0x00;
	}
	if(a=='b' || a=='B')
	{
		PORTA=0x01;
	}
}
void uart_init()
{
	
	UBRRL=0x33;//Fosc=8Mhz,BR=9600
	UCSRB=UCSRB|(1<<RXEN);
	UCSRC=UCSRC|(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);

}
