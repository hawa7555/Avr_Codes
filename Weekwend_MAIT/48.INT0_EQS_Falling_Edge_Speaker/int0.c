#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
void int0_init();
void lcd_init();
void lcd_command(char );
void lcd_init(void );
void display();
void lcd_data_enable_to_write();
void lcd_command_enable_to_write();
void lcd_data(char );
void lcd_string(const char *);
int main()
{
 DDRA=DDRA|(1<<0);
 lcd_init();
 int0_init();

 while(1)
 { 
  lcd_command(0x80);
  lcd_string("Hello Friends");
  lcd_command(0x01);
 }

}
void int0_init()
{
  sei();//enable Global interrupt bit
  GICR=GICR|(1<<INT0);
  MCUCR=MCUCR|2;//falling edge at INT0
}
ISR(INT0_vect)
{
 int i;
 for(i=0;i<4;i++)
 {  
   PORTA=PORTA|(1<<0);
   _delay_ms(1000);
   PORTA=PORTA&~(1<<0);
   _delay_ms(1000);
}
}

void lcd_string(const char *x)//x=2000
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
    DDRB=0xff;
	lcd_command(0x02);
    lcd_command(0x28);
	lcd_command(0x0E);
}
void lcd_command(char x)
{
 PORTB=(x&0xf0);  //upper 4 bit
 lcd_command_enable_to_write();
 PORTB=((x<<4)&0xf0); //lower 4 bit
 lcd_command_enable_to_write();
}
void lcd_data(char x)
{
 PORTB=(x&0xf0);  //upper 4 bit
 lcd_data_enable_to_write();
 PORTB=((x<<4)&0xf0); //lower 4 bit
 lcd_data_enable_to_write();
}
void lcd_data_enable_to_write()
{
 PORTB=PORTB |(1<<0);//RS=0;
 PORTB=PORTB&~(1<<1);//RW=0;
 PORTB=PORTB |(1<<2);//EN=1;
 PORTB=PORTB&~(1<<2);//EN=0;
 _delay_ms(1);
}

void lcd_command_enable_to_write()
{
 PORTB=PORTB&~(1<<0);//RS=0;
 PORTB=PORTB&~(1<<1);//RW=0;
 PORTB=PORTB |(1<<2);//EN=1;
 PORTB=PORTB&~(1<<2);//EN=0;
 _delay_ms(1);
}
