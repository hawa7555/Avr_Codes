#define F_CPU 1000000UL
#include<avr/io.h>
void counter_init();
int main()
{
	counter_init();
	while(1)
	{
		
		PORTA=TCNT0;
	}
}

void counter_init()
{
	DDRA=0xff;
	DDRB=DDRB&~(1<<0);
	TCNT0=253;
	TCCR0=0x06;
}
