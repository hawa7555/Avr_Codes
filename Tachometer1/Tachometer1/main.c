#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>

void cntr_init();
void cast(int);
void lcd_cmd(char);
void lcd_cmd_enable();
void init();
void lcd_data(char);
void lcd_data_enable();

void cntr_init()
{
	TCNT1=0;
	TCCR1B=0x07;
}

void cast(int x)
{
	int a;
	char pos=0x85;
	//lcd_cmd(0x85);
	for(int i=0;i<6;i++)
	{
		lcd_cmd(pos);
		a=x%10;
		x=x/10;
		lcd_data(a+48);
		pos--;
	}
}

void lcd_cmd(char x)
{
	PORTA=x&(0xF0);
	lcd_cmd_enable();
	PORTA=(x<<4)&(0xF0);
	lcd_cmd_enable();
}

void lcd_cmd_enable()
{
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
	lcd_data_enable();
	PORTA=(x<<4)&(0xF0);
	lcd_data_enable();
}

void lcd_data_enable()
{
	PORTA=PORTA|(1<<0);    //RS=1
	PORTA=PORTA&~(1<<1);   //RW=0
	PORTA=PORTA|(1<<2);    //EN=1
	_delay_ms(1);
	PORTA=PORTA&~(1<<2);   //EN=0
	_delay_ms(1);
}

void main()
{
	DDRB=DDRB&(1<<1);
	cntr_init();
	init();
	while(1)
	{
		TCNT1=0;
		_delay_ms(10000);
		int rpm=TCNT1*6;
		cast(rpm);
	}
}