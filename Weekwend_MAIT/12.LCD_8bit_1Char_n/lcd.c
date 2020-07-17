#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
void lcd_command(char );
void lcd_init(void );
void lcd_data(char );
void lcd_display(void );
int main()
{
  lcd_init();
  lcd_display();
}

void lcd_display()
{
  lcd_data('G');
  _delay_ms(100);
  lcd_data('O');
  _delay_ms(100);
  lcd_data('D');
  _delay_ms(100);
   lcd_data(' ');
   _delay_ms(100);
  lcd_data('I');
  _delay_ms(100);
  lcd_data('S');
  _delay_ms(100);
   lcd_data(' ');
   _delay_ms(100);
  lcd_data('O');
  _delay_ms(100);
  lcd_data('N');
  _delay_ms(100);
   lcd_data('E');
}
void lcd_init()
{
    DDRA=0xff;
	DDRB=DDRB|7;
	lcd_command(0x38);
	lcd_command(0x06);
	lcd_command(0x0E);
	lcd_command(0x01);
	lcd_command(0x80);
}

void lcd_command(char x)
{
 PORTA=x;
 PORTB=PORTB&~(1<<0);//RS=0;
 PORTB=PORTB&~(1<<1);//RW=0;
 PORTB=PORTB |(1<<2);//EN=1;
 PORTB=PORTB&~(1<<2);//EN=0;
 _delay_ms(1);
}
void lcd_data(char x)
{
 PORTA=x;
 PORTB=PORTB |(1<<0);//RS=1;
 PORTB=PORTB&~(1<<1);//RW=0;
 PORTB=PORTB |(1<<2);//EN=1;
 PORTB=PORTB&~(1<<2);//EN=0;
 _delay_ms(1);
}
