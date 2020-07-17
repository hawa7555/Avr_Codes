#define F_CPU 14745600UL
#include<avr/io.h>
#include<util/delay.h>

void uart_init()
{
	UBRR0L = 0x5F;
	UBRR0H = 0x00;
	UCSR0B = 0x98;
	UCSR0C = 0x06;
	UCSR0A = 0x00;

}

void transmit(char *x)
{
	
	while(*x!='\0')
	{
	 while((UCSR0A&(1<<UDRE0))==0);
	 UDR0=*x;
	 _delay_ms(100);
	 x++;
	}
}

void receive()
{
	char data;
	while((UCSR0A&(1<<RXC0))==0);
	data=UDR0;
}

//ISR(USART0_RX_vect)
//{
	
//}

//void int_init()
//{
//	SREG=SREG|(1<<7);
	
//}

void main()
{
	uart_init();
	//int_init();
	while(1)
	{
		transmit("HARSHAL");
	}
}