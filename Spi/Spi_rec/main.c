#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
void lcd_command(char );
void lcd_init(void );
void display();
void lcd_data_enable_to_write();
void lcd_command_enable_to_write();
void lcd_data(char );

void Spi_init()
{
	//DDRB=DDRB&~(1<<PB7);
	//DDRB=DDRB&~(1<<PB6);
	SPCR=SPCR|(1<<SPE)|(1<<DORD);
 }
 
void Spi_receive()
{
	char a;
	while(!(SPSR&(1<<SPIF)));
	a=SPDR;
	lcd_data(a);
	_delay_ms(10);
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
	_delay_ms(1);
	PORTA=PORTA&~(1<<2);//EN=0;
	_delay_ms(1);
}

void lcd_command_enable_to_write()
{
	PORTA=PORTA&~(1<<0);//RS=0;
	PORTA=PORTA&~(1<<1);//RW=0;
	PORTA=PORTA |(1<<2);//EN=1;
	_delay_ms(1);
	PORTA=PORTA&~(1<<2);//EN=0;
	_delay_ms(1);
}
void main()
{
	Spi_init();
	lcd_init();
	//while(1)
	//{
		Spi_receive();
	//}
}