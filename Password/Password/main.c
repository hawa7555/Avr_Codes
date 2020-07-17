#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

#define row0 0
#define row1 1
#define row2 2
#define row3 3
#define col0 4
#define col1 5
#define col2 6
#define col3 7

void keypad();
void lcd_cmd(char);
void lcd_cmd_enable();
void lcd_data(char);
void lcd_data_enable();
void lcd_display(char []);

static int i=0;
char a[5];

void keypad()
{
	//static int i=0;
	//char a[4];
	PORTA=PORTA&~(1<<col0);
	PORTA=PORTA|(1<<col1)|(1<<col2)|(1<<col3);
	if( (PINA&(1<<row0))==0 )
	{
		lcd_cmd(0x01);
		lcd_display("*");
	    a[i]=7;
		i++;
		return;
	}
	
	else if( (PINA&(1<<row1))==0 )
	{
		lcd_cmd(0x01);
		lcd_display("*");
		a[i]=4;
		i++;
		return;
	}
	
	else if( (PINA&(1<<row2))==0 )
	{
		lcd_cmd(0x01);
		lcd_display("*");
		a[i]=1;
		i++;
		return;
	}
	


	PORTA=PORTA&~(1<<col1);
	PORTA=PORTA|(1<<col0)|(1<<col2)|(1<<col3);
	
	if( (PINA&(1<<row0))==0 )
	{
		lcd_cmd(0x01);
		lcd_display("*");
		a[i]=8;
		i++;
		return;
	}
	
	else if( (PINA&(1<<row1))==0 )
	{
		lcd_cmd(0x01);
		lcd_display("*");
	    a[i]=5;
	    i++;
		return;
	}
	
	else if( (PINA&(1<<row2))==0 )
	{
		lcd_cmd(0x01);
		lcd_display("*");
		a[i]=2;
		i++;
		return;
	}
	
		
	PORTA=PORTA&~(1<<col2);
	PORTA=PORTA|(1<<col0)|(1<<col1)|(1<<col3);
	
	if( (PINA&(1<<row0))==0 )
	{
		lcd_cmd(0x01);
		lcd_display("*");
		a[i]=9;
		i++;
		return;
	}
	
	else if( (PINA&(1<<row1))==0 )
	{
		lcd_cmd(0x01);
		lcd_display("*");
		a[i]=6;
		i++;
		return;
	}
	
	else if( (PINA&(1<<row2))==0 )
	{
		lcd_cmd(0x01);
		lcd_display("*");
		a[i]=3;
		i++;
		return;
	}
	
	
	
	/*PORTA=PORTA&~(1<<col3);
	PORTA=PORTA|(1<<col0)|(1<<col1)|(1<<col2);
	
	if( (PINA&(1<<row0))==0 )
	{
		lcd_cmd(0x01);
		lcd_display("*");
	}
	
	else if( (PINA&(1<<row1))==0 )
	{
		lcd_cmd(0x01);
		lcd_display("*");
	}
	
	else if( (PINA&(1<<row2))==0 )
	{
		lcd_cmd(0x01);
		lcd_display("*");
	}
	
	else if( (PINA&(1<<row3))==0 )
	{
		lcd_cmd(0x01);
		lcd_display("*");
	}*/
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

void lcd_display(char a[])
{
	for(int i=0;a[i]!='\0';i++)
	{
		lcd_data(a[i]);
		//_delay_ms(300);
		_delay_ms(50);
	}
}

void password()
{
	lcd_display("Enter password");
	do
	{
	  keypad();
	}while(i<5);
   
   a[++i]='\0';
   i=0;
   
   if(strcmp(a,"1234")==0)
   {
	   lcd_display("Welcome");
	   
   }
   else
   {
	   lcd_display("try again");
	   _delay_ms(500);
	   password();
   }
 }

void main()
{
	PORTA=0x0F;      //just pull up activation
	DDRA=0xF0;
	init();
	while(1)
	{
	 password();
	}
}
