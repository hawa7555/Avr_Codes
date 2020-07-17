#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#define rs 0
#define rw 1
#define en 2
void EEPROM_write(unsigned int , char );
char EEPROM_read(unsigned int );
void init_lcd();
void lcdstring(char *);
void init_lcd();
void lcdcmd(char );
void lcddata(char );
void databreak(char );
void cmdbreak(char);
int main()
{
	DDRB=0x00;
	char x;
	init_lcd();
	cmdbreak(0x80);
	lcdstring("Counter is");
	x=EEPROM_read(0x00);
	cmdbreak(0xC4);
	lcd_num(x);
	 while(1)
	 {
		 if (PINB & 1)
		 {
			 x++;
			 cmdbreak(0xC4);
			 lcd_num(x);
			 EEPROM_write(0x00,x);
			 while(PINB & 1);
			 _delay_ms(500);
		 }
		 
		 else if (PINB & 2)
		 {
			 x--;
			 cmdbreak(0xC4);
			 lcd_num(x);
			 EEPROM_write(0x00,x);
			 while(PINB & 2);
			 _delay_ms(500);
		 }
		 
	 }
	
}





void EEPROM_write(unsigned int add, char data)
{
	while((EECR & (1<<EEWE)));
	
	EEAR=add;
	EEDR=data;
	EECR|=1<<EEMWE;
	EECR|=1<<EEWE;
	
	
}


void lcdstring(char *p)
{
	while( *p !='\0')
	{
		databreak(*p);
		p++;
		_delay_ms(100);
	}
}
void init_lcd()
{
	DDRD=0xff;
	cmdbreak(0x02);
	cmdbreak(0x28);
	cmdbreak(0x0e);
	cmdbreak(0x06);
}
void lcdcmd(char x)
{
	PORTD=x;
	PORTD=PORTD&~(1<<rs);//rs=0==>select command reg
	PORTD=PORTD&~(1<<rw);//rw=0==>to write
	PORTD=PORTD|(1<<en);	//en is HIGH
	_delay_ms(1);
	PORTD=PORTD&~(1<<en);	//en is LOW
	_delay_ms(2);
}
void lcddata(char x)
{
	PORTD=x;
	PORTD=PORTD|(1<<rs);//rs=1==>select data reg
	PORTD=PORTD&~(1<<rw);//rw=0==>to write
	PORTD=PORTD|(1<<en);	//en is HIGH
	_delay_ms(1);
	PORTD=PORTD&~(1<<en);	//en is LOW
	_delay_ms(2);
}

void databreak(char x)
{
	lcddata(x&0xf0);
	lcddata(((x<<4)&0xf0));
}
void cmdbreak(char x)
{
	
	lcdcmd(x&0xf0);
	lcdcmd(((x<<4)&0xf0));
}



char EEPROM_read(unsigned int add)
{
	while((EECR & (1<<EEWE)));
	
	EEAR=0x00;
	EECR|=1<<EERE;
	return EEDR;
}

void lcd_num(int n)
{
	
	databreak((n/1000)+48);
	n%=1000;
	
	databreak((n/100)+48);
	n%=100;
	
	databreak((n/10)+48);
	n%=10;
	
	databreak(n+48);
}