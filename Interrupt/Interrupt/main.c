#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
void int0_init()
{
	SREG=SREG|(1<<7);
	//sei();
	GICR=GICR|(1<<INT0);
	MCUCR=MCUCR|(3<<0);
 }
 
ISR(INT0_vect)
{
	for(int i=0;i<10;i++)
	{
	 PORTA=PORTA|(1<<0);
	 _delay_ms(650);
	 PORTA=PORTA&~(1<<0);
	 _delay_ms(650);
	 }
}
 int main()
 {
	 int0_init();
	 DDRA=DDRA|(1<<0);
	 DDRB=DDRB|(1<<0);
	 while(1)
	 {
	   PORTB=PORTB|(1<<0);
	  _delay_ms(700);
	  PORTB=PORTB&~(1<<0);
	  _delay_ms(700);
	 }
 }