#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
void lcd_command(char );
void lcd_init(void );
void display();
void lcd_data_enable_to_write();
void lcd_command_enable_to_write();
void lcd_data(char );
void lcd_string(char *);
int main()
{
  lcd_init();
  while(1)
  {
    
    display();
	lcd_command(0x01);


  }
return 0;
}


void display()
{
 char a[]="GOD IS ONE";
 char b[]="BUT WHO BELIEVS";
 lcd_command(0x80);
 lcd_string(a); //a=2000
 lcd_command(0xc0);
 lcd_string(b); //a=2000
}
void lcd_string(char *x)//x=2000
{
  
  while(*x !=  '\0')
  {
    lcd_data(*x++);
	_delay_ms(300);
	//x++; //2001//2002
  }

}
void lcd_init()
{
    DDRD=0xff;
	lcd_command(0x02);
    lcd_command(0x28);
	lcd_command(0x0E);

}
void lcd_command(char x)
{
 PORTD=(x&0xf0);  //upper 4 bit
 lcd_command_enable_to_write();
 PORTD=((x<<4)&0xf0); //lower 4 bit
 lcd_command_enable_to_write();
}
void lcd_data(char x)
{
 PORTD=(x&0xf0);  //upper 4 bit
 lcd_data_enable_to_write();
 PORTD=((x<<4)&0xf0); //lower 4 bit
 lcd_data_enable_to_write();
}
void lcd_data_enable_to_write()
{
 PORTD=PORTD |(1<<0);//RS=0;
 PORTD=PORTD&~(1<<1);//RW=0;
 PORTD=PORTD |(1<<2);//EN=1;
 PORTD=PORTD&~(1<<2);//EN=0;
 _delay_ms(1);
}

void lcd_command_enable_to_write()
{
 PORTD=PORTD&~(1<<0);//RS=0;
 PORTD=PORTD&~(1<<1);//RW=0;
 PORTD=PORTD |(1<<2);//EN=1;
 PORTD=PORTD&~(1<<2);//EN=0;
 _delay_ms(1);
}
