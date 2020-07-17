#define F_CPU 8000000UL
#include<avr/io.h>
#include<util/delay.h>
void lcd_command(char );
void lcd_init(void );
int main()
{
  lcd_init();
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
 lcd_commnad_enable_to_write();
 PORTA=((x<<4)&0xf0); //lower 4 bit
 lcd_commnad_enable_to_write();

}
void lcd_commnad_enable_to_write()
{
 PORTA=PORTA&~(1<<0);//RS=0;
 PORTA=PORTA&~(1<<1);//RW=0;
 PORTA=PORTA |(1<<2);//EN=1;
 PORTA=PORTA&~(1<<2);//EN=0;
 _delay_ms(1);
}














