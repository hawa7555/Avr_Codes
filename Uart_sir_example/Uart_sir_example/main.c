
#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
void uart_init(void);
void rx();
void lcd_command(char );
void lcd_init(void );
void display();
void lcd_data_enable_to_write();
void lcd_command_enable_to_write();
void lcd_data(char );
int main()
{
	lcd_init();
	uart_init();
	while(1)
	{
		rx();
	}
	return 0;
}

void rx()
{
	//while( (UCSRA &(1<<RXC))==0);
	//lcd_data(UDR);
	char a;
	int temp;
	while((UCSRA&(1<<RXC))==0);
	a=UDR;
	temp=(int)a;
	if(temp>=97 && temp<=122)
	{
		temp-=32;
		}
	a=(char)temp;
	lcd_data(a);
}
void uart_init()
{
	UBRRL=0x33;//Fosc=8Mhz,BR=9600
	UCSRB=UCSRB|(1<<RXEN);
	UCSRC=UCSRC|(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);

}

void lcd_init()
{
	DDRA=0xff;
	lcd_command(0x02);
	lcd_command(0x28);
	lcd_command(0x0E);

}
void lcd_command(char x)
{
	PORTA=(x&0xf0);  //upper 4 bit
	lcd_command_enable_to_write();
	PORTA=((x<<4)&0xf0); //lower 4 bit
	lcd_command_enable_to_write();
}
void lcd_data(char x)
{
	PORTA=(x&0xf0);  //upper 4 bit
	lcd_data_enable_to_write();
	PORTA=((x<<4)&0xf0); //lower 4 bit
	lcd_data_enable_to_write();
}
void lcd_data_enable_to_write()
{
	PORTA=PORTA |(1<<0);//RS=0;
	PORTA=PORTA&~(1<<1);//RW=0;
	PORTA=PORTA |(1<<2);//EN=1;
	PORTA=PORTA&~(1<<2);//EN=0;
	_delay_ms(1);
}

void lcd_command_enable_to_write()
{
	PORTA=PORTA&~(1<<0);//RS=0;
	PORTA=PORTA&~(1<<1);//RW=0;
	PORTA=PORTA |(1<<2);//EN=1;
	PORTA=PORTA&~(1<<2);//EN=0;
	_delay_ms(1);
}
