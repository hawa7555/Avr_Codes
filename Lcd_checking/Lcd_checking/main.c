#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
void lcd_cmd(char x)
{
	PORTA=x&(0xF0);
	PORTA=PORTA&~(1<<0);   //RS=0
	PORTA=PORTA&~(1<<1);   //RW=0
	PORTA=PORTA|(1<<2);    //EN=1
	_delay_ms(1);
	PORTA=PORTA&~(1<<2);   //EN=0
	_delay_ms(1);
	//lcd_cmd(x<<4);
	PORTA=(x<<4)&(0xF0);
	PORTA=PORTA&~(1<<0);   //RS=0
	PORTA=PORTA&~(1<<1);   //RW=0
	PORTA=PORTA|(1<<2);    //EN=1
	_delay_ms(1);
	PORTA=PORTA&~(1<<2);   //EN=0
	_delay_ms(1);
}
void init()
{
	DDRA=0xFF;
	lcd_cmd(0x02);
	lcd_cmd(0x28);
	lcd_cmd(0x0E);
	//lcd_cmd(0x01);
	//lcd_cmd(0x06);
	lcd_cmd(0x80);
}
void lcd_data(char x)
{
	PORTA=x&(0xF0);
	PORTA=PORTA|(1<<0);    //RS=1
	PORTA=PORTA&~(1<<1);   //RW=0
	PORTA=PORTA|(1<<2);    //EN=1
	_delay_ms(1);
	PORTA=PORTA&~(1<<2);   //EN=0
	_delay_ms(1);
	//lcd_data(x<<4);
	PORTA=(x<<4)&(0xF0);
	PORTA=PORTA|(1<<0);    //RS=1
	PORTA=PORTA&~(1<<1);   //RW=0
	PORTA=PORTA|(1<<2);    //EN=1
	_delay_ms(1);
	PORTA=PORTA&~(1<<2);
	_delay_ms(1);
}
void display()
{
	lcd_cmd(0x80);
	char a[]="Fuck it in my way";
	for(int i=0;a[i]!='\0';i++)
	{
		if(i==16)
		{
			lcd_cmd(0xC0);
			}
		lcd_data(a[i]);
		//lcd_cmd(0x06);
		_delay_ms(300);
	}
	
}
void main()
{
	init();
	while(1)
	{
		display();
		lcd_cmd(0x01);
	}
}