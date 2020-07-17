#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

static int i=0;

void lcd_cmd(char x)
{ 
	PORTA=x&(0xF0);
	PORTA=PORTA&~(1<<0);   //RS=0
	PORTA=PORTA&~(1<<1);   //RW=0
	PORTA=PORTA|(1<<2);    //EN=1
	PORTA=PORTA&~(1<<2);   //EN=0
	_delay_ms(1);
	i++;
	if(i==1)
	{
	  lcd_cmd(x<<4);
	 }
}
	