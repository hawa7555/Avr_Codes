
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
char yash[]="20002CC04E82";
char tushar[]="20002C6F5437";
char rishu[]="2000284D5411";
char pappu[]="42006B40026B";
char a[13];
typedef struct emp
{
  char name[12];
  int emp_id;
};















int main()
{
 int i;
 DDRB=3;
 lcd_init();
 uart_init();
 while(1)
 {
    for(i=0;i<12;i++)
	{
		while( (UCSRA &(1<<7))==0);
    	a[i]=UDR;
    }
  a[i]='\0';
  
  if( (strcmp(a,yash))==0)
  {
    lcd_command(0x01);
	lcd_string("HiYash");
	PORTB=0b00000001;
	_delay_ms(5000);
	PORTB=0b00000010;

  }
  else if( (strcmp(a,tushar))==0)
  {
    lcd_command(0x01);
	lcd_string("Hi Tushar");
	PORTB=0b00000001;
	_delay_ms(5000);
	PORTB=0b00000010;
  }
  else if( (strcmp(a,rishu))==0)
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
  }
 else
 {
    lcd_command(0x01);
	lcd_string("Access Denied");
 }
 }
return 0;
}
void lcd_string(char *x)
{
 while(*x)
 {
   lcd_data(*x++);
   _delay_ms(100);
 }
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
