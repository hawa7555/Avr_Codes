#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
 
void lcd_cmd(char x)
  { 
	 PORTA=x;
	 PORTB=PORTB&~(1<<0);  //RS=0
	 PORTB=PORTB&~(1<<1);  //RW=0
	 PORTB=PORTB|(1<<2);   //EN=1
	 PORTB=PORTB&~(1<<2);  //EN=0
	 _delay_ms(1000);
   }
void init()
  {
	DDRA=0xFF;
	DDRB=DDRB|7;
	lcd_cmd(0x38);
	lcd_cmd(0x0E);
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	
   }
void main()
{
	init();
 }
	 
	
	
