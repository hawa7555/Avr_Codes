
#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
#include<string.h>
void uart_init(void);
void rx();
void lcd_command(char );
void lcd_init(void );
void display();
void lcd_data_enable_to_write();
void lcd_command_enable_to_write();
void lcd_data(char );
void lcd_string(char *);
char zaid[]="20002CC04E82";
char harshal[]="20002C6F5437";
//char rishu[]="2000284D5411";
//char pappu[]="42006B40026B";
char a[13];


int main()
{
	int i;
	//DDRB=3;
	//DDRC=0xFF;
	//PORTC=0x0F;
	lcd_init();
	uart_init();
	lcd_string("hello");
	while(1)
	{
		for(i=0;i<12;i++)
		{
			while( (UCSRA &(1<<RXC))==0){}
			a[i]=UDR;
		}
		a[i]='\0';
		
		if( (strcmp(a,zaid))==0)
		{
			lcd_command(0x01);
			lcd_command(0x80);
			lcd_string("Hi Zaid");
		//	PORTB=0b00000001;
			_delay_ms(5000);
			//PORTB=0b00000010;

		}
		else if( (strcmp(a,harshal))==0)
		{
			lcd_command(0x01);
			lcd_command(0x80);
			lcd_string("Hi Harshal");
			PORTB=0b00000001;
			_delay_ms(5000);
			PORTB=0b00000010;
		}
		/*else if( (strcmp(a,rishu))==0)
		{
			lcd_command(0x01);
			lcd_string("Hi Rishu");
			PORTB=0b00000001;
			_delay_ms(5000);
			PORTB=0b00000010;
		}
		else if( (strcmp(a,pappu))==0)
		{
			lcd_command(0x01);
			lcd_string("Hi Pappu");
			PORTB=0b00000001;
			_delay_ms(5000);
			PORTB=0b00000010;
		}*/
		else
		{
			lcd_command(0x01);
			lcd_command(0xc0);
			lcd_string("Access Denied");
		}
	}
	return 0;
}
void lcd_display(char *x)
{
	while(*x)
	{
		lcd_data(*x);
		x++;
		_delay_ms(100);
	}
}
void uart_init()
{
	UBRRL=0x33;//Fosc=8Mhz,BR=9600
	UCSRB=UCSRB|(1<<RXEN);
	UCSRC=UCSRC|(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);

}

void init()
{
	DDRA=0xff;
	lcd_command(0x02);
	lcd_command(0x28);
	lcd_command(0x0E);
	lcd_command(0x06);

}
void lcd_cmd(char x)
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
