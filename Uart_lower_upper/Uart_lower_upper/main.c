#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>

void uart_init(void);
void tx(char*);
void rx(void);
void lcd_cmd(char );
void init(void );
void lcd_data_enable_to_write();
void lcd_command_enable_to_write();
void lcd_data(char);
void lcd_display(char *);

void uart_init()
{
  UBRRL=0x33;
  //UCSRB=UCSRB|(2<<TXEN);
  UCSRB=UCSRB|(1<<RXEN)|(1<<TXEN);
  UCSRC=UCSRC|(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
}
void tx(char *x)
{
	while(*x!='\0')
	{
		UDR=*x++;
		while((UCSRA&(1<<UDRE))!=1);
		_delay_ms(10);
		//x++;
	}
}
void rx()
{
	char a;
	int temp;
	while((UCSRA&(1<<RXC))!=1);
	a=UDR;
	temp=(int)a;
	if(temp>=97 && temp<=122)
	{
		temp-=32;
		a=(char)temp;
	}
	lcd_display(a);
}
void lcd_cmd(char x)
{
	PORTC=x&(0xF0);
	lcd_cmd_enable();
	PORTC=(x<<4)&(0xF0);
	lcd_cmd_enable();
}

void lcd_cmd_enable()
{
	PORTC=PORTC&~(1<<0);   //RS=0
	PORTC=PORTC&~(1<<1);   //RW=0
	PORTC=PORTC|(1<<2);    //EN=1
	PORTC=PORTC&~(1<<2);   //EN=0
	_delay_ms(1);
}

void init()
{
	DDRC=0xFF;
	lcd_cmd(0x02);
	lcd_cmd(0x28);
	lcd_cmd(0x0E);
	//lcd_cmd(0x01);
	//lcd_cmd(0x06);
	lcd_cmd(0x80);
}

void lcd_data(char x)
{
	PORTC=x&(0xF0);
	lcd_data_enable();
	PORTC=(x<<4)&(0xF0);
	lcd_data_enable();
}

void lcd_data_enable()
{
	PORTC=PORTC|(1<<0);    //RS=1
	PORTC=PORTC&~(1<<1);   //RW=0
	PORTC=PORTC|(1<<2);    //EN=1
	PORTC=PORTC&~(1<<2);   //EN=0
	_delay_ms(1);
}

void lcd_display(char x[])
{
	for(int j=0;x[j]!='\0';j++)
	{
		lcd_data(x[j]);
		//_delay_ms(300);
		_delay_ms(50);
	}
}

void main()
{
	init();
	uart_init();
	lcd_display("outside main");
	lcd_display(0x01);
	while(1)
	{
		lcd_display("inside main");
		lcd_cmd(0x01);
		tx("hello fraands");
		_delay_ms(1);
		rx();
	}
}

