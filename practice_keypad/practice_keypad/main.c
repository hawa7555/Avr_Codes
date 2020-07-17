#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

void lcd_cmd(char x)
{
	PORTD=x&(0xF0);
	PORTD=PORTD&~(1<<0);   //RS=0
	PORTD=PORTD&~(1<<1);   //RW=0
	PORTD=PORTD|(1<<2);    //EN=1
	_delay_ms(1);
	PORTD=PORTD&~(1<<2);   //EN=0
	_delay_ms(1);
	//lcd_cmd(x<<4);
	PORTD=(x<<4)&(0xF0);
	PORTD=PORTD&~(1<<0);   //RS=0
	PORTD=PORTD&~(1<<1);   //RW=0
	PORTD=PORTD|(1<<2);    //EN=1
	_delay_ms(1);
	PORTD=PORTD&~(1<<2);   //EN=0
	_delay_ms(1);
}
void init()
{
	DDRD=0xFF;
	lcd_cmd(0x02);
	lcd_cmd(0x28);
	lcd_cmd(0x0E);
	//lcd_cmd(0x01);
	//lcd_cmd(0x06);
	lcd_cmd(0x80);
}
void lcd_data(char x)
{
	PORTD=x&(0xF0);
	PORTD=PORTD|(1<<0);    //RS=1
	PORTD=PORTD&~(1<<1);   //RW=0
	PORTD=PORTD|(1<<2);    //EN=1
	_delay_ms(1);
	PORTD=PORTD&~(1<<2);   //EN=0
	_delay_ms(1);
	//lcd_data(x<<4);
	PORTD=(x<<4)&(0xF0);
	PORTD=PORTD|(1<<0);    //RS=1
	PORTD=PORTD&~(1<<1);   //RW=0
	PORTD=PORTD|(1<<2);    //EN=1
	_delay_ms(1);
	PORTD=PORTD&~(1<<2);
	_delay_ms(1);
}
/*void display(char x)
{
	lcd_cmd(0x80);
	
	while(*x!='\0')
	{
		lcd_data(*x);
		//lcd_cmd(0x06);
		_delay_ms(300);
		x++;
	}
	
}*/
void keypad()
{
	PORTA=(PORTA|(1<<1)|(1<<2)|(1<<3))&~(1<<0);
	if(!(PINA&(1<<4)))
	{
		lcd_cmd(0x01);
		lcd_data('1');
	}
	if(!(PINA&(1<<5)))
	{
		lcd_cmd(0x01);
		lcd_data('2');
	}
	if(!(PINA&(1<<6)))
	{
		lcd_cmd(0x01);
		lcd_data('3');
	 }
	
	PORTA=(PORTA|(1<<0)|(1<<2)|(1<<3))&~(1<<1);
	if(!(PINA&(1<<4)))
	{
		lcd_cmd(0x01);
		lcd_data('4');
	}
	if(!(PINA&(1<<5)))
	{
		lcd_cmd(0x01);
		lcd_data('5');
	}
	if(!(PINA&(1<<6)))
	{
		lcd_cmd(0x01);
		lcd_data('6');
	}
	
	PORTA=(PORTA|(1<<0)|(1<<1)|(1<<3))&~(1<<2);
	if(!(PINA&(1<<4)))
	{
		lcd_cmd(0x01);
		lcd_data('7');
	}
	if(!(PINA&(1<<5)))
	{
		lcd_cmd(0x01);
		lcd_data('8');
	}
	if(!(PINA&(1<<6)))
	{
		lcd_cmd(0x01);
		lcd_data('9');
	}
	
	PORTA=(PORTA|(1<<0)|(1<<1)|(1<<2))&~(1<<3);
	if(!(PINA&(1<<4)))
	{
		lcd_cmd(0x01);
		lcd_data('*');
      }
	if(!(PINA&(1<<5)))
	{
		lcd_cmd(0x01);
		lcd_data('0');
	}
	if(!(PINA&(1<<6)))
	{
		lcd_cmd(0x01);
		lcd_data('#');
	}
}


void main()
{
	PORTA=0xF0;   //pullup activate
	DDRA=0b00001111;
	init();
	while(1)
	{
	  keypad();
	}
}
