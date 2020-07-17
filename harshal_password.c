#define F_CPU 1000000UL
#include<avr/io.h>
#include<util/delay.h>
#include<string.h>

#define row0 0
#define row1 1
#define row2 2
#define row3 3
#define col0 4
#define col1 5
#define col2 6

int keypad(char *);
void lcd_cmd(char);
void lcd_cmd_enable();
void lcd_data(char);
void lcd_data_enable();
void lcd_display(char *);
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
void lcd_display(char *x)//x=2000
{
	
	while(*x !=  '\0')
	{
		lcd_data(*x++);
		_delay_ms(200);
		//x++; //2001//2002
	}

}
int keypad(char *a)
{
	label:
	PORTA=PORTA&~(1<<col0);
	PORTA=PORTA|(1<<col1)|(1<<col2);
	if( (PINA&(1<<row0))==0)
	{
		lcd_display("*");
		*a='1';
		return(0);
	}
	else if( (PINA&(1<<row1))==0)
	{
		lcd_display("*");
		*a='4';
		return(0);
	}
	else if( (PINA&(1<<row2))==0)
	{
		lcd_display("*");
		*a='7';
		return(0);
	}
	PORTA=PORTA&~(1<<col1);
	PORTA=PORTA|(1<<col0)|(1<<col2);
	if( (PINA&(1<<row0))==0)
	{
		lcd_display("*");
		*a='2';
		return(0);
	}
	else if( (PINA&(1<<row1))==0)
	{
		lcd_display("*");
		*a='5';
		return(0);
	}
	else if( (PINA&(1<<row2))==0)
	{
		lcd_display("*");
		*a='8';
		return(0);
	}
	else if( (PINA&(1<<row3))==0)
	{
		lcd_display("*");
		*a='0';
		return(0);
	}

	PORTA=PORTA&~(1<<col2);
	PORTA=PORTA|(1<<col0)|(1<<col1);
	if( (PINA&(1<<row0))==0)
	{
		lcd_display("*");
		*a='3';
		return(0);
	}
	else if( (PINA&(1<<row1))==0)
	{
		lcd_display("*");
		*a='6';
		return(0);
	}
	else if( (PINA&(1<<row2))==0)
	{
		lcd_display("*");
		*a='9';
		return(0);
	}
	//else
	//goto label;
}
void password()
{
	lcd_display("Enter password");
	_delay_ms(100);
	lcd_cmd(0x01);
	char a[5];
	int i=0;
	while(i<=3)
	{
	keypad(*a++);
	i++;
	
	}	
	a[4]='\0';
	 if(strcmp(a,"1234")==0)
   {
	   lcd_cmd(0xc0);
	   lcd_display("Welcome");
	   _delay_ms(1000);
	}
   else
   {
	   lcd_cmd(0xc0);++
	   lcd_display("try again");
	   _delay_ms(1000);
   }
 }

int main()
{
	PORTA=0x0F;      //just pull up activation
	DDRA=0xF0;
	init();
	while(1)
	{
	 password();
	 lcd_cmd(0x01);
	 _delay_ms(10);
	}
	return 0;
}
